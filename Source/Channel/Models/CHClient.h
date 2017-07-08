//
//  CHClient.h
//  Channel
//
//  Created by Apisit Toompakdee on 1/26/17.
//  Copyright © 2017 Mogohichi, Inc. All rights reserved.
//

#import <Channel/Channel.h>
#import "CHAPI.h"
#import "CHThread.h"
#import "CHMessage.h"
#import "CHNotification.h"
#import "CHApplication.h"
#import "CHAgent.h"
@class CHClient;

@protocol CHClientDelegate <NSObject>

- (void)client:(CHClient*)client messageFromServer:(CHMessage*)message;

@end

typedef void (^DidCheckNewMessages)(NSInteger numberOfNewMesages);
typedef void (^DidConnectClient)(NSError* error);
typedef void (^DidLoadActiveThread)(CHThread* thread,NSError* error);
typedef void (^DidSendMessage)(CHThread* thread,CHMessage* sentMessage,NSError* error);
typedef void (^DidLoadMessages)(CHThread* thread, NSArray<CHMessage*>* messages,NSError* error);
typedef void (^DidFinishUploadImage)(NSURL* imageURL, NSError* error);
typedef void (^DidGetUpdateFromServer)();
typedef void (^DidLoadCardTemplate)(NSString* templateString);
typedef void (^DidGetApplicationInfo) (CHApplication* application, NSArray<CHAgent *>* agents);
typedef void (^DidCheckNotification) (CHNotification* notification, NSError* error);
@interface CHClient : CHBase

@property (nonatomic, strong) NSString* clientID;
@property (nonatomic, strong) NSString* userID;
@property (nonatomic, strong) NSDictionary* userData;
@property (nonatomic) id<CHClientDelegate> delegate;

+(void)connectClientwithUserID:(NSString*)userID userData:(NSDictionary*)userData block:(DidConnectClient)block;
+ (void)connectClient:(DidConnectClient)block;

+ (CHClient*)currentClient;

-(void)updateClientDataWithUserID:(NSString*)userID userData:(NSDictionary*)userData block:(DidConnectClient)block;

- (void)applicationInfo:(DidGetApplicationInfo)block;

- (void)sendMessage:(CHMessage*)message block:(DidSendMessage)block;
- (void)activeThread:(DidLoadActiveThread)block;
- (void)loadMoreMessage:(CHThread*)thread block:(DidLoadMessages)block;

- (void)startTyping;

- (void)subscribeUpdateFromServerWithDelegate:(id<CHClientDelegate>)delegate;

- (void)unsubscribe;
- (void)uploadImage:(UIImage*)image block:(DidFinishUploadImage)block;

- (void)checkNewMessages:(DidCheckNewMessages)block;

- (void)updateActiveStatus:(Boolean)active;

- (void)loadCardTemplate:(CHCardPayloadTemplate*)payload block:(DidLoadCardTemplate)block;

- (void)checkNewNotification:(DidCheckNotification)block;

- (void)postbackNotification:(CHNotification*)notification button:(CHNotificationButton*)button;

- (void)presentWebViewWithURL:(NSURL*)url inViewController:(UIViewController*)viewController;

- (void)saveDeviceToken:(NSData*)deviceToken;

- (void)markOpenFromPushNotification:(NSString*)notificationPublicID;

- (void)pushNotificationEnabled:(BOOL)enabled;

- (void)appendTags:(NSDictionary*)tags;

@end
