//
//  AFHTTPClient.h
//  Amber
//
//  Created by Keith Duncan on 03/06/2009.
//  Copyright 2009. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <CFNetwork/CFNetwork.h>
#endif /* TARGET_OS_IPHONE */

#import "CoreNetworking/AFHTTPConnection.h"

#import "CoreNetworking/AFNetwork-Macros.h"

@class AFHTTPClient;

@class AFNetworkPacketQueue;
@class AFHTTPTransaction;

@protocol AFHTTPClientDelegate <AFHTTPConnectionDelegate>

- (void)networkConnection:(AFHTTPClient *)connection didReceiveResponse:(CFHTTPMessageRef)response context:(void *)context;

@end

/*!
	\brief
	Adds request/response transaction tracking to AFHTTPConnection raw messaging
 */
@interface AFHTTPClient : AFHTTPConnection {
 @private
	NSString *_userAgent;
	
	BOOL _shouldStartTLS;
	
	AFNetworkPacketQueue *_transactionQueue;
}

@property (assign, nonatomic) id <AFHTTPClientDelegate> delegate;

+ (NSString *)userAgent;
+ (void)setUserAgent:(NSString *)userAgent;

@property (copy, nonatomic) NSString *userAgent;

/*
	Transaction Methods
		These automatically enqueue reading a response.
 */

/*!
	\brief
	This method enqueues a transaction, which pairs a request with it's response. The request may not be issued immediately.
 */
- (void)performRequest:(NSString *)HTTPMethod onResource:(NSString *)resource withHeaders:(NSDictionary *)headers withBody:(NSData *)body context:(void *)context;

/*!
	\brief
	This method enqueues a transaction, which pairs a request with it's response. The request may not be issued immediately.
	This method may assist you in moving to a request/response model from the URL loading architecture in Cocoa.
	
	\details
	This is likely to be most useful where you already have a web service context, which vends preconstructed requests.
	
	\param request
	This method handles HTTP NSURLRequest objects with an HTTPBodyData, or HTTPBodyFile.
	If passed an NSURLRequest with an HTTPBodyStream, an exception is thrown.
 */
- (void)performRequest:(NSURLRequest *)request context:(void *)context;

/*!
	\brief
	Replaces NSURLDownload which can't be scheduled in multiple run loops or modes.
	
	\details
	Will handle large files by streaming them to disk.
 */
- (void)performDownload:(NSString *)HTTPMethod onResource:(NSString *)resource withHeaders:(NSDictionary *)headers withLocation:(NSURL *)fileLocation context:(void *)context;

/*!
	\brief
	Counterpart to <tt>performDownload:onResource:withHeaders:withLocation:</tt>.
	
	\details
	Will handle large files by streaming them from disk.
 */
- (BOOL)performUpload:(NSString *)HTTPMethod onResource:(NSString *)resource withHeaders:(NSDictionary *)headers withLocation:(NSURL *)fileLocation context:(void *)context error:(NSError **)errorRef;

/*
	Primitive
 */

/*!
	\brief
	Append your own request/response pair reading packets
 */
- (void)enqueueTransaction:(AFHTTPTransaction *)transaction;

@end
