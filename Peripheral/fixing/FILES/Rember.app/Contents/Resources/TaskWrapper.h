/*
 
TaskWrapper.h
  
  TaskWrapper 
  
  Copyright (C) 2004  Eddie Kelley  <eddie@kelleycomputing.net>
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#import <Foundation/Foundation.h>

@protocol TaskWrapperController

// Your controller's implementation of this method will be called when output arrives from the NSTask.
// Output will come from both stdout and stderr, per the TaskWrapper implementation.
- (void)appendOutput:(NSString *)output;

// This method is a callback which your controller can use to do other initialization when a process
// is launched.
- (void)processStarted;

// This method is a callback which your controller can use to do other cleanup when a process
// is halted.
- (void)processFinished;

@end

@interface TaskWrapper : NSObject {
    NSTask 			*task;
    id				<TaskWrapperController>controller;
    NSArray			*arguments;
}
// returns task termination status
-(int)terminationStatus;

// returns a task's process identifier
-(int)processID;

// This method returns status of the task
-(BOOL)isRunning;

// This is the designated initializer - pass in your controller and any task arguments.
// The first argument should be the path to the executable to launch with the NSTask.
- (id)initWithController:(id <TaskWrapperController>)controller arguments:(NSArray *)args;

// This method launches the process, setting up asynchronous feedback notifications.
- (void) startProcess;

// This method stops the process, stoping asynchronous feedback notifications.
- (void) stopProcess;

@end

