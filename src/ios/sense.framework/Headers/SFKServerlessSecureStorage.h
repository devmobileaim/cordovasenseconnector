//
//  SFKServerlessSecureStorage.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 10.07.17.
//  Copyright © 2017 Sysmosoft. All rights reserved.
//

#import "SFKSecureStorageProtocol.h"

@interface SFKServerlessSecureStorage : NSObject

/**
 *  Define if the storage is available without a SENSE session.
 *
 *  @return YES if the storage is available otherwise NO
 */
+ (BOOL)isAvailable;

/**
 *  Manage the encryption of your files without a SENSE session.
 *
 *  @warning Return a valid instance only if a SENSE session is not opened.
 *
 *  @return The secure storage otherwise returns nil
 */
+ (id<SFKSecureStorageProtocol>)serverlessSecureStorage;

@end
