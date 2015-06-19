//
//  SFKPCHImport.h
//  sense
//
//  Created by Marc-Henri Primault
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

/**
 *  Enable the control of the logs
 *
 *  To enable the control of the logs
 *  1) You should import this file into your .pch project file.
 *  2) Then into your Build Settings, you should be sure that the Preprocessor Macro contains
 *     SENSE_LOG_ENABLED for the debug target to enable log for debug.
 */
#ifdef SENSE_LOG_ENABLED
    #define NSLog( s, ... ) NSLog( @"<%@:(%d)> %@", [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__, [NSString stringWithFormat:(s), ##__VA_ARGS__] )
#else
    #define NSLog( s, ... ) NSLog( @"%@", @"")
#endif
