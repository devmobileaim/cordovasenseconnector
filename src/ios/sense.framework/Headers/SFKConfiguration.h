//
//  SFKConfiguration.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault
//  Copyright © 2016 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SFKConfiguration : NSObject

/**
 *  Read the content of the sense-config.properties and generate a dictionary with the file's content.
 *
 *  @return SENSE configuration keys
 */
+ (NSDictionary *)senseConfiguration;

@end
