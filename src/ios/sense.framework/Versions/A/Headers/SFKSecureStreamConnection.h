//
//  SFKSecureStreamConnectionFactory.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 03.06.14.
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SFKSecureStreamConnectionProtocol.h"

__attribute__((deprecated("first deprecated in Sense 3.7 - Use NSURLConnection or NSURLSession")))
@interface SFKSecureStreamConnection : NSObject

/**
 *  Define if the communication is available
 *
 *  @return YES if the communication is available otherwise NO
 *
 *  @deprecated in 3.7
 *
 *  @warning All the communication should use the HTTP proxy. Please use NSURLConnection or NSURLSession.
 */
+ (BOOL)isAvailable;

/**
 *  Manage the communication between the Sense server and your application
 *
 *  @return The secure communication otherwise returns nil
 *
 *  @deprecated in 3.7
 *
 *  @warning All the communication should use the HTTP proxy. Please use NSURLConnection or NSURLSession.
 */
+ (NSObject<SFKSecureStreamConnectionProtocol> *)secureStreamConnection;

/**
 *  Manage the communication between the Sense server and your application
 *
 *  @param applicationRef The application reference given in the osmosys.properties
 *
 *  @return The secure communication otherwise returns nil
 *
 *  @deprecated in 3.7
 *
 *  @warning All the communication should use the HTTP proxy. Please use NSURLConnection or NSURLSession.
 */
+ (NSObject<SFKSecureStreamConnectionProtocol> *)secureStreamConnectionWithApplicationRef:(NSString *)applicationRef;

@end
