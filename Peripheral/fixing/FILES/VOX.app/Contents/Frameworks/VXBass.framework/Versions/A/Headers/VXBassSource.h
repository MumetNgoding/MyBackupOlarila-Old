//
//  VXBassSource.h
//  Vox
//
//  Created by Marchenko Igor on 17.05.12.
//  Copyright (c) 2012 Coppertino Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#define SOURCE_GET_NEXT_INTERVAL 20.0

@protocol VXBassSourceDelegate;
@class VXMatrix;

@interface VXBassSource : NSObject {
	@protected
	uint32_t	_sourceHandle;
	NSString	*_trackMetaInfoString;
	uint32_t	_fileEndSync;
	NSURL		*_url;
}

// Hide parameterless init
- (id)init __attribute__((unavailable("init not available, use -initWithDelegate:")));
+ (id)new  __attribute__((unavailable("new  not available, use -initWithDelegate:")));

- (instancetype)initWithURL:(NSURL*)url delegate:(id<VXBassSourceDelegate>) delegate userInfo:(id)userInfo;

@property (nonatomic, weak) id <VXBassSourceDelegate> delegate;

@property (nonatomic, assign) float	tempo; //(1 = natural, no tempo effect)
@property (nonatomic, assign) BOOL  tempoEnabled;
@property (nonatomic, assign) BOOL  tempoIsTurntableStyle;

@property (nonatomic, assign) BOOL  allowsParallelLoad;

@property (nonatomic, strong)           NSURL       *originalUrl;
@property (nonatomic, readonly, strong) NSURL		*url;
@property (nonatomic, readonly, assign) uint32_t	sourceHandle;
@property (nonatomic, readonly, assign) uint32_t	mainHandler;
@property (nonatomic, readonly, strong) NSString	*trackMetaInfoString;

@property (nonatomic, readonly, assign) NSInteger   numberOfChannels;
@property (nonatomic, assign)           uint32_t	outputMixerStream;
@property (nonatomic, strong)           VXMatrix	*mixerMatrix;
#pragma mark track properties

- (NSString *) advancedDescription;
- (NSString *) pluginString;

@property (nonatomic, readonly, assign) NSTimeInterval totalLength;

@property (nonatomic, assign)   NSTimeInterval currentPosition;
//@property (nonatomic, assign)   NSTimeInterval timeLeft;
@property (nonatomic, readonly) double downloadProgress;//(0...1.0f)
@property (nonatomic, readonly) double downloadStart;//(0...1.0f)
@property (nonatomic, assign)   float crossFadeTime;
@property (nonatomic, assign)   NSUInteger bitrate;
@property (nonatomic, assign)   float volume;

@property (nonatomic, assign)   float getNextInterval;

@property (nonatomic, assign)   NSArray * histogram;

- (void)setChannelsPan:(float)channelsPan;

- (void)generateSourceHandler;
- (void)generateEndSync;
- (void)deallocateSourceHandler;
- (void)removeEndSyncs;

- (void) willChangePositionInMixer:(NSTimeInterval)oldPosition;
- (void)  didChangePositionInMixer:(NSTimeInterval)newCurrentPosition;

- (NSString *)getTagInformationForTag:(uint32_t)tag;
- (NSArray *)getTagsArrayInformationForTag:(uint32_t)tag;

- (NSString *)musicName;

- (NSUInteger)sampleRate;
- (NSInteger)bitDepth;

- (NSTimeInterval)totalTimePlayed;
- (void)restartTotalTimeCalculation;
- (float)totalPercentPlayed;

- (NSUInteger)averageBitrate;
- (NSString *)trackCodec;
- (NSString *)trackInfo;

- (BOOL)isHD;
- (BOOL)isLossless;
- (BOOL)isVBR;

- (BOOL)isFading;

- (void)startHistogram;

- (void)abortConnections;
- (void)fadeOutWithDuration:(float)fadeDuration;


- (void)onPlaybackStateChanged:(BOOL)playing;

// userInfo for outside world
@property (nonatomic, strong) id userInfo;

@property (nonatomic, assign) BOOL           isEndlessStream;
@property (nonatomic, assign) NSTimeInterval startPosition;
@property (nonatomic, readonly) NSDictionary * tags; //album, artist, title, albumArtist, albumReleaseYear, trackNumber, trackTotal, discNumber, discTotal

@end

//sync callbacks
void __outputEndSyncVX(uint32_t handle, uint32_t channel, uint32_t data, void *user);
void __outputCrossFadeSync(uint32_t handle, uint32_t channel, uint32_t data, void *user);
void __outputStartSyncVX(uint32_t handle, uint32_t channel, uint32_t data, void *user);

@protocol VXBassSourceDelegate <NSObject>

- (void)sourceStartedPlaying:(VXBassSource *)source;
- (void)sourceIsAboutToFinish:(VXBassSource *)source;
- (void)sourceFinishedPlaying:(VXBassSource *)source;
- (void)sourceFinishedFadingOut:(VXBassSource *)source;
- (void)sourceReachedFadingPosition:(VXBassSource *)source;
- (void)sourceFinishedGaplessPlaying:(VXBassSource *)source;
- (void)sourceReachedPartialTransition:(VXBassSource *)source;
- (void)sourceTimedOutNeedsRecreate:(VXBassSource *)source needsAuth:(BOOL)needAuth;

- (void)sourceStartedNetworkActivity:(VXBassSource *)source;
- (void)sourceStoppedNetworkActivity:(VXBassSource *)source;

- (void)source:(VXBassSource*)source downloadProgress:(float) progress;//0...1

// these 3 download - related methods are called in bass secondary thread:
- (BOOL)source:(VXBassSource*)source willDownloadTotalLength:(NSUInteger)totalLength;
- (NSUInteger)source:(VXBassSource*)source didDownloadData:(NSData*)data atOffset:(NSUInteger)offset;
- (void)source:(VXBassSource*)source didEndDownloading:(BOOL)successfully;

- (BOOL)isPlaying;

@optional
- (BOOL)sourceShouldUseReplaygain:(VXBassSource*)source;
- (void)source:(VXBassSource*)source streamNameRecieved:(NSString*) stationName;
- (void)source:(VXBassSource*)source streamMetaInfoRecieved:(NSString*) metaInfo;
- (void)source:(VXBassSource*)source streamBitrateChanged:(float) bitrate;

- (void)source:(VXBassSource *)source didPauseWithReason:(NSString *)reason;
- (void)source:(VXBassSource *)source reportsInsufficientNetworkSpeedWithTimeout:(NSTimeInterval)timeout;


- (void)source:(VXBassSource *)source didBuildHistogram:(NSArray *)histogram toPosition:(float) position complete:(BOOL)isComplete;
- (NSUInteger)histogramLengthForSource:(VXBassSource *)source;

@end

@protocol VXBassPartialSourceProtocol <NSObject>

- (BOOL)reuseWithStartPosition:(NSTimeInterval)newStartPosition totalLength:(NSTimeInterval)newTotalLength;
- (void)updatePartialFileEndSync;
@property (nonatomic, assign) NSTimeInterval startPosition;



@end
