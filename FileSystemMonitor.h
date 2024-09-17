#pragma once
#include <windows.h>
#include <string>
#include <memory>
#include <vector>
#include "EventHandler.h"
#include "FileEvent.h"

class FileSystemMonitor {
public:
  FileSystemMonitor( const std::wstring & directory );
  ~FileSystemMonitor();

  void StartMonitoring();
  void StopMonitoring();
  bool IsMonitoring() const { return monitoring_; };  // Ќовый метод дл€ проверки состо€ни€ мониторинга
  void AddEventHandler( std::shared_ptr<EventHandler> handler );

private:
  void Monitor();

  std::wstring directory_;
  HANDLE hDir_;
  bool monitoring_;
  std::vector<std::shared_ptr<EventHandler>> handlers_;
};