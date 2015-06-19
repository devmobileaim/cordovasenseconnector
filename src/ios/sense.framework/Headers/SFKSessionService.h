//
//  SFKSessionConnectionService.h
//  sense-sdk-ios-framework
//
//  Created by Géraud de Laval
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Managing everything related to enrollment and login.
 *  Before using Sense, a user has to be enrolled. You can have a list of all the username already enrolled.
 *  If the user is already enrolled, he can create a session with the corresponding method.
 *  At anytime, you can see who is logged by using the userLogged.
 */
@interface SFKSessionService : NSObject

/**
 *  Enroll a user
 *
 *  @param username   Username of the user to enroll
 *  @param password   Password of the user to enroll
 *  @param pin        This is the enrollment code given by the admin
 *  @param errorBlock The block will be called (on the main thread) at the end of the enrollment phase.
 *                    If there is no error returned, then  the enrollment passed and the user is enrolled.
 *                    You can check it by using the method userLogged or alreadyEnrolledUsers
 */
+ (void)enrollUsername:(NSString *)username password:(NSString *)password pin:(NSString *)pin errorBlock:(void(^)(NSError *))errorBlock;

/**
 *  Create a session for the user on the server
 *
 *  This is the method called for a log in.
 *
 *  @param username   Username of the user to authenticate
 *  @param password   Password of the user to authenticate
 *  @param errorBlock The block will be called (on the main thread) at the end of the login phase.
 *                    If there is no error returned, then the login passed. You can check it by using the method userLogged.
 */
+ (void)createSessionWithUsername:(NSString *)username password:(NSString *)password errorBlock:(void(^)(NSError *))errorBlock;

/**
 *  Re-authenticate a user 
 *  
 *  For example to re-authenticate a user after the inactivity timeout.
 *
 *  @param password   Password of the user to authenticate
 *  @param errorBlock The block will be called (on the main thread) at the end of the login phase.
 *                    If there is no error returned, then the login passed.
 */
+ (void)authenticate:(NSString *)password errorBlock:(void(^)(NSError *))errorBlock;

/**
 *  Change the password client side
 *
 *  When the user has changed his password on the server. Sense needs to change the password accordingly.
 *  @warning This method doesn't change the password server side.
 *
 *  @param oldPassword Password of the user before changing it
 *  @param newPassword Password of the user after
 *  @param username    Username of the user
 *  @param errorBlock  The block will be called (on the main thread) at the end of the change password phase.
 *                     If there is no error returned, then the password is changed and the user is logged in.
 *                     You can check it by using the method userLogged.
 */
+ (void)changePassword:(NSString *)oldPassword withNewPassword:(NSString *)newPassword forUsername:(NSString *)username  errorBlock:(void(^)(NSError*))errorBlock;

/**
 *  Create an offline session for the user on the device
 *
 *  Authenticate an enrolled user but without any communication with the server. 
 *  The authentification is done locally with data stored from the previous session.
 *  The user must be enrolled on device before to call this method.
 *
 *  @param username   Username of the user to authenticate
 *  @param password   Password of the user to authenticate
 *  @param errorBlock The block will be called (on the main thread) at the end of the login phase.
 *                    If there is no error returned, then  the login passed. You can check it by using the method userLogged.
 */
+ (void)createOfflineSessionWithUsername:(NSString *)username password:(NSString *)password errorBlock:(void(^)(NSError *))errorBlock;

/**
 *  Log out the current logged user.
 */
+ (void)logOut;

/**
 *  Returns the username who is logged in.
 *
 *  @return The username or an empty string if no one is logged.
 */
+ (NSString *)userLogged;

/**
 *  Returns the list of users already enrolled in sense on this device.
 *
 *  @return A list of string of the username already enrolled. The list is sorted by the time of the last time the user logged in successfully.
 *          The first object is the last one who logged in.
 */
+ (NSArray *)alreadyEnrolledUsers;

/**
 *  Disenroll all the users registered on the device.
 */
+ (void)disenrollUsers;

@end
