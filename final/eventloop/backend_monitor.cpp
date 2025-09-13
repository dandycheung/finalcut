/***********************************************************************
* backend_monitor.cpp - Monitoring general objects                     *
*                                                                      *
* This file is part of the FINAL CUT widget toolkit                    *
*                                                                      *
* Copyright 2023-2025 Markus Gans                                      *
*                                                                      *
* FINAL CUT is free software; you can redistribute it and/or modify    *
* it under the terms of the GNU Lesser General Public License as       *
* published by the Free Software Foundation; either version 3 of       *
* the License, or (at your option) any later version.                  *
*                                                                      *
* FINAL CUT is distributed in the hope that it will be useful, but     *
* WITHOUT ANY WARRANTY; without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
* GNU Lesser General Public License for more details.                  *
*                                                                      *
* You should have received a copy of the GNU Lesser General Public     *
* License along with this program.  If not, see                        *
* <http://www.gnu.org/licenses/>.                                      *
***********************************************************************/

#include <unistd.h>

#include "final/eventloop/eventloop_functions.h"
#include "final/eventloop/eventloop.h"
#include "final/eventloop/backend_monitor.h"
#include "final/util/fsystem.h"

namespace finalcut
{

//----------------------------------------------------------------------
// class BackendMonitor
//----------------------------------------------------------------------

// constructors and destructor
//----------------------------------------------------------------------
BackendMonitor::BackendMonitor (EventLoop* eloop)
  : Monitor(eloop)
{ }

//----------------------------------------------------------------------
BackendMonitor::~BackendMonitor() noexcept // destructor
{
  // Close pipe file descriptors
  static const auto& fsystem = FSystem::getInstance();

  if ( self_pipe.getReadFd() != PipeData::NO_FILE_DESCRIPTOR )
  {
    static_cast<void>(fsystem->close(self_pipe.getReadFd()));
    self_pipe.setReadFd(NO_FILE_DESCRIPTOR);
  }

  if ( self_pipe.getWriteFd() != PipeData::NO_FILE_DESCRIPTOR )
  {
    static_cast<void>(fsystem->close(self_pipe.getWriteFd()));
    self_pipe.setWriteFd(NO_FILE_DESCRIPTOR);
  }
}

// public methods of BackendMonitor
//----------------------------------------------------------------------
void BackendMonitor::setEvent() const noexcept
{
  // Early exit if pipe is not valid
  if ( self_pipe.getWriteFd() == PipeData::NO_FILE_DESCRIPTOR )
    return;

  // The event loop is notified by write access to the pipe
  uint64_t buffer{SIGNAL_NOTIFICATION};
  const auto successful = ::write ( self_pipe.getWriteFd()
                                  , &buffer, sizeof(buffer) ) > 0;

  if ( ! successful )
  {
    // Possible error handling
  }
}

//----------------------------------------------------------------------
void BackendMonitor::clearEvent() const
{
  if ( ! hasValidFileDescriptor() )
    throw monitor_error{"Cannot clear event: invalid file descriptor"};

  try
  {
    drainPipe(getFileDescriptor());
  }
  catch (const std::exception& e)
  {
    // Wrap the exception with more context
    auto err_msg{ std::string{"Failed to clear backend monitor event: "}
                + e.what() };
    throw monitor_error(err_msg);
  }
}

//----------------------------------------------------------------------
void BackendMonitor::trigger (short return_events)
{
  try
  {
    clearEvent();
    Monitor::trigger(return_events);
  }
  catch (...)
  {
    clearEvent();
    throw;  // Re-throw other errors
  }
}


// private methods of BackendMonitor
//----------------------------------------------------------------------
void BackendMonitor::init()
{
  static const auto& fsystem = FSystem::getInstance();
  setEvents (POLLIN);

  // Set up pipe for notification
  if ( fsystem->pipe(self_pipe) != 0 )
  {
    throw monitor_error{"No pipe could be set up for the signal monitor."};
  }

  setFileDescriptor(self_pipe.getReadFd());  // Read end of pipe
  setInitialized();
}

}  // namespace finalcut
