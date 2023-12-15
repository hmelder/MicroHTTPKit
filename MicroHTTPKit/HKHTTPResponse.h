/* MicroHTTPKit - A small libmicrohttpd wrapper
 * Copyright (C) 2023 Hugo Melder
 *
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HKHTTPResponse : NSObject

@property (strong, nullable) NSData *data;
@property (assign) NSUInteger status;
@property (strong) NSDictionary<NSString *, NSString *> *headers;

/**
	@brief If set to YES, the server will check if the endpoint exists *after* the middleware block

	This property only has an effect when set in the middleware block.
*/
@property BOOL checkIfEndpointExists;

+ (instancetype)responseWithStatus:(NSUInteger)status;
+ (instancetype)responseWithData:(NSData *)data status:(NSUInteger)status;

- (instancetype)initWithStatus:(NSUInteger)status;

- (instancetype)initWithData:(NSData *)data status:(NSUInteger)status;

- (instancetype)initWithData:(NSData *)data
					 headers:(NSDictionary<NSString *, NSString *> *)headers
					  status:(NSUInteger)status;

@end

@interface HKHTTPJSONResponse : HKHTTPResponse

+ (instancetype)responseWithJSONObject:(id)JSONObject
								status:(NSUInteger)status
								 error:(NSError **)error;

- (instancetype)initWithJSONObject:(id)JSONObject status:(NSUInteger)status error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
