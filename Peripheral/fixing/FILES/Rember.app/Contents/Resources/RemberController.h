/* 
RemberController.h
 
RemberController class definition.
 
 Controls program interaction between TaskWrapper and Interface
 
Copyright (C) 2004  Eddie Kelley <eddie@kelleycomputing.net>

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
 
 Version History:
	0.1b Initial Public Beta
	0.1.04b Updated version online with newer memtest 4.0.4M
		¥ Memtest 4.0.4M executable included
		¥ Switched to spinning progress indicator (for better performance)
	0.2.0b
		¥ Total GUI overhaul.  
		¥ Preferences added.  
		¥ Verbose logging (filtering) function added
		¥ Test progress in status field
		¥ Loop counter
		¥ Application/Finder quit functions
	0.2.1b
		¥ Preferences window is now a sheet
		¥ Save option for log details
		¥ Dock menu
		¥ Icon added 
	0.2.2b
		¥ Performance enahncements
		¥ Icon touch-up
	0.2.3b
		¥ Uses new version of memtest executable (4.05M)
	0.3b
		¥ Uses new version of memtest executable (4.11)
		¥ Added "Continue on Error" preference
	0.3.1b
		¥ Uses new version of memtest executable (4.12)
		¥ Utilizes User Defaults system to save preferences
	0.3.2b
		¥ Uses new version of memtest executable (4.13)
		¥ Universal Binary
	0.3.3b
		¥ Now displays determinate progress
		¥ Bug fixes
		¥ First localized version.  Includes Japanese, Italian, and English languages.
	0.3.4b
		¥ New memory info window displays DIMM information
		¥ New report window displays test results in human-readable format
		¥ Rember now delays scheduled system sleep while tests are running
		¥ Uses new version of memtest executable (4.2)
 
	0.3.5b
		¥ New icon and images
		¥ Memory info window now compatible with Snow Leopard
		¥ Improved progress display and output parsing
		¥ Uses new version of memtest executable (4.22)
		¥ Provides status via Dock icon while testing or on error
 
	0.3.6b
		¥ No longer accepts decimal input for loop for memory allotment
		¥ Regression regarding memory info and early versions of Snow Leopard fixed
		¥ Modernized (not classic 9) ProcessController class (used to quit other running apps before testing)
		¥ Modernized power management functions for delaying idle system sleep (Rember now requires Mac OS X v.10.5 or later)
		¥ Now localized in Russian and French Languages
		¥ No longer limited to arbitrary limit of 8GB when allocating memory for testing

	0.3.7b
		¥ Uses new Japanese localization thanks to Norio Ikawa at MacMem dot com
		¥ Report now displays Rember version
		¥ Bug fix (cancelling testing would not reset user interface)
*/

#import <Cocoa/Cocoa.h>

#import "TaskWrapper.h"
#import "ProcessController.h"

// includes for system power notifications
#import <IOKit/IOMessage.h> 
#import <IOKit/pwr_mgt/IOPMLib.h>

@interface RemberController : NSObject <TaskWrapperController>
{
	// NSTextFields
    IBOutlet NSTextField *amountTextField, *loopTextField, *loopsTextField, *loopsCompletedTextField;
    IBOutlet id statusTextField;
	
	// NSNumberFormatters
	IBOutlet NSNumberFormatter *amountFormatter, *loopFormatter;
	
	// NSButtons
	IBOutlet id maxButton, allButton, mbButton, testButton, verboseButton, quitAllButton, 
		quitFinderButton, verboseButton2, verboseButton3, 
		saveButton, okButton, errorButton, reportButton;
	
	// NSMatrix
    IBOutlet id memoryMatrix;
	
	// NSProgressIndicator
	IBOutlet id testProgress;
	
	//Log
	IBOutlet id testLog;
	// preferences window
	IBOutlet id Preferences;
	// memory info window
	IBOutlet id MemoryInfo;
	
	IBOutlet id memoryInfoButton, memoryInfoButton2;
	
	// TaskWrapper for memtest task calls
	TaskWrapper * remberTask;
	
	// Array for storing memory information
	NSArray * memoryInfo;
	
	// Memory test report window IBOutlets
	IBOutlet id Report, reportSaveButton, reportPrintButton, reportOKButton, reportTextView;
	NSMutableDictionary * reportDict;
	
	// Preferences
	
	// rember is running BOOL
	BOOL remberRunning;
	// stop on error BOOL
	BOOL continueOnError;
	// quit all before launching BOOL
	BOOL quitAll;
	// quit finder before launching BOOL (quitAll must be TRUE for quitFinder to be TRUE)
	BOOL quitFinder;
	// max test loops BOOL
	BOOL maxLoops;
	// test all memory BOOL
	BOOL allMemory;
	// show report BOOL
	BOOL showReport;
	
	// number of total loops, and loops completed
	int totalLoops, loopsCompleted, amount;
	
	// power management assertion (prevent sleep)
	IOPMAssertionID assertionID;

	// process controller (used to quit other applications before testing)
	ProcessController *processController;

}

NSArray * testList, * progressList;
BOOL verbose, showMemoryInfo;
int terminationStatus;
int processID;

- (id) updatePreferencesPanel;
- (int) openTask:(NSString*)path withArguments:(NSArray*)arguments;

- (IBAction) amountTextFieldAction:(id)sender;
- (IBAction) loopTextFieldAction:(id)sender;
- (IBAction) testButtonAction:(id)sender;
- (IBAction) maxButtonAction:(id)sender;
- (IBAction) allButtonAction:(id)sender;
- (IBAction) mbButtonAction:(id)sender;
- (IBAction) verboseButtonAction:(id)sender;
- (IBAction) quitAllButtonAction:(id)sender;
- (IBAction) quitFinderButtonAction:(id)sender;
- (IBAction) saveButtonAction:(id)sender;
- (IBAction) reportSaveButtonAction:(id)sender;
- (IBAction) errorButtonAction:(id)sender;
- (IBAction) infoOKButtonAction:(id)sender;
- (IBAction) reportSaveButtonAction:(id)sender;
- (IBAction) reportOKButtonAction:(id)sender;
- (IBAction) reportButtonAction:(id)sender;
- (IBAction) memoryInfoButtonAction:(id)sender;
- (IBAction) terminate:(id)sender;
- (IBAction) beginMemoryInfoPanel:(id)sender;
- (IBAction) beginReportPanel:(id)self;
- (NSArray *) memoryInfo;
- (int) updateMemoryInfo;
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)app;
- (BOOL) isSnowLeopard;

@end
