//
//  SenseConnector.m
//  SenseConnector
//
//  Created by aimservices on 19.05.14.
//
//

#import "SenseConnector.h"
#import <sense/SFKInitializer.h>
#import <sense/SFKSessionService.h>
#import <sense/SFKNotificationName.h>
#import <sense/SFKSecureStorage.h>

const int LOGIN_OK               = 0;
const int LOGIN_PINCODE_REQUIRED = 1;
const int LOGIN_UPDATE_AVAILABLE = 2;
const int SESSION_EXPIRED        = 3;
const int SESSION_LOCKED         = 4;

typedef void (^LoginBlock)(NSError* error, SenseConnector* connector, CDVInvokedUrlCommand* command, NSString* updateUri);
LoginBlock loginCallback = ^(NSError* error, SenseConnector* connector, CDVInvokedUrlCommand* command, NSString* updateUri) {
    NSLog(@"\t%@", @"Inside callback");
    CDVPluginResult* loginResult = nil;
    if (error) {
        NSString* errorMsg = [[error userInfo] objectForKey:@"NSLocalizedDescription"];
        NSString* message = [NSString stringWithFormat:@"Unable to login.\nError: %@", errorMsg];
        NSLog(@"\t%@", message);

        NSDictionary* json = [connector createJSON:@"ERR_LOGIN_FAILED" withMessage:errorMsg];
        loginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:json];
    } else {
        NSString* message = @"Successfully logged-in.";
        NSLog(@"\t%@", message);
        NSDictionary* json;
        if(updateUri == nil){
            NSString* message = @"No update available, sending LOGIN_OK";
            NSLog(@"\t%@", message);
            json = [connector createJSON:[NSNumber numberWithInt:LOGIN_OK] withMessage:nil];
        } else {
            NSString* message = [NSString stringWithFormat:@"Update available at %@, sending LOGIN_UPDATE_AVAILABLE", updateUri];
            NSLog(@"\t%@", message);
            json = [connector createJSON:[NSNumber numberWithInt:LOGIN_UPDATE_AVAILABLE] withMessage:updateUri];
        }
        loginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:json];
        [loginResult setKeepCallbackAsBool:TRUE];

    }
    connector.loginCommmandId = command.callbackId;
    [connector.commandDelegate sendPluginResult:loginResult callbackId:command.callbackId];
};

@interface SenseConnector ()

    @property (nonatomic, assign) BOOL sessionReady;
    @property (nonatomic, strong) NSString* updateUri;

    - (BOOL)isEnrolled:(NSString*)username;
    - (void)privacySettings;
    - (void)clearTraces;
    - (NSString*)decodeB64:(NSString*)value;

@end

@implementation SenseConnector

- (void)pluginInitialize {
    NSLog(@"SenseConnector plugin initialized");
    self.sessionReady = NO;

    [[SFKInitializer sharedInitializer] initializeSenseWithSecurityURL:SECURITY_SERVER_URL errorBlock:^(NSError* error) {
        if (error) {
            NSString* errorMsg = [[error userInfo] objectForKey:@"NSLocalizedDescription"];
            NSString* message = [NSString stringWithFormat:@"Something went wrong here.\nError: %@", errorMsg];
            NSLog(@"\t%@", message);
        }
    }];

    /* SENSE:
     * When a user authenticates himself on a server, Sense framework will receive the security settings set by the admin.
     * By registering to these two notifications, you will know when the inactivity timers fire
     * and when the session is over. You have to implement how these notifications are handled on your application.
     */
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(displayInactivityVC) name:SFK_INACTIVITY_TIMEOUT_NOTIFICATION object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(sessionTimeout) name:SFK_OFFLINE_TIMEOUT_NOTIFICATION object:nil];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateAvailable:) name:SFK_UPDATE_AVAILABLE_NOTIFICATION object:nil];
}

- (void)displayInactivityVC {
    NSLog(@"Sense inactivity time-out notification");
    NSDictionary* json = [self createJSON:[NSNumber numberWithInt:SESSION_LOCKED] withMessage:nil];
    [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:json] callbackId:self.loginCommmandId];
}

- (void)sessionTimeout {
    NSLog(@"Sense session time-out notification");
    NSDictionary* json = [self createJSON:[NSNumber numberWithInt:SESSION_EXPIRED] withMessage:nil];
    [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:json] callbackId:self.loginCommmandId];
}

- (void)updateAvailable:(NSNotification *)notification {
    NSLog(@"Update available notification");
    NSString* uri = notification.object[@"uri"];
    self.updateUri = uri;
}

- (BOOL)isEnrolled:(NSString*)username {
    NSArray* enrolledUsers = [SFKSessionService alreadyEnrolledUsers];
    return ([enrolledUsers containsObject:username]);
}

- (NSDictionary*)createJSON:(NSObject*)code withMessage:(NSString*)message {
    NSString* codeStr = [NSString stringWithFormat:@"%@", code];
    NSDictionary* jsonObj = [[NSDictionary alloc] initWithObjectsAndKeys:codeStr, @"code", nil];
    if (message != nil) {
        jsonObj = [NSMutableDictionary dictionaryWithDictionary:jsonObj];
        [jsonObj setValue:message forKey:@"message"];
    }
    return jsonObj;
}

- (void)updateApp:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = [command argumentAtIndex:0];
    NSString* url = [arguments valueForKey:@"url"];
    NSLog(@"Updating application from %@", url);

    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Application update"
                                                    message:[NSString stringWithFormat:@"Url: %@", url]
                                                   delegate:nil
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];
    [alert show];

    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
    self.updateUri = nil;
    NSLog(@"App should be updating now");
}

- (void)exitApp:(CDVInvokedUrlCommand*)command {
    exit(0);
}

- (void)login:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = [command argumentAtIndex:0];
    NSString* username = [arguments valueForKey:@"username"];
    NSString* password = [self decodeB64:[arguments valueForKey:@"password"]];

    NSLog(@"Logging in to Sense\n%@", [NSString stringWithFormat:@"Command: %@", command]);
    if ([self isEnrolled:username]) {
        // call createSessionWithUsername only if deviced is enrolled
        [SFKSessionService createSessionWithUsername:username password:password errorBlock:^(NSError* error){
            if (error == nil) {
                self.sessionReady = YES;
            }

            loginCallback(error, self, command, self.updateUri);
        }];
    } else {
        NSString* message = @"Unable to login.\nError: You need to enroll a user first";
        NSLog(@"\t%@", message);

        NSDictionary* json = [self createJSON:[NSNumber numberWithInt:LOGIN_PINCODE_REQUIRED] withMessage:nil];
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:json] callbackId:command.callbackId];
    }
}

- (void)enroll:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = [command argumentAtIndex:0];
    NSString* username = [arguments valueForKey:@"username"];
    NSString* password = [self decodeB64:[arguments valueForKey:@"password"]];
    NSString* pincode = [arguments valueForKey:@"pincode"];
    NSLog(@"Logging in to Sense\n%@", [NSString stringWithFormat:@"Command: %@", command]);
    [SFKSessionService enrollUsername:username password:password pin:pincode errorBlock:^(NSError* error) {
        if (error == nil) {
            self.sessionReady = YES;
        }

        loginCallback(error, self, command, self.updateUri);
    }];
}

- (void)dispose
{
    // @todo: [self privacySettings];
    [super dispose];
}

- (void)changePassword:(CDVInvokedUrlCommand*)command {
    NSDictionary* arguments = [command argumentAtIndex:0];
    NSString* username = [arguments valueForKey:@"username"];
    NSString* oldPassword = [self decodeB64:[arguments valueForKey:@"oldPassword"]];
    NSString* newPassword = [self decodeB64:[arguments valueForKey:@"newPassword"]];
    NSLog(@"Changing password \n%@", [NSString stringWithFormat:@"Command: %@", command]);
    [SFKSessionService changePassword:oldPassword withNewPassword:newPassword forUsername:username errorBlock:^(NSError* error) {
        if (error == nil) {
            self.sessionReady = YES;
        }

        loginCallback(error, self, command, self.updateUri);
    }];
}

#pragma mark file system management
- (id<SFKSecureStorageProtocol>)secureStorage{
    if([SFKSecureStorage isAvailable] && self.sessionReady) {
        return [SFKSecureStorage secureStorage];
    }
    
    return nil;
}

- (void)itemExistsAtPath:(CDVInvokedUrlCommand*)command{
    NSDictionary* arguments = [command argumentAtIndex:0];
    NSString* path = [arguments valueForKey:@"path"];
    
    id<SFKSecureStorageProtocol> secureStorage = [self secureStorage];
    
    if (secureStorage) {
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:[secureStorage itemExistsAtPath:path]] callbackId:command.callbackId];
    }else{
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR] callbackId:command.callbackId];
    }
}

- (void)createItemAtPath:(CDVInvokedUrlCommand*)command{
    NSDictionary* arguments = [command argumentAtIndex:0];
    NSString* path = [arguments valueForKey:@"path"];
    NSData* data = [[NSData alloc] initWithBase64EncodedString:[arguments valueForKey:@"data"] options:0];
    
    id<SFKSecureStorageProtocol> secureStorage = [self secureStorage];
    
    if (secureStorage) {
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:[secureStorage createItemAtPath:path contents:data]] callbackId:command.callbackId];
    }else{
      [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR] callbackId:command.callbackId];
    }
}

- (void)contentsAtPath:(CDVInvokedUrlCommand*)command{
    NSDictionary* arguments = [command argumentAtIndex:0];
    NSString* path = [arguments valueForKey:@"path"];
    
    id<SFKSecureStorageProtocol> secureStorage = [self secureStorage];
    
    if (secureStorage) {
        NSData* data = [secureStorage contentsAtPath:path];
        
        if (data) {
            NSString* dataAsString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:dataAsString] callbackId:command.callbackId];
            
        }else{
            [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR] callbackId:command.callbackId];
        }
        
    }else{
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR] callbackId:command.callbackId];
    }
}

- (void)moveItemAtPath:(CDVInvokedUrlCommand*)command{
    NSDictionary* arguments = [command argumentAtIndex:0];
    NSString* currentPath  = [arguments valueForKey:@"currentPath"];
    NSString* newPath  = [arguments valueForKey:@"newPath"];
    
    id<SFKSecureStorageProtocol> secureStorage = [self secureStorage];
    
    if (secureStorage) {
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:[secureStorage moveItemAtPath:currentPath toPath:newPath error:nil]] callbackId:command.callbackId];
    }else{
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR] callbackId:command.callbackId];
    }
    
}
- (void)removeItemAtPath:(CDVInvokedUrlCommand*)command{
    NSDictionary* arguments = [command argumentAtIndex:0];
    NSString* path = [arguments valueForKey:@"path"];
    
    id<SFKSecureStorageProtocol> secureStorage = [self secureStorage];
    
    if (secureStorage) {
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:[secureStorage removeItemAtPath:path error:nil]] callbackId:command.callbackId];
    }else{
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR] callbackId:command.callbackId];
    }
}

- (void)privacySettings {
    // Clearing cache Memory
    [[NSUserDefaults standardUserDefaults] setInteger:0 forKey:@"WebKitCacheModelPreferenceKey"];
    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:@"WebKitOfflineWebApplicationCacheEnabled"];
    [[NSUserDefaults standardUserDefaults] setObject:@"" forKey:@"WebKitLocalStorageDatabasePathPreferenceKey"];
    [[NSUserDefaults standardUserDefaults] setObject:@"" forKey:@"WebKitDiskImageCacheSavedCacheDirectory"];
    [[NSUserDefaults standardUserDefaults] setObject:@"" forKey:@"WebDatabaseDirectory"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    [[NSURLCache sharedURLCache] removeAllCachedResponses];
    [[NSURLCache sharedURLCache] setMemoryCapacity:0];
    
    [self clearTraces];
}

- (void)clearTraces {
    if ([self.webView isKindOfClass:[UIWebView class]]) {
        [(UIWebView*)self.webView stringByEvaluatingJavaScriptFromString:@"localStorage.clear();"];
        [(UIWebView*)self.webView stringByEvaluatingJavaScriptFromString:@"sessionStorage.clear();"];
    }
    
    // Deleting all the cookies
    for(NSHTTPCookie *cookie in [[NSHTTPCookieStorage sharedHTTPCookieStorage] cookies]) {
        [[NSHTTPCookieStorage sharedHTTPCookieStorage] deleteCookie:cookie];
    }
}

- (NSString*)decodeB64:(NSString*)value {
    NSData* data = [[NSData alloc] initWithBase64EncodedString:value options:0];
    NSString* decoded = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    return decoded;
}

@end
