/* MicroHTTPKit - A small libmicrohttpd wrapper
 * Copyright (C) 2023 Hugo Melder
 *
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>
#include <Foundation/NSObjCRuntime.h>

#import <MicroHTTPKit/HKHTTPRequest.h>
#import <MicroHTTPKit/HKHTTPResponse.h>

NS_ASSUME_NONNULL_BEGIN

typedef HKHTTPResponse *_Nonnull (^HKHandlerBlock)(HKHTTPRequest *request);

extern NSString *const HKResponseDataKey;
extern NSString *const HKResponseStatusKey;

@interface HKRoute : NSObject

@property (readonly, copy) NSString *path;
@property (readonly, copy) HKHandlerBlock handler;
@property (readonly, copy) NSString *method;

+ (instancetype)routeWithPath:(NSString *)path
					   method:(NSString *)method
					  handler:(HKHandlerBlock)handler;

- (instancetype)initWithPath:(NSString *)path
					  method:(NSString *)method
					 handler:(HKHandlerBlock)handler;

@end

@interface HKRouter : NSObject

@property (copy) HKHandlerBlock notFoundHandler;
@property (copy, nullable) HKHandlerBlock middleware;

- (HKHandlerBlock)handlerForRequest:(HKHTTPRequest *)request;

+ (instancetype)routerWithRoutes:(NSArray<HKRoute *> *)routes
				 notFoundHandler:(HKHandlerBlock)notFoundHandler;

- (instancetype)initWithRoutes:(NSArray<HKRoute *> *)routes
			   notFoundHandler:(HKHandlerBlock)notFoundHandler NS_DESIGNATED_INITIALIZER;

- (void)registerRoute:(HKRoute *)route;

- (NSArray<HKRoute *> *)routes;

@end

NS_ASSUME_NONNULL_END