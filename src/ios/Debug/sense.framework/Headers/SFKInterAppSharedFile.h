//
//  SFKInterAppSharedFile.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 12.07.16.
//  Copyright © 2016 Sysmosoft. All rights reserved.
//

/**
 Provides an object able to decrypt a SENSE file type shared between applications by a SFKDocumentInteractionController.
 */
@interface SFKInterAppSharedFile : NSObject

///--------------------------------------
/// @name Opening an encrypted SENSE file
///--------------------------------------

/**
 Decrypt and return a SENSE shared file.
 
 @warning The SENSE file is deleted after decryption.
 
 @param url An URL targeting a encrypted local file.
 @return The decrypted file content.
 */
+ (NSData *)openSharedFileAtURL:(NSURL *)url;

@end
