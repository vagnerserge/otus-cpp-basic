#pragma once
#include "EventHandler.h"
#include <fstream>

class LogFileHandler : public EventHandler {
public:
  LogFileHandler( const std::wstring & logFilePath );
  ~LogFileHandler();

  void HandleEvent( const FileEvent & event ) override;

private:
  std::wofstream logFile_;
};