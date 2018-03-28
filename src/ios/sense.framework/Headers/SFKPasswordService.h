//
//  SFKPasswordService.h
//  sense-sdk-ios-framework
//
//  Created by jcaillet on 23.02.18.
//  Copyright © 2018 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Service providing functions to allow a user to manage his own password
 */
@interface SFKPasswordService : NSObject

/**
 * Determine if the user is allowed to change his password
 * This parameter is set in SENSE server under the security settings.
 */
+ (BOOL)isAvailable;

/**
 * Change the password for the current user.
 *
 * @param oldPassword The old password.
 * @param newPassword The new password.
 * @param errorBlock The error if the oldPassword is incorrect or if the session is not valid or if the user is not allowed to change its password.
 */
+ (void)changePassword:(NSString *)oldPassword newPassword:(NSString *)newPassword errorBlock:(void (^)(NSError *))errorBlock;

@end
