#include "LogFileHandler.h"
#include <sstream>
#include <iostream>  // Для std::cerr и std::wcout

LogFileHandler::LogFileHandler( const std::wstring & logFilePath ) {
  logFile_.open( logFilePath, std::ios::app );
}

LogFileHandler::~LogFileHandler() {
  if ( logFile_.is_open() ) {
    logFile_.close();
  }
}

void LogFileHandler::HandleEvent( const FileEvent & event ) {
  //if ( logFile_.is_open() ) {
  //  std::wstring type = event.IsDirectory() ? L"Directory" : L"File";
  //  logFile_ << type << L": " << event.GetFileName() << L", Action: ";

  //  switch ( event.GetEventType() ) {
  //    case FileEvent::Created:
  //      logFile_ << L"Created";
  //      break;
  //    case FileEvent::Deleted:
  //      logFile_ << L"Deleted";
  //      break;
  //    case FileEvent::Modified:
  //      logFile_ << L"Modified";
  //      break;
  //    case FileEvent::RenamedOldName:
  //      logFile_ << L"Renamed (Old Name)";
  //      break;
  //    case FileEvent::RenamedNewName:
  //      logFile_ << L"Renamed (New Name)";
  //      break;
  //    default:
  //      logFile_ << L"Unknown";
  //  }

  //  logFile_ << std::endl;
  //}

  if ( !logFile_.is_open() ) {
    std::wcerr << L"Лог-файл не открыт." << std::endl;
    return;
  }

  std::wstringstream logStream;
  std::wstring type = event.IsDirectory() ? L"Directory" : L"File";
  logStream << type << L": " << event.GetFileName() << L", Action: ";

  switch ( event.GetEventType() ) {
    case FileEvent::Created:
      logStream << L"Created";
      break;
    case FileEvent::Deleted:
      logStream << L"Deleted";
      break;
    case FileEvent::Modified:
      logStream << L"Modified";
      break;
    case FileEvent::RenamedOldName:
      logStream << L"Renamed (Old Name)";
      break;
    case FileEvent::RenamedNewName:
      logStream << L"Renamed (New Name)";
      break;
    default:
      logStream << L"Unknown";
  }

  logStream << std::endl;

  // Выводим в файл
  logFile_ << logStream.str();

  // Выводим в консоль для отладки
  std::wcout << logStream.str();
}