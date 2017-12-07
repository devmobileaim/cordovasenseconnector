//
//  SFKUpdateService.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault on 14.06.17.
//  Copyright © 2017 Sysmosoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SFKUpdateService : NSObject

/**
 *  Determine if the update service is available.
 *  An online opened session is required.
 *
 *  @return YES if the update service is available otherwise NO
 */
+ (BOOL)isAvailable;

/**
 *  Ask the server to know if an application update is available.
 *
 *  If an new version is available, the SFK_UPDATE_AVAILABLE_NOTIFICATION notification is fired with the ITMS link in the info dictionary.
 *  Otherwise, the notification SFK_APPLICATION_UP_TO_DATE_NOTIFICATION is fired.
 *
 *  @param error The error if there is not online opened session.
 *               You may specify nil for this parameter if you do not want the error information.
 *
 *  @return YES if the request to the server is executed otherwise NO.
 */
+ (BOOL)checkForUpdateWithError:(NSError **)error;

@end
