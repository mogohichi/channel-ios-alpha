//
//  Channel.h
//  Channel
//
//  Created by Apisit Toompakdee on 12/18/16.
//  Copyright © 2016 Mogohichi, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "CHNotification.h"
#import "CHNotificationButton.h"

@class Channel;
@class CHNotification;
@class CHNotificationButton;

@protocol ChannelDelegate <NSObject>

@optional
- (void)channelUserDidTapButtonNotificationView:(CHNotification* _Nonnull)notification button:(CHNotificationButton* _Nonnull)button;
@optional
- (void)channelUserDidTapPushNotificationTypeConversations;
@optional
- (void)channelUserDidTapPushNotificationTypeInAppMessage;
@end

typedef void (^DidCheckUnseenMessage)(NSInteger numberOfNewMessages);

@interface Channel : NSObject

@property (weak, nonatomic, nullable) id<ChannelDelegate> delegate;

+ (Channel* _Nonnull)shared;

+ (void)setupWithApplicationId:(NSString* _Nonnull)appId;

+ (void)setupWithApplicationId:(NSString* _Nonnull)appId userID:(NSString* _Nullable)userID userData:(NSDictionary* _Nullable)userData;

+ (void)setupWithApplicationId:(NSString* _Nonnull)appId launchOptions:(NSDictionary* _Nullable)launchOptions;

+ (void)setupWithApplicationId:(NSString* _Nonnull)appId userID:(NSString* _Nullable)userID userData:(NSDictionary* _Nullable)userData launchOptions:(NSDictionary* _Nullable)launchOptions;;

+ (void)checkNewMessages:(DidCheckUnseenMessage _Nonnull)block;

- (void)showLatestNotification;

+(UIViewController * _Nonnull)chatViewControllerWithUserID:(NSString* _Nonnull)userID userData:(NSDictionary* _Nullable)userData;

- (void)updateUserID:(NSString* _Nonnull)userID userData:(NSDictionary* _Nullable)userData;

+ (void)pushNotificationEnabled:(BOOL)enabled;

- (void)appendTags:(NSDictionary*)tags;

@end
