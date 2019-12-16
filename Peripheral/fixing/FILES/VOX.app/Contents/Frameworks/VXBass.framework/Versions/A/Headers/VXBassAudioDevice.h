//
//  VXBassAudioDevice.h
//  VXBass
//
//  Created by Oleg Naumenko on 7/31/15.
//  Copyright (c) 2015 Coppertino Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VXBassAudioDeviceSource.h"

@class VXMatrix;
//@class VXBassAudioDeviceSource;

@interface VXBassAudioDevice : NSObject

- (BOOL)hasJack;
- (BOOL)isJackConnected;

- (void)selectOutputDeviceSource:(VXBassAudioDeviceSource *)audioDeviceSource;
- (VXBassAudioDeviceSource *)outputDeviceSourceWithName:(NSString *)nameOfOutputDeviceSource;//deprecated
- (VXBassAudioDeviceSource *)outputDeviceSourceWithID:(NSString *)outputDeviceSourceID;
- (BOOL)outputDeviceSourceIsSelected:(VXBassAudioDeviceSource *)audioDeviceSource;
- (VXBassAudioDeviceSource *) currentOutputDeviceSource;
- (NSInteger)bestCompatibleSampleRateTo:(NSInteger)sampleRate;

- (VXMatrix *)matrixForMultichannel;
- (VXMatrix *)matrixForStereo;

- (NSString *)advancedDescription;

// hog mode
- (BOOL)isInHogMode;
- (BOOL)isHogedByCurrentProcess;
- (BOOL)hogDevice;
- (BOOL)unhogDevice;

@property (nonatomic, strong) NSString				*deviceName;
@property (nonatomic, readonly) NSString	*humanReadableDeviceName;
@property (nonatomic, strong) NSString				*deviceUID;
@property (nonatomic, strong) NSArray				*outputDeviceSources;

@property (nonatomic, assign) NSInteger		bitDepth;
@property (nonatomic, assign) NSInteger		sampleRate;
@property (nonatomic, assign) NSInteger		bassDeviceIndex;
@property (nonatomic, assign) NSInteger		numberOfChannels;
@property (nonatomic, readonly) NSInteger	numberOfChannelsInDesiredLayoutConfiguration;

@property (nonatomic, assign) BOOL	isOutput;
@property (nonatomic, assign) BOOL	isAirplay;
@property (nonatomic, assign) BOOL	isBuiltIn;
@property (nonatomic, assign) BOOL	isSystemDefault;
@property (nonatomic, assign) BOOL	supportsSampleRateSwitching;
@property (nonatomic, readonly) NSArray<NSNumber*>* supportedSampleRates;

@property (nonatomic, assign) BOOL	isExternal;

@property (nonatomic, readonly)BOOL isNetwork;
@property (nonatomic, assign) BOOL	isSonos;

@property (nonatomic, assign) float deviceVolume;
@property (nonatomic, assign) BOOL  deviceMute;


@end
