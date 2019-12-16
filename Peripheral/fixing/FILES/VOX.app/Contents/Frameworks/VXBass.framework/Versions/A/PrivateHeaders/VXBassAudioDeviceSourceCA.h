//
//  VXBassAudioDeviceSource.h
//  Vox
//
//  Created by Igor Marchenko on 03.08.12.
//  Copyright (c) 2012 Coppertino Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VXBassAudioDeviceSource.h"

@class VXBassAudioDeviceCA;

@interface VXBassAudioDeviceSourceCA : VXBassAudioDeviceSource

- (id)initWithSourceID:(UInt32)sourceID audioDevice:(VXBassAudioDeviceCA *)device;


@end