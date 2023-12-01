#import <MicroHTTPKit/MicroHTTPKit.h>

int main(void) {
	@autoreleasepool {
		HKHTTPServer *server;
		HKRoute *route;
		HKRoute *postRoute;
		HKHandlerBlock simpleMiddleware;
		NSError *error;

		server = [[HKHTTPServer alloc] initWithPort:8080];
		route = [HKRoute
			routeWithPath:@"/"
				   method:HKHTTPMethodGET
				  handler:^(HKHTTPRequest *request) {
					  NSLog(@"UserInfo: %@", [request userInfo]);
					  return [HKHTTPResponse
						  responseWithData:[@"Hello, World!" dataUsingEncoding:NSUTF8StringEncoding]
									status:200];
				  }];

		postRoute = [HKRoute
			routeWithPath:@"/post"
				   method:HKHTTPMethodPOST
				  handler:^(HKHTTPRequest *request) {
					  NSString *body;
					  NSData *data;

					  data = [request HTTPBody];
					  body = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];

					  NSLog(@"Received %lu bytes: %@", [data length], body);
					  return [HKHTTPResponse
						  responseWithData:[@"Received!" dataUsingEncoding:NSUTF8StringEncoding]
									status:200];
				  }];

		simpleMiddleware = ^(HKHTTPRequest *request) {
			[request setUserInfo:@{@"foo" : @"bar"}];
			NSLog(@"Middleware called");
			return nil;
		};

		[[server router] registerRoute:route];
		[[server router] registerRoute:postRoute];
		[[server router] setMiddleware:simpleMiddleware];

		if (![server startWithError:&error]) {
			NSLog(@"Failed to start server: %@", error);
			return -1;
		}

		NSLog(@"Server available at :8080");

		[[NSRunLoop currentRunLoop] run];

		[server stop];
	}
	return 0;
}
