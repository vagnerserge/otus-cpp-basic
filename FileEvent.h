#pragma once
#include <string>
#include <windows.h>

class FileEvent {
public:
  enum EventType {
    Created,
    Deleted,
    Modified,
    RenamedOldName,
    RenamedNewName,
    Unknown
  };

  FileEvent( const std::wstring & fileName, DWORD action, bool isDirectory );

  std::wstring GetFileName() const;
  EventType GetEventType() const;
  bool IsDirectory() const;

private:
  std::wstring fileName_;
  EventType eventType_;
  bool isDirectory_;

  EventType TranslateAction( DWORD action );
};