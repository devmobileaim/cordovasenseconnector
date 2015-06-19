//
//  SFKKeychain.h
//  sense
//
//  Created by Marc-Henri Primault
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

/**
 *  A keychain is a set of key-value stored in a global dictionary.
 *  Each set is identified by an id.
 *  SFKeychain can access to whichever set designed by its id.
 */
@interface SFKKeychain : NSObject

/**
 *  Return all the keychain ids stored
 *
 *  @return All keychain ids stored
 */
+ (NSArray *)allIds;

/**
 *  Remove the keychain given by id
 *
 *  @param keychainId The id of the keychain
 */
+ (void)removeId:(NSString *)keychainId;

/**
 *  Instance which manage the keychain given by id
 *
 *  If the keychain exists, we retrieve it.
 *  If the keychain doesn't exist, we create a new one.
 *
 *  @param keychainId The id of the keychain
 *
 *  @return Keychain for the given id
 */
- (instancetype)initWithId:(NSString *)keychainId;

/**
 *  Persist a data under the given key
 *
 *  @param data The data to persist
 *  @param key  The key to retrieve the data
 */
- (void)persist:(NSData *)data forKey:(NSString *)key;

/**
 *  Load the data stored with the given key
 *
 *  @param key The key to retrieve the data
 *
 *  @return The data stored for the given key
 */
- (NSData *)loadKey:(NSString *)key;

/**
 *  Clear the data referenced by the given key
 *
 *  @param key The key referencing the data to clear
 */
- (void)clear:(NSString *)key;

/**
 *  Clear all the data into the keychain
 */
- (void)clearAll;

@end
