//
//  SFKRemoteNotification.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 20.07.15.
//  Copyright (c) 2015 Sysmosoft. All rights reserved.
//

@interface SFKRemoteNotification : NSObject

/*
 *  Determine if the remote notification registration is available. 
 *  This parameter is set in SENSE server under the security settings.
 *
 *  @return 1 if the remote notification registration is available otherwise 0
 */
+ (NSNumber *)isAvailable;

/*
 *  Register the token provided by the Apple Push Notification(APN) service in SENSE server.
 *
 *  @param token The APN token received for the application.
 *  @param error The error if the registration failed.
 *               You may specify nil for this parameter if you do not want the error information.
 *
 *  @return 1 if the registration successful otherwise 0.
 */
+ (NSNumber *)registerRemoteNotificationToken:(NSData *)token error:(NSError **)error;

@end
