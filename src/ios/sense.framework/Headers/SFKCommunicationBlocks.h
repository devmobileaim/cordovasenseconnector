//
//  SFKCommunicationConstants.h
//  sense-sdk-ios-framework
//
//  Created by Géraud de Laval on 08/05/14.
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Represent an NSError returned to be used in a block.
 *
 *  @param NSError The error set by a method
 */
typedef void (^SFKErrorBlock)(NSError *error);

/**
 *  Represent a NSData returned to be used in a block
 *
 *  @param NSData The data set by a method
 */
typedef void (^SFKStreamConnectionResponseBlock)(NSData *data);
