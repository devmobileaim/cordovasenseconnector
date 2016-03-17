//
//  SenseConnector.h
//  SenseConnector
//
//  Created by aimservices on 19.05.14.
//
//

#import <Cordova/CDV.h>

#define SECURITY_SERVER_URL    @"${sec-server-url}"

@interface SenseConnector : CDVPlugin
- (void)exitApp:(CDVInvokedUrlCommand*)command;
- (void)login:(CDVInvokedUrlCommand*)command;
- (void)enroll:(CDVInvokedUrlCommand*)command;
- (void)changePassword:(CDVInvokedUrlCommand*)command;

- (NSDictionary*)createJSON:(NSObject*)code withMessage:(NSString*)message;


@property (nonatomic, strong) NSString* loginCommmandId;

@end
