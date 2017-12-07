//
//  SFKPCHImport.h
//  sense
//
//  Created by Marc-Henri Primault
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

#import "SFKLogger.h"

/**
 *  Enable the control of the logs
 *
 *  To enable the control of the logs
 *  1) You should import this file into your .pch project file.
 *  2) Then into your Build Settings, you should be sure that the Preprocessor Macro (GCC_PREPROCESSOR_DEFINITIONS) 
 *     contains DEBUG for the debug target to print log in the console.
 */
#ifdef DEBUG
    #define NSLog( s, ... ) [[SFKLogger instance] log:[NSString stringWithFormat:@"<%@:(%d)> %@", [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__, [NSString stringWithFormat:(s), ##__VA_ARGS__]]]; \
                            NSLog(@"%@", [NSString stringWithFormat:@"<%@:(%d)> %@", [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__, [NSString stringWithFormat:(s), ##__VA_ARGS__]])
#else
    #define NSLog( s, ... ) [[SFKLogger instance] log:[NSString stringWithFormat:@"<%@:(%d)> %@", [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__, [NSString stringWithFormat:(s), ##__VA_ARGS__]]]
#endif
