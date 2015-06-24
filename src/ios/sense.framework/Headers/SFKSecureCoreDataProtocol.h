//
//  SFKSecureCoreDataProtocol.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 23.05.14.
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

@protocol SFKSecureCoreDataProtocol <NSObject>
@required

/**
 *  Return the persistent store coordinator that link the object model to the database file
 *
 *  @param managedObjectModel your object model which will link with the crypted database
 *  @param fileName           the name of your database file associated to your object model
 *
 *  @return The store coordinator linked to the model
 */
- (NSPersistentStoreCoordinator *)securePersistentStoreCoordinatorWithManagedObjectModel:(NSManagedObjectModel *)managedObjectModel databaseFileName:(NSString *)fileName;

/**
 *  Specify the size of the cipher pages for SQLCipher
 *
 *  @warning Call this method before [securePersistentStoreCoordinatorWithManagedObjectModel:databaseFileName](#)
 *
 *  For more information, [check the documentation](http://sqlcipher.net/sqlcipher-api/#cipher_page_size)
 *
 *  @param pageSize The size of the page
 */
- (void)setSQLCipherOptionsCipherPageSize:(NSInteger *)pageSize;

/**
 *  Specify the cipher for SQLCipher
 *
 *  @warning Call this method before [securePersistentStoreCoordinatorWithManagedObjectModel:databaseFileName](#)
 *
 *  For more information, [check the documentation](http://sqlcipher.net/sqlcipher-api/#cipher)
 *
 *  @param cipher The cipher will be used
 */
- (void)setSQLCipherOptionsCipher:(NSString *)cipher;

/**
 *  Specify the number of iteration for SQLCipher
 *
 *  @warning Call this method before [securePersistentStoreCoordinatorWithManagedObjectModel:databaseFileName](#)
 *
 *  For more information, [check the documentation](http://sqlcipher.net/sqlcipher-api/#kdf_iter)
 *
 *  @param iteration The number of iteration
 */
- (void)setSQLCipherOptionsKDFIter:(NSInteger *)iteration;

@end
