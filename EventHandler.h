#pragma once
#include "FileEvent.h"

class EventHandler {
public:
  virtual ~EventHandler() = default;
  virtual void HandleEvent( const FileEvent & event ) = 0;
};