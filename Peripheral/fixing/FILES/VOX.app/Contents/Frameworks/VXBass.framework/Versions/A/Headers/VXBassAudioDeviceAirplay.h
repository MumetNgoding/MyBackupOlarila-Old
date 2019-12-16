//
//  VXBassAudioDeviceAirplay.h
//  VXBass
//
//  Created by Oleg Naumenko on 10/12/15.
//  Copyright © 2015 Coppertino Inc. All rights reserved.
//


#import "VXBassAudioDevice.h"
#import "VXAirTunes.h"

@interface VXBassAudioDeviceAirplay : VXBassAudioDevice

- (instancetype)initWithPendingDevice:(VXPendingAirDevice*)pendingDevice;
//- (instancetype)initWithPendingDeviceName:(NSString*)pendingDeviceName host:(NSString*)host port:(NSUInteger)port;

@property (nonatomic, readonly) NSString * host;
@property (nonatomic, readonly) NSUInteger port;
@property (nonatomic, readonly, strong) VXPendingAirDevice * pendingDevice;

@end