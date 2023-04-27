//
//  PushRegistryManager.h
//  PhoneSipManager
//
//  Created by Phone.com on 09/12/19.
//  Copyright © 2019 Phone.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PushKit/PushKit.h>

NS_ASSUME_NONNULL_BEGIN

/// This protocol is required to handle callbacks from PushRegistryManager class
@protocol PushRegistryManagerDelegate <NSObject>

@optional
/*!
    @discussion     This method is invoked when a incoming call push notification has been received for the specified PKPushType.
 
    @param          payload
                    The push payload sent by a developer via APNS server API.
    @param          type
                    This is a PKPushType constant which is present in [registry desiredPushTypes].
    @param          completion
                    This completion handler should be called to signify the completion of payload processing.
*/

/// This method is invoked when a incoming call push notification has been received for the specified PKPushType.
/// Never block main thread in this method, blocking of main thread would crash the application.
///
/// @param payload: The push payload sent by a developer via APNS server API.
/// @param type: This is a PKPushType constant which is present in [registry desiredPushTypes].
/// @param completion: This completion handler should be called to signify the completion of payload processing.
///
- (void)didReceivedIncomingCallPayload:(PKPushPayload *)payload forType:(PKPushType)type withCompletionHandler:(void(^)(void))callDidCompleted;

/*!
    @discussion     This method is invoked when new credentials (including push token) have been received for the specified
                    PKPushType.
    @param          token
                    The device token recevied new credentials
*/

/// This method is invoked when new credentials (including push token) have been received for the specified PKPushType.
///
/// @param token: The device token recevied new credentials
///
- (void)didUpdatePushCredentials:(NSString *)token;

@end

/*!
    @class         PushRegistryManager
    @abstract      PushRegistryManager is a singletn class.
    @discussion    An instance of this class can be used to register for PKPushRegistry. The supported push
                    notification types are listed above as PKPushType constants.
*/
/// An instance of this class can be used to register for PKPushRegistry. The supported push notification types are listed above as PKPushType constants.
@interface PushRegistryManager : NSObject


#pragma mark *** Sip call handlers ***

/// delegate to handle callbacks from the class
@property (nonatomic, weak) id<PushRegistryManagerDelegate> delegate;


#pragma mark *** Intialise singleton object ***

/*!
    @brief       Class funtion to creates singleton instance of PushRegistryManager

    @discussion  A PushRegistryManager singleton instance use to register for PKPushRegistry
    @return      PushRegistryManager
                The singleton instance.
*/
/// Class funtion to creates singleton instance of PushRegistryManager
///
/// A PushRegistryManager singleton instance use to register for PKPushRegistry
///
/// - returns: The singleton instance.
///
+ (PushRegistryManager *_Nonnull)sharedManager;

/*!
    @brief       Registers the PKPushRegistry object for type 'PKPushTypeVoIP'

    @discussion  The push registry object makes a registration request with the PushKit server. This request is asynchronous, and the success of the request is reported to your                    delegate object. For a successful registration, PushRegistryManager delivers a device token to the delegate.
 
    @see          PKPushRegistry
*/

/// Registers the PKPushRegistry object for type 'PKPushTypeVoIP'
///
/// The push registry object makes a registration request with the PushKit server. This request is asynchronous, and the success of the request is reported to your delegate object. For a successful registration, PushRegistryManager delivers a device token to the delegate.
/// Must call this function on application launch in application delegate class
///
/// - See: PKPushRegistry
/// - See: - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
///
- (void)registerForPushKit;

/*!
    @brief       Return PKPushRegistry object
 
    @return     pushRegistry
                Object created at the time of 'registerForPushKit' function
*/

/// Return PKPushRegistry object
/// Highly recommended to save PKPushRegistry object in application delegate class for smooth functioning
///
/// - Returns: Object created at the time of 'registerForPushKit' function
///
- (PKPushRegistry *)pushRegistry;

@end

NS_ASSUME_NONNULL_END
