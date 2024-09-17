#include "FileSystemMonitor.h"
#include <iostream>
#include <thread>

#define MONITOR_FLAGS (FILE_NOTIFY_CHANGE_FILE_NAME | \
                       FILE_NOTIFY_CHANGE_DIR_NAME  | \
                       FILE_NOTIFY_CHANGE_ATTRIBUTES | \
                       FILE_NOTIFY_CHANGE_SIZE | \
                       FILE_NOTIFY_CHANGE_LAST_WRITE | \
                       FILE_NOTIFY_CHANGE_CREATION)

FileSystemMonitor::FileSystemMonitor( const std::wstring & directory )
  : directory_( directory ), hDir_( INVALID_HANDLE_VALUE ), monitoring_( false ) {}

FileSystemMonitor::~FileSystemMonitor() {
  if ( hDir_ != INVALID_HANDLE_VALUE ) {
    CloseHandle( hDir_ );
  }
}

void FileSystemMonitor::StartMonitoring() {
  hDir_ = CreateFileW(
    directory_.c_str(),
    FILE_LIST_DIRECTORY,
    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
    NULL,
    OPEN_EXISTING,
    FILE_FLAG_BACKUP_SEMANTICS,
    NULL );

  if ( hDir_ == INVALID_HANDLE_VALUE ) {
    std::cerr << "Open directory error." << std::endl;
    return;
  }

  monitoring_ = true;
  //Monitor();

  std::thread monitoringThread( &FileSystemMonitor::Monitor, this );  // Запуск мониторинга в отдельном потоке
  monitoringThread.detach();  // Отсоединяем поток, чтобы он работал фоном
}

void FileSystemMonitor::StopMonitoring() {
  monitoring_ = false;
  if ( hDir_ != INVALID_HANDLE_VALUE ) {
    CloseHandle( hDir_ );
    hDir_ = INVALID_HANDLE_VALUE;
  }
}

void FileSystemMonitor::AddEventHandler( std::shared_ptr<EventHandler> handler ) {
  handlers_.push_back( handler );
}

void FileSystemMonitor::Monitor() {
  char buffer[1024];
  DWORD bytesReturned;

  while ( monitoring_ ) {
    if ( ReadDirectoryChangesW(
      hDir_,
      &buffer,
      sizeof( buffer ),
      TRUE,
      MONITOR_FLAGS,
      &bytesReturned,
      NULL,
      NULL ) ) {

      FILE_NOTIFY_INFORMATION * notifyInfo = reinterpret_cast< FILE_NOTIFY_INFORMATION * >( buffer );
      std::wstring fileName( notifyInfo->FileName, notifyInfo->FileNameLength / sizeof( WCHAR ) );

      // Определение, является ли объект папкой
      DWORD fileAttributes = GetFileAttributesW( ( directory_ + L"\\" + fileName ).c_str() );
      bool isDirectory = ( fileAttributes != INVALID_FILE_ATTRIBUTES ) && ( fileAttributes & FILE_ATTRIBUTE_DIRECTORY );

      FileEvent event( fileName, notifyInfo->Action, isDirectory );

      // Уведомление всех обработчиков
      for ( const auto & handler : handlers_ ) {
        handler->HandleEvent( event );
      }
    }
    else {
      std::cerr << "Error with ReadDirectoryChangesW." << std::endl;
      break;
    }
  }
  std::cout << "Monitoring is stopped." << std::endl;  // Вывод сообщения при завершении мониторинга
}