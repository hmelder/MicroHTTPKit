/* MicroHTTPKit - A small libmicrohttpd wrapper
 * Copyright (C) 2023 Hugo Melder
 *
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HKHTTPRequest : NSObject {
  @private
	NSData *_HTTPBody;
}

@property (nonatomic, readonly, copy) NSString *method;
@property (nonatomic, readonly, copy) NSURL *URL;
@property (nonatomic, readonly, copy) NSDictionary<NSString *, NSString *> *headers;
@property (nonatomic, readonly, copy) NSDictionary<NSString *, NSString *> *queryParameters;

- (instancetype)initWithMethod:(NSString *)method
						   URL:(NSURL *)URL
					   headers:(NSDictionary<NSString *, NSString *> *)headers;

- (instancetype)initWithMethod:(NSString *)method
						   URL:(NSURL *)URL
					   headers:(NSDictionary<NSString *, NSString *> *)headers
			   queryParameters:(NSDictionary<NSString *, NSString *> *)queryParameters;

- (NSData *)HTTPBody;

@end

NS_ASSUME_NONNULL_END