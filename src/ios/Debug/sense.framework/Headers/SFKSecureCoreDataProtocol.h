//
//  SFKSecureCoreDataProtocol.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 23.05.14.
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

#import <CoreData/CoreData.h>

@protocol SFKSecureCoreDataProtocol <NSObject>
@required

/*
 *  Return the persistent store that link the coordinator to the database file
 *
 *  @param persistentStoreCoordinator The coordinator which will link with the crypted database
 *  @param storeURL                   The file location of the persistent store.
 *  @param options                    A dictionary containing key-value pairs that specify whether the store should be read-only.
 *                                    For key definitions use the value of SFKSQLCipherOptions or see the official documentation 
 *                                    of addPersistentStoreWithType:configuration:URL:options:error:
 *                                    This value may be nil.
 *  @param error                      If a new store cannot be created, upon return contains an instance of NSError that describes the problem.
 *
 *  @return The persistent store linked to the coordinator
 */
- (NSPersistentStore *)securePersistentStoreWithPersistentStoreCoordinator:(NSPersistentStoreCoordinator *)persistentStoreCoordinator URL:(NSURL *)storeURL options:(NSDictionary *)options error:(NSError **)error;

/*
 *  Return the persistent store coordinator that link the object model to the database file
 *
 *  @param managedObjectModel your object model which will link with the crypted database
 *  @param fileName           the name of your database file associated to your object model
 *
 *  @return The store coordinator linked to the model
 *
 *  @deprecated in 3.7
 *
 *  @warning Please use securePersistentStoreWithPersistentStoreCoordinator:URL:options:error: instead of this method.
 */
- (NSPersistentStoreCoordinator *)securePersistentStoreCoordinatorWithManagedObjectModel:(NSManagedObjectModel *)managedObjectModel databaseFileName:(NSString *)fileName __attribute__((deprecated("first deprecated in SENSE 3.7 - instead use securePersistentStoreWithPersistentStoreCoordinator:URL:options:error:")));

/*
 *  Specify the size of the cipher pages for SQLCipher
 *
 *  @warning Call this method before [securePersistentStoreCoordinatorWithManagedObjectModel:databaseFileName](#)
 *
 *  For more information, [check the documentation](http://sqlcipher.net/sqlcipher-api/#cipher_page_size)
 *
 *  @param pageSize The size of the page
 *
 *  @deprecated in 3.7
 *
 *  @warning Please use SFKSQLCipherOptionsCipherPageSize option key instead of this method.
 */
- (void)setSQLCipherOptionsCipherPageSize:(NSInteger *)pageSize __attribute__((deprecated("first deprecated in SENSE 3.7 - instead use SFKSQLCipherOptionsCipherPageSize option key")));

/*
 *  Specify the cipher for SQLCipher
 *
 *  @warning Call this method before [securePersistentStoreCoordinatorWithManagedObjectModel:databaseFileName](#)
 *
 *  For more information, [check the documentation](http://sqlcipher.net/sqlcipher-api/#cipher)
 *
 *  @param cipher The cipher will be used
 *
 *  @deprecated in 3.7
 *
 *  @warning Please use SFKSQLCipherOptionsCipher option key instead of this method.
 */
- (void)setSQLCipherOptionsCipher:(NSString *)cipher __attribute__((deprecated("first deprecated in SENSE 3.7 - instead use SFKSQLCipherOptionsCipher option key")));

/*
 *  Specify the number of iteration for SQLCipher
 *
 *  @warning Call this method before [securePersistentStoreCoordinatorWithManagedObjectModel:databaseFileName](#)
 *
 *  For more information, [check the documentation](http://sqlcipher.net/sqlcipher-api/#kdf_iter)
 *
 *  @param iteration The number of iteration
 *
 *  @deprecated in 3.7
 *
 *  @warning Please use SFKSQLCipherOptionsKDFIter option key instead of this method.
 */
- (void)setSQLCipherOptionsKDFIter:(NSInteger *)iteration __attribute__((deprecated("first deprecated in SENSE 3.7 - instead use SFKSQLCipherOptionsKDFIter option key")));

@end
