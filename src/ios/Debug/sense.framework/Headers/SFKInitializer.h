//
//  SFKInitializer.h
//  sense-sdk-ios-framework
//
//  Created by Géraud de Laval on 15/05/14.
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SFKCommunicationBlocks.h"

/**
 *  This class is used to initialize the framework. For the moment,
 *  the developer can only set the URL of the SENSE security server.
 */
@interface SFKInitializer : NSObject

/**
 *  Generate or retrieve the unique instance of SFKInitializer
 *
 *  @return The unique instance of SFKInitializer
 */
+ (instancetype)sharedInitializer;

/**
 *  Set the hostname of the SENSE server
 *
 *  @param security   Represents the URL of the security server
 *  @param errorBlock An error is returned if the initialization doesn't work
 */
- (void)initializeSenseWithSecurityURL:(NSString *)security errorBlock:(SFKErrorBlock)errorBlock;

/**
 *  Set the hostname of the SENSE server
 *
 *  @param security   Represents the URL of the security server
 *  @param proxy      Represents the URL of the proxy server
 *  @param errorBlock An error is returned if the initialization doesn't work
 *
 *  @deprecated in 3.8
 *
 *  @warning The proxy URL is not required for the initialization. It is the SENSE server which provides the
 *           proxy URL now.
 */
- (void)initializeSenseWithSecurityURL:(NSString *)security proxyURL:(NSString *)proxy errorBlock:(SFKErrorBlock)errorBlock __attribute__((deprecated("first deprecated in SENSE 3.8 - instead use initializeSenseWithSecurityURL:errorBlock")));

@end
