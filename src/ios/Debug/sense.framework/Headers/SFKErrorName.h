//
//  SFKErrorName.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//


/**
 *  SFK_ERROR_DOMAIN
 *
 *  The error domain of sense framework
 */
extern NSString *const SFK_ERROR_DOMAIN;

/**
 * SFK_ERROR_CODE_NSEXCEPTION
 *
 *  This error code means that sense catch an NSException.
 *  See the error descirption to learn why it failed.
 */
extern NSInteger const SFK_ERROR_CODE_NSEXCEPTION;

/**
 * SFK_ERROR_CODE_KEYCHAIN_ACCESS
 *
 *  This error code means that sense are not able to read the iOS Keychain.
 *  See the error descirption to learn why it failed.
 */
extern NSInteger const SFK_ERROR_CODE_KEYCHAIN_ACCESS;

/**
 *  SFK_ERROR_CODE_FRAMEWORK_NOT_INITIALIZED
 *
 *  This error code means that the SENSE framework
 *  is not initialized and you must initialize it first.
 */
extern NSInteger const SFK_ERROR_CODE_FRAMEWORK_NOT_INITIALIZED;

/**
 *  SFK_ERROR_CODE_DEVICE_JAILBROKEN
 *
 *  This error code means that the device is jailbroken.
 */
extern NSInteger const SFK_ERROR_CODE_DEVICE_JAILBROKEN;

/**
 *  SFK_ERROR_CODE_IDENTIFICATION
 *
 *  This error code means that the username or the shared secret are wrong.
 */
extern NSInteger const SFK_ERROR_CODE_IDENTIFICATION;

/**
 *  SFK_ERROR_CODE_AUTHENTICATION
 *
 *  This error code means that the username or the password are wrong.
 *  It is the sense server or the AD which invalided the authentication.
 */
extern NSInteger const SFK_ERROR_CODE_AUTHENTICATION;

/**
 *  SFK_ERROR_CODE_ACCESS_DENIED
 *
 *  This error code means that the user tries to use an invalid
 *  application because it has not the permission.
 */
extern NSInteger const SFK_ERROR_CODE_ACCESS_DENIED;

/**
 *  SFK_ERROR_CODE_APPLICATION_DISABLED
 *
 *  This error code means that the user is not allowed to use this application.
 */
extern NSInteger const SFK_ERROR_CODE_APPLICATION_DISABLED;

/**
 *  SFK_ERROR_CODE_USER_NOT_ENROLLED
 *
 *  This error code means that the user tries to login itself
 *  but it is not enrolled.
 */
extern NSInteger const SFK_ERROR_CODE_USER_NOT_ENROLLED;

/**
 *  SFK_ERROR_CODE_USER_ALREADY_ENROLLED
 *
 *  This error code means that the user tries to enroll itself
 *  but it is already enrolled.
 */
extern NSInteger const SFK_ERROR_CODE_USER_ALREADY_ENROLLED;

/**
 *  SFK_ERROR_CODE_USER_DISENROLLED
 *
 *  This error code means that the user is disenrolled.
 */
extern NSInteger const SFK_ERROR_CODE_USER_DISENROLLED;

/**
 *  SFK_ERROR_CODE_ACCOUNT_LOCKED
 *
 *  This error code means that the user account has just been locked.
 *  It is the sense server which locked the account.
 */
extern NSInteger const SFK_ERROR_CODE_ACCOUNT_LOCKED;

/**
 *  SFK_ERROR_CODE_ACCOUNT_ALREADY_LOCKED
 *
 *  This error code means that the user account is already locked.
 *  Almost the same as SFK_ERROR_CODE_ACCOUNT_LOCKED
 *  but the account was locked before the user tried. Basically they both have the same usage
 *  It is the sense server which locked the account.
 */
extern NSInteger const SFK_ERROR_CODE_ACCOUNT_ALREADY_LOCKED;

/**
 *  SFK_ERROR_CODE_SESSION
 *
 *  This error code means that the session is locked.
 *  It is the sense server which locked the session.
 */
extern NSInteger const SFK_ERROR_CODE_SESSION;

/**
 *  SFK_ERROR_CODE_CHANGE_PASSWORD_NOT_ALLOWED
 *
 *  This error code means that the change password is not allowed
 *  because it is not mandatory at this time.
 *  Use [SFKSessionService canChangePassword:] to know if you need to change the password.
 */
extern NSInteger const SFK_ERROR_CODE_CHANGE_PASSWORD_NOT_ALLOWED;

/**
 *  SFK_ERROR_CODE_PASSWORD_NOT_CHANGED
 *
 *  This error code means that the password did not change
 *  when the user try to change it on the device.
 */
extern NSInteger const SFK_ERROR_CODE_PASSWORD_NOT_CHANGED;

/**
 *  SFK_ERROR_CODE_OFFLINE_NOT_ALLOWED
 *
 *  This error code means that the user tries to login in offline
 *  mode but the user has not the permission to do that.
 */
extern NSInteger const SFK_ERROR_CODE_OFFLINE_NOT_ALLOWED;

/**
 *  SFK_ERROR_CODE_OFFLINE_CORRUPTED
 *
 *  This error code means that the information needed for the offline login are corrupted.
 *  The user has to login online before being able to login offline again.
 */
extern NSInteger const SFK_ERROR_CODE_OFFLINE_CORRUPTED;

/**
 *  SFK_ERROR_CODE_DEVICE_LOCKED
 *
 *  This error code means that the device is locked.
 *  It is the sense server which locked the device.
 */
extern NSInteger const SFK_ERROR_CODE_DEVICE_LOCKED;

/**
 *  SFK_ERROR_CODE_DEVICE_NOT_COMPLIANT
 *
 *  This error code means that the device is not compliant
 *  with the rules established by the administrator.
 */
extern NSInteger const SFK_ERROR_CODE_DEVICE_NOT_COMPLIANT;

/**
 *  SFK_ERROR_CODE_SERVER_ERROR
 *
 *  This error code represents a generic server error.
 */
extern NSInteger const SFK_ERROR_CODE_SERVER_ERROR;

/**
 *  SFK_ERROR_CODE_NETWORK
 *
 *  This error code means that the network is not available.
 */
extern NSInteger const SFK_ERROR_CODE_NETWORK;

/**
 *  SFK_ERROR_CODE_SERVER_UNREACHABLE
 *
 *  This error code means that the server is not reachable or
 *  the URLs are wrongly set.
 */
extern NSInteger const SFK_ERROR_CODE_SERVER_UNREACHABLE;

/**
 *  SFK_ERROR_CODE_NO_PROXY_URL_AVAILABLE
 *
 *  This error code means that the SENSE SDK
 *  does not have a valid proxy URL provided by the SENSE server.
 */
extern NSInteger const SFK_ERROR_CODE_NO_PROXY_URL_AVAILABLE;

/**
 *  SFK_ERROR_CODE_REPONSE_UNKNOW
 *
 *  This error code means that the reponse from the server
 *  it unknows for the device.
 */
extern NSInteger const SFK_ERROR_CODE_REPONSE_UNKNOW;

/**
 *  SFK_ERROR_CODE_XML_FORMAT
 *
 *  This error code means that the XML communication between
 *  the server and the device is corrupted.
 */
extern NSInteger const SFK_ERROR_CODE_XML_FORMAT;

/**
 *  SFK_ERROR_CODE_REQUEST_TIMEOUT
 *
 *  This error code means that the request is out of time
 *  to have a reponse from the server.
 */
extern NSInteger const SFK_ERROR_CODE_REQUEST_TIMEOUT;

/**
 *  SFK_ERROR_CODE_REQUEST_CANCELED
 *
 *  This error code means that the request is canceled.
 */
extern NSInteger const SFK_ERROR_CODE_REQUEST_CANCELED;

/**
 *  SFK_ERROR_CODE_OFFLINE_LOGIN_BLOCKED
 *
 *  This error code means that the user can't login in offline mode again.
 *  The reason is that he tried with a wrong password too much times.
 */
extern NSInteger const SFK_ERROR_CODE_OFFLINE_LOGIN_BLOCKED;

/**
 *  SFK_ERROR_CODE_MAX_ACCESS_TRY
 *
 *  This error code means that the user can't use the same sesion in online mode.
 *  The reason is that he tried with a wrong password too much times.
 *  The user must create a new session.
 */
extern NSInteger const SFK_ERROR_CODE_MAX_ACCESS_TRY;

/**
 *  SFK_ERROR_CODE_LOCATION_REQUIRED
 *
 *  This error code means that the user can't log in.
 *  The reason is that the location is not enable to the application.
 *  The user must authorize the location for the application to log in.
 *  This parameter is required by the administrator.
 */
extern NSInteger const SFK_ERROR_CODE_LOCATION_REQUIRED;

/**
 *  SFK_ERROR_CODE_USER_SESSION_CLOSED
 *
 *  This error code means that the user session is closed.
 *  You must create a new user session.
 */
extern NSInteger const SFK_ERROR_CODE_USER_SESSION_CLOSED;

/**
 *  SFK_ERROR_CODE_NOT_AVAILABLE_OFFLINE
 *
 *  This error code means that the service is not available
 *  with an offline session.
 */
extern NSInteger const SFK_ERROR_CODE_NOT_AVAILABLE_OFFLINE;

/**
 *  SFK_ERROR_CODE_SERVICE_NOT_ALLOWED
 *
 *  This error code means that the service is not allowed
 *  by the administrator.
 */
extern NSInteger const SFK_ERROR_CODE_SERVICE_NOT_ALLOWED;

/**
 *  SFK_ERROR_CODE_STORAGE_INDEX_WRITTING
 *
 *  This error code means that index file, representing the storage,
 *  is not editable.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_INDEX_WRITTING;

/**
 *  SFK_ERROR_CODE_STORAGE_INDEX_READING
 *
 *  This error code means that index file, representing the storage,
 *  is not readable.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_INDEX_READING;

/**
 *  SFK_ERROR_CODE_STORAGE_INDEX_CLOSED
 *
 *  This error code means that index file, representing the storage,
 *  is used with a closed session. A new instance of SFKSecureStorage is required.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_INDEX_CLOSED;

/**
 *  SFK_ERROR_CODE_STORAGE_COPY_ITEM
 *
 *  This error code means that the copying of a new item failed.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_COPY_ITEM;

/**
 *  SFK_ERROR_CODE_STORAGE_MOVE_ITEM
 *
 *  This error code means that the moving of a new item failed.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_MOVE_ITEM;

/**
 *  SFK_ERROR_CODE_STORAGE_UNKNOW_ITEM
 *
 *  This error code means that the application tries to handle
 *  an unknow item.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_UNKNOW_ITEM;

/**
 *  SFK_ERROR_CODE_STORAGE_OVERWRITE_FILE
 *
 *  This error code means that the application tries to overwrite
 *  an exisiting file with a item.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_OVERWRITE_FILE;

/**
 *  SFK_ERROR_CODE_STORAGE_OVERWRITE_FOLDER
 *
 *  This error code means that the application tries to overwrite
 *  an exisiting folder with a item.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_OVERWRITE_FOLDER;

/**
 *  SFK_ERROR_CODE_STORAGE_OVERWRITE_PATH
 *
 *  This error code means that the application tries to overwrite
 *  an exisiting path with another path.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_OVERWRITE_PATH;

/**
 *  SFK_ERROR_CODE_STORAGE_INTERNAL_PATH
 *
 *  This error code means that the application tries to move
 *  a path into its own path.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_INTERNAL_PATH;

/**
 *  SFK_ERROR_CODE_STORAGE_REMOVE_FOLDER
 *
 *  This error code means that the application tries to remove
 *  a folder but it is forbidden.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_REMOVE_FOLDER;

/**
 *  SFK_ERROR_CODE_STORAGE_INTERMEDIATE_FOLDER
 *
 *  This error code means that the application tries to create
 *  an intermediate folder but it is forbidden.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_INTERMEDIATE_FOLDER;

/**
 *  SFK_ERROR_CODE_STORAGE_IS_NOT_FOLDER
 *
 *  This error code means that the application tries to handle
 *  a folder but the item is not a folder.
 */
extern NSInteger const SFK_ERROR_CODE_STORAGE_IS_NOT_FOLDER;
