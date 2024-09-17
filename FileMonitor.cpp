#include <windows.h>
#include <iostream>
#include "FileSystemMonitor.h"
#include "LogFileHandler.h"

//void MonitorDirectory( const std::wstring & directory ) {
//  HANDLE hDir = CreateFileW(
//    directory.c_str(),
//    FILE_LIST_DIRECTORY,
//    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
//    NULL,
//    OPEN_EXISTING,
//    FILE_FLAG_BACKUP_SEMANTICS,
//    NULL );
//
//  if ( hDir == INVALID_HANDLE_VALUE ) {
//    std::cerr << "Ошибка при открытии директории." << std::endl;
//    return;
//  }
//
//  char buffer[1024];
//  DWORD bytesReturned;
//
//  while ( true ) {
//    if ( ReadDirectoryChangesW(
//      hDir,
//      &buffer,
//      sizeof( buffer ),
//      TRUE,
//      FILE_NOTIFY_CHANGE_FILE_NAME,
//      &bytesReturned,
//      NULL,
//      NULL ) ) {
//      std::cout << "Directory is changed!" << std::endl;
//    }
//    else {
//      std::cerr << "Error with ReadDirectoryChangesW." << std::endl;
//      break;
//    }
//  }
//
//  CloseHandle( hDir );
//}


void WaitForStopCommand( FileSystemMonitor & monitor ) {
  std::string command;
  while ( monitor.IsMonitoring() ) {
    std::cout << "Insert 'q' to stop monitoring." << std::endl;
    std::cin >> command;
    if ( command == "q" ) {
      monitor.StopMonitoring();
      break;
    }
  }
}



int main() {
  //std::wstring directoryToWatch = L"C:\\temp";  // Задайте путь к директории
  //MonitorDirectory( directoryToWatch );
  //return 0;

  std::wstring directoryToWatch = L"C:\\temp";
  std::wstring logFilePath = L"log.txt";

  FileSystemMonitor monitor( directoryToWatch );
  auto logHandler = std::make_shared<LogFileHandler>( logFilePath );

  monitor.AddEventHandler( logHandler );
  monitor.StartMonitoring();

  // Запуск функции ожидания команды пользователя в основном потоке
  WaitForStopCommand( monitor );
}