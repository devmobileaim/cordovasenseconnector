//
//  SFKDocumentInteractionController.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 04.07.16.
//  Copyright © 2016 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 Provides an UIDocumentInteractionController object containing a SENSE file URL. 
 Any application responding to the SENSE file type can open it with the [openSharedFileAtURL:]([SFKInterAppSharedFile openSharedFileAtURL:]) method.
 */
@interface SFKDocumentInteractionController : NSObject

///---------------------
/// @name Initialization
///---------------------

/**
 Creates and returns a new UIDocumentInteractionController object initialized with the specified URL
 
 The URL must represent a local file else 'nil' is returned.
 
 @param url An URL targeting a local file.
 @return A new document interaction controller object.
 */
+ (UIDocumentInteractionController *)interactionControllerWithURL:(NSURL *)url;

/**
 Creates and returns a new UIDocumentInteractionController object initialized with data and a file name.
 
 The data will be saved in a SENSE file according to the given file name. If the data or the file name is empty the method return 'nil'.
 
 @param data The data to share through a file.
 @param fileName The name for the shared file.
 @return A new document interaction controller object.
 */
+ (UIDocumentInteractionController *)interactionControllerWithData:(NSData *)data fileName:(NSString *)fileName;

@end
