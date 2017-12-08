//
//  SFKSecureStreamConnectionProtocol.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

#import "SFKCommunicationBlocks.h"

__attribute__((deprecated("first deprecated in SENSE 3.7 - Use NSURLConnection or NSURLSession requests")))
@protocol SFKSecureStreamConnectionProtocol <NSObject>

/**
 *  Execute an asynchrounous request to the given service and data for the application
 *
 *  If the response of the server is valid, responseBlock is called otherwise errorBlock.
 *
 *  @param service       The name of the service
 *  @param data          The data that is associated with the method
 *  @param responseBlock The block that is executed if there is no error
 *  @param errorBlock    The block that is executed if there is an error
 *
 *  @deprecated in 3.7
 *
 *  @warning All the communication should use the HTTP proxy. Please use NSURLConnection or NSURLSession requests instead of this method.
 */
- (void)streamConnectionWithService:(NSString *)service data:(NSData *)data withResponseBlock:(SFKStreamConnectionResponseBlock)responseBlock errorBlock:(SFKErrorBlock)errorBlock;

@end
