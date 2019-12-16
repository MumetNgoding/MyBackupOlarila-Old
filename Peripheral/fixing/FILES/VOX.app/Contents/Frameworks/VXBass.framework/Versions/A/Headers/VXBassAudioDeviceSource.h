//
//  VXBassAudioDeviceSourceCA.h
//  VXBass
//
//  Created by Oleg Naumenko on 9/21/15.
//  Copyright © 2015 Coppertino Inc. All rights reserved.
//

//#import "VXBassAudioDevice.h"

@class VXBassAudioDevice;

@interface VXBassAudioDeviceSource : NSObject

- (id)initWithSourceID:(UInt32)sourceID audioDevice:(VXBassAudioDevice *)device;

@property (nonatomic, weak) VXBassAudioDevice	*audioDevice;
@property (nonatomic, readonly) NSString        *sourceUID;
@property (nonatomic, readonly) UInt32			sourceID;
@property (nonatomic, strong) NSString			*name;

@end
