//
//  HTTPConnection.h
//  CoreNetworking
//
//  Created by Keith Duncan on 29/04/2009.
//  Copyright 2009. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <CFNetwork/CFNetwork.h>
#endif /* TARGET_OS_IPHONE */

#import "CoreNetworking/AFNetworkConnection.h"
#import "CoreNetworking/AFNetworkConnectionLayer.h"

@class AFHTTPConnection;

/*!
	\brief
	
 */
@protocol AFHTTPConnectionControlDelegate <AFNetworkConnectionControlDelegate>

@end

/*!
	\brief
	
 */
@protocol AFHTTPConnectionDataDelegate <AFNetworkConnectionDataDelegate>

- (void)networkConnection:(AFHTTPConnection *)connection didReceiveRequest:(CFHTTPMessageRef)request;

- (void)networkConnection:(AFHTTPConnection *)connection didReceiveResponse:(CFHTTPMessageRef)response;

@end

/*!
	\brief
	
 */
@protocol AFHTTPConnectionDelegate <AFNetworkConnectionDelegate, AFHTTPConnectionControlDelegate, AFHTTPConnectionDataDelegate>

@end

/*!
	\brief
	This class is indended to sit on top of AFNetworkTransport and provides HTTP messaging semantics.
	
	\details
	It handles each request in series; and includes automatic behaviour for serveral responses:
	
	- 
 */
@interface AFHTTPConnection : AFNetworkConnection {
 @private
	NSMutableDictionary *_messageHeaders;
}

/*!
	\brief
	This property adds HTTP message data callbacks to the delegate.
 */
@property (assign, nonatomic) id <AFHTTPConnectionDelegate> delegate;

/*!
	\brief
	These headers will be added to each request/response written to the connection.
 
	\details
	A client could add a 'User-Agent' header, likewise a server could add a 'Server' header.
 */
@property (readonly, retain, nonatomic) NSMutableDictionary *messageHeaders;

/*
	Override Points
 */

/*!
	\brief
	Overridable for subclasses, before a message is sent.
	
	\details
	Adds the <tt>messageHeaders</tt> and a "Content-Length" header.
 */
- (void)prepareMessageForTransport:(CFHTTPMessageRef)message;

/*!
	\brief
	Overridable for subclasses, called to return a message to the delegate.
 */
- (void)processMessageFromTransport:(CFHTTPMessageRef)message;

/*
	Requests
 */

/*!
	\brief
	This method allows for raw HTTP messaging without starting the internal request/response matching.
 */
- (void)performRequestMessage:(CFHTTPMessageRef)message;

/*!
	\brief
	This enqueues a request reading packet, and is useful for servers and raw messaging.
 */
- (void)readRequest;

/*
	Responses
 */

/*!
	\brief
	This serialises the response and writes it out over the wire.
	The connection wide headers will be appended to it.
 */
- (void)performResponseMessage:(CFHTTPMessageRef)message;

/*!
	\brief
	This enqueues a response reading packet, and is useful for raw messaging.
 */
- (void)readResponse;

/*
	Lower layer overrides
 */

- (void)networkLayer:(id <AFNetworkTransportLayer>)layer didWrite:(id)data context:(void *)context;
- (void)networkLayer:(id <AFNetworkTransportLayer>)layer didRead:(id)data context:(void *)context;

@end
