//
//  SFKNotificationName.h
//  sense-sdk-ios-framework
//
//  Created by Géraud de Laval
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  SFK_SESSION_WILL_TIMEOUT_NOTIFICATION
 *
 *  Sent by the framework when the session will end.
 *  This notification is sent during the life of the session.
 *  After this moment, the session has 1 minute until it closes.
 *  If the user has some data to save or to send to the server,
 *  it must be done at this time before that the SFK_SESSION_TIMEOUT_NOTIFICATION or
 *  SFK_OFFLINE_TIMEOUT_NOTIFICATION is fired.
 *
 *  If a server call is performed between SFK_SESSION_WILL_TIMEOUT_NOTIFICATION and
 *  SFK_SESSION_TIMEOUT_NOTIFICATION, this notification will be called again next time 
 *  the session is about to expire.
 */
extern NSString * const SFK_SESSION_WILL_TIMEOUT_NOTIFICATION;

/**
 *  SFK_SESSION_TIMEOUT_NOTIFICATION
 *
 *  Sent by the framework when the session ends.
 *  This notification is sent during the life of the session.
 *  After this moment, the user is not logged anymore, the communication is not allowed anymore and
 *  data stored in the secure storage are not accessible until the user reauthenticate himself.
 *  The user should be prompted with a login page to re authentify himself.
 */
extern NSString * const SFK_SESSION_TIMEOUT_NOTIFICATION;

/**
 *  SFK_OFFLINE_TIMEOUT_NOTIFICATION
 *
 *  Sent by the framework when the user has been using the application with the offline login for too long.
 *  This notification is sent during the life of the session.
 *  After this moment, the user is not logged anymore and
 *  data stored in the secure storage are not accessible until the user reauthenticate himself.
 *  The user should be prompted with a login page to re authentify himself.
 */
extern NSString * const SFK_OFFLINE_TIMEOUT_NOTIFICATION;

/**
 *  SFK_INACTIVITY_TIMEOUT_NOTIFICATION
 *
 *  Sent by the framework when the user has been inactive for a too long period.
 *  This notification is sent during the life of the session.
 *  After this moment, the user is still logged but the user should be prompted for his credentials before accessing the app.
 */
extern NSString * const SFK_INACTIVITY_TIMEOUT_NOTIFICATION;

/**
 *  SFK_BACKGROUND_DISABLE_NOTIFICATION
 *
 *  Sent by the framework when the application enters in background and the user has not the right 
 *  to use the application in background.
 *  This notification is sent during the life of the session.
 *  After this moment, the user is not logged anymore, the communication is not allowed anymore and
 *  data stored in the secure storage are not accessible until the user reauthenticate himself.
 *  The user should be prompted with a login page to re authentify himself.
 */
extern NSString * const SFK_BACKGROUND_DISABLE_NOTIFICATION;

/**
 *  SFK_UPDATE_AVAILABLE_NOTIFICATION
 *
 *  Sent by the framework when an update is available.
 *  The notification brings the ITMS link to call to update the application, it's accessible through the notification.object[@"uri"]
 *
 *  This notification is sent during the log in of a user (might also happen during an enrollment of the user).
 *  It can be fired by the [SFKUpdateService checkForUpdateWithError:] method too.
 */
extern NSString * const SFK_UPDATE_AVAILABLE_NOTIFICATION;

/**
 *  SFK_APPLICATION_UP_TO_DATE_NOTIFICATION
 *
 *  Sent by the framework when the [SFKUpdateService checkForUpdateWithError:] method is called and the application is up-to-date.
 */
extern NSString * const SFK_APPLICATION_UP_TO_DATE_NOTIFICATION;

/**
 *  SFK_PASSWORD_EXPIRATION_DATE_NOTIFICATION
 *
 *  Sent by the framework when the user password is about to expire.
 *  The notification brings the date of the expiration, it's accessible through the notification.object[@"date"];
 *
 *  This notification is sent during the log in of a user (might also happen during an enrollment of the user).
 */
extern NSString * const SFK_PASSWORD_EXPIRATION_DATE_NOTIFICATION;
