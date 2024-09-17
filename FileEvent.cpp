#include "FileEvent.h"

FileEvent::FileEvent( const std::wstring & fileName, DWORD action, bool isDirectory )
  : fileName_( fileName ), isDirectory_( isDirectory ) {
  eventType_ = TranslateAction( action );
}

std::wstring FileEvent::GetFileName() const {
  return fileName_;
}

FileEvent::EventType FileEvent::GetEventType() const {
  return eventType_;
}

bool FileEvent::IsDirectory() const {
  return isDirectory_;
}

FileEvent::EventType FileEvent::TranslateAction( DWORD action ) {
  switch ( action ) {
    case FILE_ACTION_ADDED:
      return Created;
    case FILE_ACTION_REMOVED:
      return Deleted;
    case FILE_ACTION_MODIFIED:
      return Modified;
    case FILE_ACTION_RENAMED_OLD_NAME:
      return RenamedOldName;
    case FILE_ACTION_RENAMED_NEW_NAME:
      return RenamedNewName;
    default:
      return Unknown;
  }
}