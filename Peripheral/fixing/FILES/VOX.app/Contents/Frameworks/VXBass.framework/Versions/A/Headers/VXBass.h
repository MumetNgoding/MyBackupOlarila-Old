//
//  VXBass2.h
//  VXBassMob
//
//  Created by Oleg Naumenko on 5/28/14.
//  Copyright (c) 2014 Coppertino. All rights reserved.
//

#import <AudioToolbox/AudioToolbox.h>
#import <Foundation/Foundation.h>
#import "VXBassSource.h"

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    #import "VXDeviceManagerIOS.h"
#else
    #import "VXDevicesManager.h"
    #import "VXBassSourceURL.h"
    #define USE_AU_DSP
#endif



#define VXBASS_ERROR_UNSUPPORTED_SAMPLE_FORMAT  6
#define VXBASS_ERROR_UNKNOWN_FILEFORMAT        41
#define VXBASS_ERROR_UNKNOWN_CODEC             44
#define VXBASS_ERROR_WRONG_HANDLE               5

typedef enum {
	VXBassStateStopped,
	VXBassStatePlaying,
	VXBassStatePaused,
} VXBassState;


typedef NSURL* (^AsyncURLResolver)(NSURL * inURL);
extern const NSString * kAsyncURLResolverBlock;
extern const NSString * VXBassForcePauseNotification;


@protocol VXBassPlayDelegate;

@interface VXBass : NSObject

// Hide parameterless init
- (id)init __attribute__((unavailable("init not available, use -initWithDelegate:")));
+ (id)new  __attribute__((unavailable("new  not available, use -initWithDelegate:")));

- (instancetype)initWithDelegate:(id<VXBassPlayDelegate>)delegate;

#pragma mark Sending items for playback

/** 
 * Set / play new track with given URL.
 * Use this to force playback of ordinary or partial track
 * Stops current playback, asynchronously loads new source, if not already, playURL version additionally starts playback from given position to a given length as soon as the source is loaded.
 * @param newURL:           URL of the file/stream that user wants to play
 * @param startPosition:    staring position, in seconds, of a track in terms of the whole audio file. 0 for ordinary tracks.
 * @param partialLength:    length of the track to play, in seconds, in terms of the whole audio file. 0 for ordinary tracks.
 * @param initialPosition:  position in track to set playhead at (only to restore app saved position). -1 to ignore.
 * @param userObject:       unique reference associated with given track (for example, track reference in playlist)
 * @param resolver:         block that will resolve newURL if nessesary, in VXBass loading thread, returning the actual media url.
**/

- (void)setURL:(NSURL*)newURL startPos:(float)startPosition length:(float)partialLength
  initPosition:(float)initialPosition userInfo:(id)userObject resolverBlock:(AsyncURLResolver)resolver;

/**
 * Partial setNextURL:userInfo: version.
 * Use this in delegate's bass:requiresNextURLForUserInfo: method:
 * to inform VXBass about next track to play when current one finishes.
 * this is required for gapless playback and for preliminary load of sources, and for seamless transition between tracks in .cue albums
 * @param nextURL:          URL of the file/stream to play next
 * @param startPosition:    staring position, in seconds, of a track in terms of the whole audio file
 * @param partialLength:    the length of the track to play, in seconds.
 * @param userObject:       unique id associated with given track URL (for example, track reference in playlist)
 **/

- (void)setNextURL:(NSURL *)nextURL startPos:(float)startPosition length:(float)partialLength
          userInfo:(id)userObject resolverBlock:(AsyncURLResolver)resolver;

# pragma mark Standart playback transport methods

- (void)play;
- (void)pause;
- (void)resume;
- (void)stop;

#pragma mark Sample Rate async setter, for explicit setting by user

- (void) setSampleRate:(NSInteger)bestSampleRate completionBlock: (void (^)())block;

# pragma mark - Spotify service

/**
 * Creates and configures Spotify SPTAudioStreamingController for login/manage purposes
 * used internally for Spotify audio playback
 * @param clientId - Spotify client ID
 **/

#if ((TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR) && !TARGET_OS_TV)
- (id) sptAudioStreamingControllerForClientId:(NSString*)clientId;
- (void) sptStopAudioStreamingController;
#endif


# pragma mark Equaliser

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

- (void) enablePeqWithParameters:(NSDictionary *) params;

@property (nonatomic, assign) BOOL manualEQGain;//when YES, uses @"preamp" param key to apply gain to EQ

#else // Mac OS X:

/**
 * Enables 10-band graphic equalizer and plugs it into output audio chain
 * @param preamp: gain/loss in dB, to compensate for level change as result of equalization
 * @param gains: Array of 10 NSNumber - wrapped float gains of corresponding frequency bands, in range +-12 dB
 * band center frequencies are: 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384 Hz
**/
 
- (void)enableEQWithPreamp:(float)preamp gains:(NSArray *)gains; //gains: 10 NSNumbers each +- 12.0f dB; preamp: float +- 15.0f dB

#endif

/**
  * Disables Graphic/Parametric EQ, unplugging it from audio output chain
**/

- (void)disableEQ;


#pragma mark Audio Level / Spectra

//Current Audio Level (0...1) (recent 20 ms!)
@property (nonatomic, readonly) float currentLevel;
@property (nonatomic, readonly) float currentLevelLog;


//enable/disable real-time spectrum analyser (beta!!!):
- (void) runAnalyserWithSpectraSize:(NSInteger)bandCount;
- (void) stopAnalyser;

//obtaining current audio spectrum:
@property (nonatomic, readonly) float * analyserData;
@property (nonatomic, readonly) NSInteger analyserDataSize;


@property (nonatomic, assign) NSInteger fftSize;
- (void) getFFT:(float*)fftBuffer ofSize:(NSInteger*)fftSize;


#pragma mark Histogram
/**
 * Enable histogram buider and return data by means of delegate method.
 * must be YES BEFORE playing source You want a histogram of!
 * histogram is then obtained through a delegate message.
 * level node interval is currently fixed to 1.0 s
 **/
@property (nonatomic, assign) BOOL shouldBuildHistograms;
@property (nonatomic, assign) NSUInteger histogramLength;//if set, forces "const length" histogram mode
@property (nonatomic, assign) float histogramInterval;//if set, forces "variable length" histogram mode, overrides histogramLength

/**
 * This method will fail if shouldBuildHistograms = YES;
 * Histogram builder starter, for currently playing source (will error on network endless streams)
 * @param barCount: desired total number of bars (level nodes) when finished
 * if (levels == nil) means histogram builder was unable to build histogram (probably resource is network, it's length is unknown)
 **/

//#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

- (BOOL) buildHistogramForURL:(NSURL*)url barCount:(NSInteger)count
                startPosition:(float)startPosition
                partialLength:(float)partialLenth
              completionBlock:(void (^)(float duration, NSArray * levels, BOOL finished)) completionBlock;
//#endif


#pragma mark Mac OS X: Audio Units Support

#ifdef USE_AU_DSP
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#else

/**
 * Enables Audio Unit processing (OS X only) for VXBass output
 **/
- (AUGraph) enableAU;
- (void) disableAU;

- (NSMutableDictionary *) addAU:(NSString *)auName
                     dictionary:(NSDictionary*)selectedDict
                     withPreset:(NSNumber *)aPreset
                   customPreset:(NSDictionary *)aCustomPreset
                     openEditor:(BOOL)openEditor;

- (BOOL) removeAUAtIndex:(NSUInteger)index;
- (BOOL) moveAUFromIndex:(NSUInteger)indexFrom toIndex:(NSUInteger)indexTo;
- (BOOL) enableDisableAUAtIndex:(NSUInteger)index enable:(BOOL)enable;
- (void) resetAUs;

- (BOOL) selectFactoryPreset:(AUPreset*)preset auNode:(AUNode)node;
- (BOOL) selectPreset:(NSDictionary*)presetDict auNode:(AUNode)node;
- (AudioUnit) unitForNode:(AUNode)node;

@property (nonatomic, readonly) NSArray * activeAudioUnits;
@property (nonatomic, readonly) BOOL audioUnitsEnabledAvailable;

#endif
#endif


#pragma mark Currently playing track info methods

/**
 * Methods for dealing with current track playback position, for LastFM
 **/

- (float)currentSourcePositionRatio;    //playback position in range 0...1 as ratio of track length
- (float)currentSourceTotalLength; // if == -1 >> probably, stream is endless
- (void) restartTotalTimeCalculation;
- (BOOL) resetPositionIfEndless;

#pragma mark Tag/Audio Property helpers

/**
 * Helper methods for getting data about audio files
 **/
- (float)totalDurationForFileURL:(NSURL*)url;
- (NSDictionary*)metadataForFileURL:(NSURL*)url;//currently returns nil!!!

/**
 * Description methods
 **/

- (NSString *)currentSourceDescription;
- (NSString *)currentSourceAdvancedDescription;
- (NSString *)advancedDescription;
- (NSString *)description;

- (void) setNetworkReachabilityStatus:(BOOL)reachable;

#pragma mark VXBass Properties

@property (nonatomic, strong) VXBassSource * currentSource;

@property (nonatomic, readonly, getter = isPlaying) BOOL playing;
@property (nonatomic, readonly, getter = isPending) BOOL pending; //YES between setURL/playURL and actual playback start ("Loading" state)
@property (nonatomic, readonly, getter = isStalled) BOOL stalled; //mixer is waiting for data (loading, etc)
@property (nonatomic, readonly) VXBassState         bassState;

/**
 * Tempo / time stretch functionality parameters
 **/
@property (nonatomic, assign) float             tempo; //(1 = natural, no tempo effect, 0.5 - halph the speed, 2.0 - twice the speed, 0 - means the same as 1)
@property (nonatomic, assign) BOOL              tempoEnable;
@property (nonatomic, assign) BOOL              tempoIsTurntableStyle;//alters pitch natural way along with tempo

/**
 * Tells VXBass to pause immediately when starting next track - for "Autopause" feature
 **/
@property (nonatomic, assign) BOOL              shouldAutopauseOnAdvance;

/**
 * Tells bass to try to load file into memory fully before playback (doesn't work for partial and large > 200 MB files
 **/
@property (nonatomic, assign) BOOL              shouldLoadLocalToMemory;

/**
 * Enables/disables Gap/overlap mode, which uses crossFadingTime to insert gap or overlap between tracks
 **/
@property (nonatomic, assign) BOOL              gapOverlapEnabled;
@property (nonatomic, assign) NSTimeInterval    crossFadingTime;

#pragma mark Current track properties
@property (nonatomic, readonly) float           bitrate;
@property (nonatomic, readonly) BOOL            isCurrentNetworkSource; //is source a network stream (SoundCloud, radio)
@property (nonatomic, readonly) BOOL            isCurrentEndlessStream; //is currently playing source endless stream (radio?)(may be not accurate!)
@property (nonatomic, readonly) double          downloadProgress; //(0.0...1.0)
@property (nonatomic, readonly) double          downloadStart;    //(0.0...1.0) start of downloaded data (0 if in the beginning of track)
@property (nonatomic, assign)   NSTimeInterval	currentPosition;  //playback position, seconds. == -1 tells caller to ignore position (temporery undefined state)
@property (nonatomic, readonly) NSTimeInterval	totalLength;      //length of current track in seconds
@property (nonatomic, readonly) NSTimeInterval	timeLeft;         //time left for current track to play, seconds
@property (nonatomic, readonly) NSString      * streamName;
@property (nonatomic, readonly) NSString      * streamTitle;
@property (nonatomic, readonly) NSString      * metaInfo;

#pragma mark Audio properties

@property (nonatomic, assign)   int         audioBufferSize;
@property (nonatomic, assign)   NSInteger   audioChannelsMode;
@property (nonatomic, readonly) NSInteger   audioOutputSampleRate;

@property (nonatomic, readonly) NSInteger   outputMixerSampleRate;


/**
 * Conversion quality for resampling:
 * 0 = linear interpolation, 1 = 8 point sinc interpolation, 2 = 16 point sinc interpolation,
 * 3 = 32 point sinc interpolation
 **/

@property (nonatomic, assign) NSInteger audioResampleAntiAliasing;

@property (nonatomic, assign) BOOL	audioUseSurroundSoundUpmix;
@property (nonatomic, assign) BOOL	audioFadeOnStateChangex; // enable smooth crossfade on play/pause and play_next/prev
@property (nonatomic, assign) BOOL  audioSynchronizeSampleRate;
@property (nonatomic, assign) BOOL  audioDeviceAutoHogingEnabled;

@property (nonatomic, assign) float volume;
@property (nonatomic, assign) BOOL	mute;
@property (nonatomic, assign) float channelsPan;

@property (nonatomic, assign) NSUInteger BS2BPreset;
@property (nonatomic, assign) BOOL		 BS2BLastPriority;

@property (nonatomic, assign) BOOL       replayGainFromTagsEnabled;


#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

@property (nonatomic, strong) VXDeviceManagerIOS   *deviceManager;

#else

@property (nonatomic, strong) VXDevicesManager   *deviceManager;

#endif

@end

// end of VXBass class ================================


#pragma mark VXBassPlayDelegate

@protocol VXBassPlayDelegate <NSObject>

// may happen both before OR after next track has started:
- (void)bass:(VXBass *)bass sourcePlayingFinished:(id)source percentPlayed:(float) percent userInfo:(id)userObject;

// may happen both before OR after previous track finished:
- (void)bass:(VXBass *)bass sourcePlayingStarted:(id)source userInfo:(id)userObject;

- (void)bassPlaybackStateChanged:(VXBass *)bass;

//set nextURL in this method:
- (void)bass:(VXBass *)bass requiresNextURLForUserInfo:(id)userObject;	// userObject is userInfo of previous (now finishing) track

//loading failure (will happen mostly while previous track is still playing)
//- (void)bass:(VXBass *)bass failedLoadingURL:(NSURL *)trackURL userInfo:(id)userObject error:(NSError *)error;


#pragma mark Optional

@optional

- (void)bass:(VXBass*)bass networkActivityStatusChanged:(BOOL)started;

//reports sucessfull seek as a result of setCurrentPosition, position may differ from what was set in setCurrentPosition
- (void)bass:(VXBass *)bass didSeekToPosition:(NSTimeInterval)position userInfo:(id)userObject;

- (void)bass:(VXBass *)bass url:(NSURL *)trackURL wasValidated:(BOOL)isValid bassError:(uint32_t)bassErrorCode userInfo:(id)userObject;
- (void)bass:(VXBass *)bass url:(NSURL *)trackURL isReportingLength:(NSTimeInterval)length userInfo:(id)userObject;
- (void)bass:(VXBass *)bass url:(NSURL *)trackURL isReportingBitrate:(NSInteger)bitrate userInfo:(id)userObject;

// report network resource states
- (void)bass:(VXBass *)bass isNetworkFileURL:(NSURL *)newURL userInfo:(id)userObject;
- (void)bass:(VXBass *)bass isEndlessStreamURL:(NSURL *)newURL userInfo:(id)userObject;
- (void)bass:(VXBass *)bass stationNameFound:(NSString *)stationName userInfo:(id)userObject;	// radio station name supplied
- (void)bass:(VXBass *)bass stationMetaInfoUpdated:(NSString *)metaInfo userInfo:(id)userObject;// radio station reports current track info (use streamTitle)

// trying to reload failed loads:
// may happen several times, return YES to continue trying to reload failed stream
- (BOOL)bass:(VXBass *)bass failedTryToReloadURL:(NSURL *)trackURL bassError:(uint32_t)bassErrorCode userInfo:(id)userObject;
//bass refuses to try to load this source anymore:
- (void)bass:(VXBass *)bass gaveUpTryingToReloadURL:(NSURL *)trackURL bassError:(uint32_t)bassErrorCode userInfo:(id)userObject;

- (void)bass:(VXBass *)bass reportsInsufficientNetworkSpeedInUserInfo:(id)userObject withTimeout:(NSTimeInterval)timeout;

// reports bass is pending waiting for minimum amount of data to download, or other timely operation (like switching device) is on:
- (void)bass:(VXBass *)bass sourceStallStateChange:(BOOL)isStalled;
- (void)bass:(VXBass *)bass source:(VXBassSource*)source stalledWithReason:(NSString*)reason;

- (void)bassReportsHeadphoneJackDisconnection:(VXBass *)bass; //Mac OS X: called when jack has beed disconnected from in-built sound card
- (void)bassReportsDeviceLayoutChange:(VXBass*)bass; //devices were added/removed or changed channel layout
- (void)bassReportsDeviceVolumeChange:(VXBass*)bass; //device volume has been changed externally
- (void)bassReportsDeviceChange:(VXBass*)bass; //device volume has been changed externally

- (void)bassDeviceWantsNextTrack:(VXBass*)bass;
- (void)bassDeviceWantsPrevTrack:(VXBass*)bass;

/**
 * Report histogram was built. This turns on/off by shouldBuildHistograms property.
 * @param histogram - array of levels that has been scanned so far
 * @param position - corresponding position in seconds (position of last level in histogram)
 * @param complete - is this histogram partial or complete (== do not wait for more)
 * @param userObject - source's unique id specified when calling setUrl:, playUrl: or setNextUrl:
 **/
- (void)bass:(VXBass *)bass didBuildHistogram:(NSArray*)histogram upToPosition:(float) position isComplete:(BOOL)complete userInfo:(id)userObject;

/*download (main thread)*/
- (void)bass:(VXBass *)bass downloadProgressChanged:(float)progress userInfo:(id)userObject; //progress in 0..1, called in main thread

/*cashing data*/
- (BOOL)bass:(VXBass *)bass shouldCacheDataForUserInfo:(id)userObject; //turn cashing on/off for individual track, called in background

// these 3 download - related methods are called in bass background pthreads:

- (BOOL)bass:(VXBass *)bass willStartDownloadOfLength:(NSUInteger)totalLength forUserInfo:(id)userObject; //download process began, prepare to copy data

- (void)bass:(VXBass *)bass didEndDownloadingSource:(VXBassSource*)source success:(BOOL)success forUserInfo:(id)userObject; //finished downloading, new version
- (NSUInteger)bass:(VXBass *)bass didDownloadData:(NSData*)data atOffset:(NSUInteger)offset forUserInfo:(id)userObject;//YES = tell VXBass to continue cashing

@end
