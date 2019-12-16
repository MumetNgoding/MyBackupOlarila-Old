//
//  VXBassSourceNetwork.h
//  Vox
//
//  Created by Marchenko Igor on 18.01.13.
//  Copyright (c) 2013 Coppertino Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VXBassSourceFile.h"

@interface VXBassSourceURL : VXBassSourceFile

@property (nonatomic, strong) NSString	*streamName;
@property (nonatomic, strong) NSString	*streamTitle;
@property (nonatomic, strong) NSString	*streamURL;
@property (nonatomic, strong) NSString  *stationName;
@property (nonatomic, strong) NSString  *metaInfo;

@property (nonatomic, readonly) BOOL shouldCache;
@property (nonatomic, assign) void * byteBuffer;

- (instancetype)initWithURL:(NSURL *)url
                   delegate:(id<VXBassSourceDelegate>) delegate
                   userInfo:(id) userObject
                shouldCache:(BOOL) doCache;

//- (NSString *)metaInfo;
//- (NSString *)streamURL;
- (NSArray  *)endlessStreamNetHeaders;
- (NSString *)getStreamRadioName;
- (void)streamInfoUpdated;

@end
