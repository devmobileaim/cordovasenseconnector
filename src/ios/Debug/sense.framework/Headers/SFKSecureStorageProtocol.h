//
//  SFKSecureStorageProtocol.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 23.05.14.
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SFKSecureStorageProtocol <NSObject>
@required

/**
 *  Returns a boolean value that indicates whether an item or directory exists at a specified path
 *
 *  @param path The path of the item or directory
 *
 *  @return YES if an item at the specified path exists or NO if the item
 *          does not exist or its existence could not be determined.
 */
- (BOOL)itemExistsAtPath:(NSString *)path;

/**
 *  Returns a boolean value that indicates whether a file or directory exists at a specified path
 *
 *  @param path        The path of the file or directory
 *  @param isDirectory Reference to a bool to know if the item is a directory or a file
 *
 *  @return YES if an item at the specified path exists or NO if the item
 *          does not exist or its existence could not be determined. isDirectory
 *          is set to YES if the path point to a directory, NO if is a file.
 */
- (BOOL)fileExistsAtPath:(NSString *)path isDirectory:(BOOL *)isDirectory;

/**
 *  Returns a dictionary with these keys: NSFileType, NSFileSize, NSFileModificationDate, NSFileCreationDate
 *
 *  @param path  The path of the item whose attributes you want
 *  @param error On input, a pointer to an error object. If an error occurs,
 *               this pointer is set to an actual error object containing the error information.
 *               You may specify nil for this parameter if you do not want the error information.
 *
 *  @return Dictionary with selected attributes
 */
- (NSDictionary *)attributesOfItemAtPath:(NSString *)path error:(NSError **)error;

/**
 *  Creates an item with the specified content at the given location
 *
 *  @param path     The path for the new item
 *  @param contents A data object containing the contents of the new item.
 *
 *  @return YES if the operation was successful, otherwise NO
 */
- (BOOL)createItemAtPath:(NSString *)path contents:(NSData *)contents;

/**
 *  Returns the contents of the item at the specified path
 *
 *  @param path The path of the item whose contents you want
 *
 *  @return An NSData object with the contents of the item. If some other
 *          error occurs, this method returns nil
 */
- (NSData *)contentsAtPath:(NSString *)path;

/**
 *  Performs a shallow search of the specified directory and returns the paths of any contained items
 *
 *  @param path  The path to the directory whose contents you want to enumerate
 *  @param error On input, a pointer to an error object. If an error occurs,
 *               this pointer is set to an actual error object containing the error information.
 *               You may specify nil for this parameter if you do not want the error information.
 *
 *  @return An array of NSString objects, each of which identifies an item, directory.
 *          Returns an empty array if the directory exists but has no contents. If an error occurs,
 *          this method returns nil and assigns an appropriate error object to the error parameter.
 */
- (NSArray *)contentsOfDirectoryAtPath:(NSString *)path error:(NSError **)error;

/**
 *  Performs a deep enumeration of the specified directory and returns the paths of all of the contained subdirectories.
 *
 *  @param path  The path of the directory to list
 *  @param error On input, a pointer to an error object. If an error occurs,
 *               this pointer is set to an actual error object containing the error information.
 *               You may specify nil for this parameter if you do not want the error information.
 *
 *  @return An array of NSString objects, each of which identifies an item, directory.
 *          Returns an empty array if the directory exists but has no contents. If an error occurs,
 *          this method returns nil and assigns an appropriate error object to the error parameter.
 */
- (NSArray *)subpathsOfDirectoryAtPath:(NSString *)path error:(NSError **)error;

/**
 *  Copy an item at path to a new path
 *
 *  @param srcPath The path of the item whose must be copy
 *  @param dstPath The new path of the item whose must be copied
 *  @param error   On input, a pointer to an error object. If an error occurs,
 *                 this pointer is set to an actual error object containing the error information.
 *                 You may specify nil for this parameter if you do not want the error information.
 *
 *  @return YES if the item was copied successfully.
 *          Otherwise NO if an error occurred, if you try to overwrite an existing item or if you try to move into his own subtree..
 */
- (BOOL)copyItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error;

/**
 *  Move an item at path to a new path
 *
 *  @param srcPath The path of the item whose must be moved
 *  @param dstPath The new path of the item whose must be moved
 *  @param error   On input, a pointer to an error object. If an error occurs,
 *                 this pointer is set to an actual error object containing the error information.
 *                 You may specify nil for this parameter if you do not want the error information.
 *
 *  @return YES if the item was moved successfully.
 *          Otherwise NO if an error occurred, if you try to overwrite an existing item or if you try to move into his own subtree.
 */
- (BOOL)moveItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error;

/**
 *  Removes the item or directory at the specified path
 *
 *  @param path  A path string indicating the item to remove.
 *  @param error On input, a pointer to an error object. If an error occurs,
 *               this pointer is set to an actual error object containing the error information.
 *               You may specify nil for this parameter if you do not want the error information.
 *
 *  @return YES if the item was removed successfully. Otherwise NO if an error occurred.
 */
- (BOOL)removeItemAtPath:(NSString *)path error:(NSError **)error;

/**
 *  Creates a directory at the specified path.
 *
 *  This method returns YES if all directories specified in 'path' were created and attributes were set.
 *  Directories are created with attributes specified by the dictionary passed to 'attributes'.
 *  If no dictionary is supplied, directories are created according to the umask of the process.
 *
 *  @param path                The path for the new directory
 *  @param createIntermediates If you pass 'NO' for createIntermediates, the directory must not exist at the time this call is made.
 *                             Passing 'YES' for 'createIntermediates' will create any necessary intermediate directories.
 *  @param attributes          Specific attributes for directory.
 *  @param error               On input, a pointer to an error object. If an error occurs,
 *                             this pointer is set to an actual error object containing the error information.
 *                             You may specify nil for this parameter if you do not want the error information.
 *
 *  @return YES if the directory was created successfully. Otherwise NO if an error occurred.
 */
- (BOOL)createDirectoryAtPath:(NSString *)path withIntermediateDirectories:(BOOL)createIntermediates attributes:(NSDictionary *)attributes error:(NSError **)error;

@end
