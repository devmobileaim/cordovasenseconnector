//
//  SFKSecureStreamConnectionProtocol.h
//  sense-sdk-ios-framework
//
//  Created by Marc-Henri Primault
//  Copyright (c) 2014 Sysmosoft. All rights reserved.
//

#import "SFKCommunicationBlocks.h"

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
 */
- (void)streamConnectionWithService:(NSString *)service data:(NSData *)data withResponseBlock:(SFKStreamConnectionResponseBlock)responseBlock errorBlock:(SFKErrorBlock)errorBlock;

@end
