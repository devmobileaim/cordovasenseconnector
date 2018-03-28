//
//  SFKAppExtensionService.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 08.12.17.
//  Copyright © 2017 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 * Share data securely between applications with a sharing app group container.
 */
@interface SFKSecureAppGroupSharingService : NSObject

/*
 * Create a secure object to encrypt and decrypt some data in an sharing app group container.
 *
 * @param keychainGroup The shared keychain group ID sets in the two applications
 * @param appGoup The shared app group ID sets in the two applications
 *
 * @return The instance of a secure app group sharing service
 */
- (instancetype)initWithKeychainGroup:(NSString *)keychainGroup appGroup:(NSString *)appGroup;

/*
 * Encrypt the data and save it to the shared app group.
 *
 * @param data The data to save
 * @param key The key associated to the data
 */
- (void)addData:(NSData *)data forKey:(NSString *)key;

/*
 * Decrypt the data associated to the key
 *
 * @param key The key associated to the data
 *
 * @return The data associated to the key otherwise nil
 */
- (NSData *)dataForKey:(NSString *)key;

/*
 * Remove the data associated to the key
 *
 * @param key The key associated to the data
 */
- (void)removeDataForKey:(NSString *)key;

@end
