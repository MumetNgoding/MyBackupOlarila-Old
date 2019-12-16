//
//  NSString+Detector.h
//  UniversalDetector
//
//  Created by Ivan Ablamskyi on 13.11.12.
//
//

#import <Foundation/Foundation.h>

@interface NSString (Detector)

@property (nonatomic, readonly, copy) NSString *stringByAutoconvertingCharset;
- (NSString *)stringByAutoconvertingCharsetByReferenceToString:(NSString *)refString;
+ (CFStringRef)CFStringByAutodetecting:(const char *)chars CF_RETURNS_RETAINED;

@end