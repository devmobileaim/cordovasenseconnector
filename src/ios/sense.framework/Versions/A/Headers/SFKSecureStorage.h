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
 *  Define if the storage is available
 *
 *  @return YES if the storage is available otherwise NO
 */
+ (BOOL)isAvailable;

/**
 *  Manage the encryption of your files
 *
 *  The default store path is Documents/Storage.
 *  Secure Storage uses an autogenerate key and persist it to secure your files.
 *
 *  @return The secure storage otherwise returns nil
 */
+ (id<SFKSecureStorageProtocol>)secureStorage;

/**
 *  Manage the encryption of your files
 *
 *  @param key  Give the key to secure your files. The key must be 32 bytes long (256 Bits).
 *              If the key is not valid, Secure Storage uses an autogenerate key and persist it.
 *              If the key is nil, Secure Storage uses an autogenerate key and persist it.
 *  @param path Path where you want to store your files (absolute path).
 *              If the path is not an absolute path, Secure Storage uses the default path Documents/Storage.
 *              If the path is nil, Secure Storage uses the default path Documents/Storage.
 *
 *  @return The secure storage otherwise returns nil
 */
+ (id<SFKSecureStorageProtocol>)secureStorageWithKey:(NSData *)key withRootPath:(NSString *)path;

@end
