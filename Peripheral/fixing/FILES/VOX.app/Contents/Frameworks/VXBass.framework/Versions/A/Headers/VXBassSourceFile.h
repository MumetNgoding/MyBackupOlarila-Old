//
//  VXBassSourceFile.h
//  Vox
//
//  Created by Igor Marchenko on 29.01.13.
//  Copyright (c) 2013 Coppertino Inc. All rights reserved.
//

#import "VXBassSource.h"

#define BASS_NETWORK_FILESYSTEM_BUFFERING_LIMIT 20 * 1024 * 1024

typedef NS_ENUM (NSInteger, VXBassSourceFileType) {
	VXBassSourceFileUnknown = -1,
	VXBassSourceFileMusic,
	VXBassSourceFileGame,
	VXBassSourceFileStream,
};


@class VXMatrix;

@interface VXBassSourceFile : VXBassSource {
	uint32_t _outputMixerStream;
}

@property (nonatomic, readonly, assign) VXBassSourceFileType	type;
@property (nonatomic, assign) BOOL								tryGapless;
@property (nonatomic, assign) uint32_t							gaplessGetNextSync;
@property (nonatomic, assign) uint32_t							endFileSync;
@property (strong, nonatomic, readonly) NSFileHandle			*fileHandle;

+ (VXBassSourceFileType)typeOfFileWithExtension:(NSString *)extension;

- (instancetype)initWithURL:(NSURL *)fileURL
                   delegate:(id <VXBassSourceDelegate>) delegate
                   userInfo:(id)userObject
               loadInMemory:(BOOL)loadIntoMemory;

- (instancetype)initForTagsWithURL:(NSURL *)fileURL;
- (void) setUpMatrix;

//- (BOOL)transferMixerFromSource:(VXBassSourceFile *)fromSource;
//- (void)attachToCurrentMixer;
//- (void)restartMixer;


@end
