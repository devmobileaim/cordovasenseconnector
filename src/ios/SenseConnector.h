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

#pragma mark session management
- (void)exitApp:(CDVInvokedUrlCommand*)command;
- (void)login:(CDVInvokedUrlCommand*)command;
- (void)enroll:(CDVInvokedUrlCommand*)command;
- (void)changePassword:(CDVInvokedUrlCommand*)command;
- (void)logout:(CDVInvokedUrlCommand*)command;

#pragma mark file system management
- (void)itemExistsAtPath:(CDVInvokedUrlCommand*)command;
- (void)createItemAtPath:(CDVInvokedUrlCommand*)command;
- (void)contentsAtPath:(CDVInvokedUrlCommand*)command;
- (void)moveItemAtPath:(CDVInvokedUrlCommand*)command;
- (void)removeItemAtPath:(CDVInvokedUrlCommand*)command;

#pragma mark async call
- (NSDictionary*)createJSON:(NSObject*)code withMessage:(NSString*)message;


@property (nonatomic, strong) NSString* loginCommmandId;

@end
