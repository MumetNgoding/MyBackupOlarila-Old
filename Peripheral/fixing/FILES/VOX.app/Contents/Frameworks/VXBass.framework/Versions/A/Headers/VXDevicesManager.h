//
//  VXHardwareManagerCoreAudio.h
//  VXBass
//
//  Created by Oleg Naumenko on 7/29/15.
//  Copyright (c) 2015 Coppertino Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VXBassAudioDevice.h"

@class VXDevicesManager;

@protocol VXDeviceManagerDelegate <NSObject>

- (void) deviceManager:(VXDevicesManager*)manager reportsHeadphoneJackStateChange:(BOOL)isRemoved;
- (void) deviceManager:(VXDevicesManager*)manager changedCurrentAudioDevice:(VXBassAudioDevice*)newDevice;
- (void) deviceManagerChangedDeviceLayout:(VXDevicesManager*)manager;
- (void) deviceManager:(VXDevicesManager*)manager deviceChangedVolume:(VXBassAudioDevice*)device;

- (void) deviceManager:(id)manager devicePausedPlayback:(VXBassAudioDevice*)device;
- (void) deviceManager:(id)manager deviceResumedPlayback:(VXBassAudioDevice*)device;
- (void) deviceManager:(VXDevicesManager*)manager deviceRequestsNextTrack:(VXBassAudioDevice*)device;
- (void) deviceManager:(VXDevicesManager*)manager deviceRequestsPreviousTrack:(VXBassAudioDevice*)device;

@end

@protocol VXDevicesManagerTrackDataSource <NSObject>

- (void) currentTrackMetaData:(NSDictionary*)data forDevicesManager:(VXDevicesManager*)manager;
// data = @{@"artist":@"name", @"album":@"albumtitle", @"track":@"treckname", @"artwork":artworkNSImage}

@end

@interface VXDevicesManager : NSObject

- (instancetype) initWithDelegate:(id<VXDeviceManagerDelegate>)delegate;

@property(nonatomic, readonly) NSArray *audioDevices;

- (void) shutOffDevice:(VXBassAudioDevice*)device;
- (BOOL) setUpDevice:(VXBassAudioDevice*)newDevice withSampleRate:(NSInteger)sampleRate;

- (void) setSampleRate:(NSInteger)sr completionBlock:(void (^)())block;
- (NSInteger) bestCompatibleSampleRateTo:(NSInteger)desiredRate;

- (VXBassAudioDevice*) audioDeviceWithUID:(NSString *)deviceUID;

- (void) onPlay;
- (void) onPause;
- (void) onDidSeek;

- (void) setReachabilityStatus:(BOOL)reachable;

@property (nonatomic, weak) id <VXDevicesManagerTrackDataSource> trackDataSource;
@property (nonatomic, assign)   VXBassAudioDevice * currentAudioDevice;
@property (nonatomic, readonly) NSInteger sampleRate;

@property(nonatomic, retain)   NSString	* airPlayAudioDeviceSourceID;//sets current multiple output device output
@property(nonatomic, retain)   NSString	* audioDeviceOutputUID;//sets current device
@property(nonatomic, readonly) NSString * airplayDeviceUID;//getter for AirPlay device UID
@property(nonatomic, readonly) NSString * defaultDeviceUID;//getter for system default device UID
@property(nonatomic, assign)   BOOL		  airplayDevicesAvailable;

@property(nonatomic, assign) uint32_t mixerHandle;

@property(nonatomic, assign) float deviceVolume;
@property(nonatomic, assign) BOOL  deviceMute;

@property(nonatomic, readonly) BOOL acceptsMetadata;
@property(nonatomic, readonly) BOOL isFullyReady;

- (void) sendMetadata:(NSDictionary *)metadata;
- (void) sendPlaybackPosition:(float)position totalDuration:(float)duration;
- (void) startDeviceDiscovery;

@end
