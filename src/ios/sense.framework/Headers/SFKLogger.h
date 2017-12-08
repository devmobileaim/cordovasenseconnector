//
//  SFKLogger.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 22.11.17.
//  Copyright © 2017 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, SFKLoggerLevel) {
    SFKLoggerLevelDisable,
    SFKLoggerLevelError,
    SFKLoggerLevelWarn,
    SFKLoggerLevelInfo,
    SFKLoggerLevelDebug,
    SFKLoggerLevelTrace
};

/**
 *  SENSE logger to handle logs with the server.
 */
@interface SFKLogger : NSObject


/**
 *  Generate or retrieve the unique instance of SFKLogger
 *
 *  @return The unique instance of SFKLogger
 */
+ (instancetype)instance;

/**
 *  Provide the SFKLoggerLevel corresponding to the string value
 *
 *  @param level String level should correspond to a SFKLoggerLevel
 *
 *  @return The SFKLoggerLevel corresponging to string value.
 *          If any found, return SFKLoggerLevelDisable.
 */
+ (SFKLoggerLevel)loggerLevelWithString:(NSString *)level;

/**
 *  Log the message to be retrieved by the server
 *
 *  @param message The message to log
 */
- (void)log:(NSString *)message;

/**
 *  Send the saved logs to the server
 */
- (void)sendLogs;

@end
