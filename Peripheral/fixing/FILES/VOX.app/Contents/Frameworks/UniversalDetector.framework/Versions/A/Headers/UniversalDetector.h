#import <Foundation/Foundation.h>

@interface UniversalDetector:NSObject
{
	void *detectorPtr;
	NSString *charsetName;
	float confidence;
}

-(void)analyzeContentsOfFile:(NSString *)path;
-(void)analyzeData:(NSData *)data;
-(void)analyzeBytes:(const char *)data length:(int)len;
-(void)reset;

@property (nonatomic, readonly) BOOL done;
@property (nonatomic, readonly, copy) NSString *MIMECharset;
@property (nonatomic, readonly) NSStringEncoding encoding;
@property (nonatomic, readonly) float confidence;

@end
