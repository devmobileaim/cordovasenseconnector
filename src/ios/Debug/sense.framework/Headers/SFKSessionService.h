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
 *  Before using SENSE, a user has to be enrolled. You can have a list of all the username already enrolled.
 *  If the user is already enrolled, he can create a session with the corresponding method.
 *  At anytime, you can see who is logged by using the userLogged.
 */
@interface SFKSessionService : NSObject

/**
 *  Enroll a user
 *
 *  @param username   Username of the user to enroll
 *  @param password   Password of the user to enroll
 *  @param code       This is the enrollment code given by the admin
 *  @param errorBlock The block will be called (on the main thread) at the end of the enrollment phase.
 *                    If there is no error returned, then  the enrollment passed and the user is enrolled.
 *                    You can check it by using the method userLogged or alreadyEnrolledUsers
 */
+ (void)enrollUsername:(NSString *)username password:(NSString *)password code:(NSString *)code errorBlock:(void(^)(NSError *))errorBlock;

/**
 *  Enroll a user and update its password
 *
 *  Use this method when the enrollUsername:password:code:errorBlock: return the error code _SFK_ERROR_CODE_PASSWORD_CHANGE_REQUIRED_.
 *
 *  @param username     Username of the user to enroll
 *  @param oldPassword  Old password of the user to enroll
 *  @param newPassword  New password of the user to enroll
 *  @param code         This is the enrollment code given by the admin
 *  @param errorBlock   The block will be called (on the main thread) at the end of the enrollment phase.
 *                      If there is no error returned, then  the enrollment passed and the user is enrolled.
 *                      You can check it by using the method userLogged or alreadyEnrolledUsers
 */
+ (void)enrollUsername:(NSString *)username oldPassword:(NSString *)oldPassword newPassword:(NSString *)newPassword code:(NSString *)code errorBlock:(void(^)(NSError *))errorBlock;

/**
 *  Enroll a user
 *
 *  @param username   Username of the user to enroll
 *  @param password   Password of the user to enroll
 *  @param pin        This is the enrollment code given by the admin
 *  @param errorBlock The block will be called (on the main thread) at the end of the enrollment phase.
 *                    If there is no error returned, then  the enrollment passed and the user is enrolled.
 *                    You can check it by using the method userLogged or alreadyEnrolledUsers
 *
 *  @deprecated in 3.14
 *
 *  @warning Please use enrollUsername:password:code:errorBlock: instead of this method.
 */
+ (void)enrollUsername:(NSString *)username password:(NSString *)password pin:(NSString *)pin errorBlock:(void(^)(NSError *))errorBlock __attribute__((deprecated("first deprecated in SENSE 3.14 - instead use enrollUsername:password:code:errorBlock:")));

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
 *  Create a session for the user on the server and update its password.
 *
 *  This is the method called for a log in.
 *
 *  Use this method when the createSessionWithUsername:password:errorBlock: return the error code _SFK_ERROR_CODE_PASSWORD_CHANGE_REQUIRED_.
 *
 *  @param username     Username of the user to authenticate
 *  @param oldPassword  Old password of the user to authenticate
 *  @param newPassword  New password of the user to authenticate
 *  @param errorBlock   The block will be called (on the main thread) at the end of the login phase.
 *                      If there is no error returned, then the login passed. You can check it by using the method userLogged.
 */
+ (void)createSessionWithUsername:(NSString *)username oldPassword:(NSString *)oldPassword newPassword:(NSString *)newPassword errorBlock:(void(^)(NSError *))errorBlock;

/**
 *  Open an existing session for the user on the server
 *
 *  This is the method called for the SSO log in. You can reuse the same session opened in another application only if the session
 *  is already open. You may know the current opened session with the alreadyLoggedInUsers method.
 *
 *  @param username   Username of the user to authenticate
 *  @param errorBlock The block will be called (on the main thread) at the end of the login phase.
 *                    If there is no error returned, then the login passed. You can check it by using the method userLogged.
 */
+ (void)openExistingSessionWithUsername:(NSString *)username errorBlock:(void(^)(NSError *))errorBlock;

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
 *  Unlocks an open session locked due to user inactivity.
 *
 *  After calling this method, the session is unlocked until _SFK_INACTIVITY_TIMEOUT_NOTIFICATION_ has been called again.
 *  This method must be called only when the application has authenticated the user, for example through fingerprint authentication.
 */
+ (void)unlockSession;

/**
 *  Know if a user can change his password client side
 *
 *  When the user has changed his password on the server. SENSE needs to change the password accordingly.
 *  @warning This method doesn't know if the password has been changed server side.
 *
 *  @param username   Username of the user
 */
+ (BOOL)canChangePassword:(NSString *)username;

/**
 *  Change the password client side
 *
 *  When the user has changed his password on the server. SENSE needs to change the password accordingly.
 *  @warning This method doesn't change the password server side.
 *
 *  @param oldPassword Password of the user before changing it
 *  @param newPassword Password of the user after
 *  @param username    Username of the user
 *  @param errorBlock  The block will be called (on the main thread) at the end of the change password phase.
 *                     If there is no error returned, then the password is changed and the user is logged in.
 *                     You can check it by using the method userLogged.
 */
+ (void)changePassword:(NSString *)oldPassword withNewPassword:(NSString *)newPassword forUsername:(NSString *)username errorBlock:(void(^)(NSError*))errorBlock;

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
 *  Returns the list of users already enrolled in SENSE on this device.
 *
 *  @return A list of string of the username already enrolled. The list is sorted by the time of the last time the user logged in successfully.
 *          The first object is the last one who logged in.
 */
+ (NSArray *)alreadyEnrolledUsers;

/**
 *  Returns the list of users already logged in SENSE on this application group.
 *
 *  A logged in user is a user who has a valid SENSE session activated currently. Typically in another application using SENSE.
 *  If a user is already logged in, you may use the openExistingSessionWithUsername:errorBlock: method to use the same session.
 *
 *  @return A list of string of the username already logged in.
 */
+ (NSArray *)alreadyLoggedInUsers;

/**
 *  Disenroll all the users enrolled on the device.
 */
+ (void)disenrollUsers;

/**
 *  Disenroll the user enrolled on the device.
 *
 *  @username Username contained in [alreadyEnrolledUsers]
 */
+ (void)disenrollUser:(NSString *)username;

@end
