//
//  SFKSecureStorageFactory.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 23.05.14.
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

#import "SFKSecureStorageProtocol.h"

@interface SFKSecureStorage : NSObject

/**
 *  Define if the storage is available with a SENSE session.
 *
 *  @return YES if the storage is available otherwise NO
 */
+ (BOOL)isAvailable;

/**
 *  Manage the encryption of your files with a SENSE session.
 *
 *  Secure Storage uses the parameter given by the SENSE server
 *
 *  @param error Reason why the secure storage is nil. May be nil.
 *
 *  @warning Return a valid instance only if a SENSE session is opened.
 *
 *  @return The secure storage otherwise returns nil
 */
+ (id<SFKSecureStorageProtocol>)secureStorageWithError:(NSError **)error;

/**
 *  Manage the encryption of your files with a SENSE session.
 *
 *  @param path Path where you want to store your files (absolute path).
 *              If the path is not an absolute path or it is nil, Secure Storage uses the default path Documents/Storage.
 *
 *  @param error Reason why the secure storage is nil. May be nil.
 *
 *  @warning Return a valid instance only if a SENSE session is opened.
 *
 *  @return The secure storage otherwise returns nil
 */
+ (id<SFKSecureStorageProtocol>)secureStorageWithPath:(NSString *)path error:(NSError **)error;

/**
 *  Remove the stored files managed by [secureStorageWithError] or [secureStorage].
 *
 *  @param error Reason why the operation failed. May be nil.
 *
 *  @return YES if the operation succeed, otherwise NO.
 */
+ (BOOL)removeSecureStorageWithError:(NSError **)error;

/**
 *  Remove the stored files managed by [secureStorageWithKey:withRootPath:error] or [secureStorageWithKey:withRootPath].
 *
 *  @param path Path where you choose to store your files (absolute path).
 *              If the path is not an absolute path, Secure Storage uses the default path Documents/Storage.
 *              If the path is nil, Secure Storage uses the default path Documents/Storage.
 * 
 *  @param error Reason why the operation failed. May be nil.
 *
 *  @return YES if the operation succeed, otherwise NO.
 */
+ (BOOL)removeSecureStorageAtPath:(NSString *)path error:(NSError **)error;

/**
 *  Manage the encryption of your files with a SENSE session.
 *
 *  Secure Storage uses the parameter given by the SENSE server
 *
 *  @warning Return a valid instance only if a SENSE session is opened.
 *
 *  @deprecated in 3.16 Please migrate your data to use the SENSE provided key.
 *
 *  @return The secure storage otherwise returns nil
 */
+ (id<SFKSecureStorageProtocol>)secureStorage __attribute__((deprecated("first deprecated in SENSE 3.16 - instead use secureStorageWithError:")));

/**
 *  Manage the encryption of your files with a SENSE session.
 *
 *  @param key  Key to encrypt your files. The key must be 32 bytes long (256 Bits).
 *              If the key is not valid or it is nil, return an invalid instance.
 *  @param path Path where you want to store your files (absolute path).
 *              If the path is not an absolute path or it is nil, Secure Storage uses the default path Documents/Storage.
 *
 *  @param error Reason why the secure storage is nil. May be nil.
 *
 *  @warning Return a valid instance only if a SENSE session is opened.
 *
 *  @deprecated in 3.16 Please migrate your data to use the SENSE provided key.
 *
 *  @return The secure storage otherwise returns nil
 */
+ (id<SFKSecureStorageProtocol>)secureStorageWithKey:(NSData *)key withRootPath:(NSString *)path error:(NSError **)error __attribute__((deprecated("first deprecated in SENSE 3.16 - instead use secureStorageWithPath:error: and migrate your data to use the SENSE provided key")));

/**
 *  Manage the encryption of your files with a SENSE session.
 *
 *  @param key  Key to encrypt your files. The key must be 32 bytes long (256 Bits).
 *              If the key is not valid or it is nil, return an invalid instance.
 *  @param path Path where you want to store your files (absolute path).
 *              If the path is not an absolute path or it is nil, Secure Storage uses the default path Documents/Storage.
 *
 *  @warning Return a valid instance only if a SENSE session is opened.
 *
 *  @deprecated in 3.16 Please migrate your data to use the SENSE provided key.
 *
 *  @return The secure storage otherwise returns nil
 */
+ (id<SFKSecureStorageProtocol>)secureStorageWithKey:(NSData *)key withRootPath:(NSString *)path __attribute__((deprecated("first deprecated in SENSE 3.16 - instead use secureStorageWithPath:error: and migrate your data to use the SENSE provided key")));

@end
