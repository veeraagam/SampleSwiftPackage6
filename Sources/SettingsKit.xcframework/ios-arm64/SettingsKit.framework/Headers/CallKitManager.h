//
//  CallKitManager.h
//  MobileOffice
//
//  Created by Labs108 on 02/10/17.
//  Copyright © 2017 Phone.Com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SipManagerBridge.h"

@class IncomingPushCallObject;


/*!
    @class         CallKitManager
    @abstract      CallKitManager is a singletn class.
    @discussion    An instance of this class can be used to perform CallKit actions.
*/

/// An instance of this class can be used to perform CallKit actions.
@interface CallKitManager : NSObject

@property (copy, nonatomic) WillInitiatInComingCall _Nullable willInitiatInComingCallHandler;

/// Queue used to execute completion callback. Default is mainQueue
@property(nonatomic, strong, nullable) dispatch_queue_t completionQueue; // Default to mainQueue

/// The unique identifier for the associated SipCallInfo object.
@property (strong, nonatomic) NSString * _Nonnull pjsuaCallUUID;


/// CallKitManager is a singleton class. sharedManager is used to access singleton object
///
/// - Returns: A singleton CallKitManager object.
///
+ (CallKitManager *_Nonnull)sharedManager;

/*!
    @brief       Invalidates the provider and completes all active calls with an error.

    @discussion  After a receiver is invalidated, no additional messages are sent to its delegate.
 
    @see          CXProvider
*/

/// Invalidates the provider and completes all active calls with an error.
///
/// After a receiver is invalidated, no additional messages are sent to its delegate.
///
/// - See: CXProvider
///
- (void)invalidateAllCalls;

/*!
    @brief       Initializes callkit configuration with the specified localized name.

    @discussion  This is the function must call to initialize Callkit
 
    @param       appName
                 A localized name for the provider.
    @param       supportsVideo
                 A Boolean value that indicates whether the provider supports video in addition to audio.
    @param       actionNotificationBlock
                 Action notification block, this will call on any action perform on Callkit
 
    @see         SipCallKitActionNotificationBlock
    @see         CallKitCallActionType
*/

/// Initializes callkit configuration with the specified localized name.
///
/// @param appName: A localized name for the provider.
/// @param supportsVideo: A Boolean value that indicates whether the provider supports video in addition to audio.
/// @param actionNotificationBlock: Action notification block, this will call on any action perform on Callkit
///
/// - See: SipCallKitActionNotificationBlock
/// - See: CallKitCallActionType
///
- (void)setupWithAppName:(NSString *_Nullable)appName
           supportsVideo:(BOOL)supportsVideo
 actionNotificationBlock:(SipCallKitActionNotificationBlock _Nullable)
actionNotificationBlock;


/*!
    @brief       Perform mute action.

    @discussion  Initializes a new action for a call identified by a given UUID, as well as whether the call is muted.
 
    @param       mute
                 A Boolean value that indicates whether the call is muted
    @param       callUUID
                 The unique identifier for the associated SipCallInfo object.
    @param       completion
                 Code to be executed after the transaction is completed.
 
    @see         CXSetMutedCallAction
*/

/// Perform mute action.
///
/// Initializes a new action for a call identified by a given UUID, as well as whether the call is muted.
///
/// @param mute:A Boolean value that indicates whether the call is muted
/// @param callUUID: The unique identifier for the associated SipCallInfo object.
/// @param completion: Code to be executed after the transaction is completed.
///
/// - See: CXSetMutedCallAction
///
- (void)mute:(BOOL)mute callUUID:(NSUUID * _Nonnull)callUUID completion:(SipCallKitManagerCompletion _Nullable)completion;

/*!
    @brief       Perform hold action.

    @discussion  Initializes a new action for a call identified by a given UUID, as well as whether the call is hold.
 
    @param       hold
                 Whether the call is on hold.
    @param       callUUID
                 The unique identifier for the associated SipCallInfo object.
    @param       completion
                 Code to be executed after the transaction is completed.
 
    @see         CXSetHeldCallAction
*/

/// Perform hold action.
///
/// Initializes a new action for a call identified by a given UUID, as well as whether the call is hold.
///
/// @param hold: Whether the call is on hold.
/// @param callUUID: The unique identifier for the associated SipCallInfo object.
/// @param completion: Code to be executed after the transaction is completed.
///
/// - See: CXSetHeldCallAction
///
- (void)hold:(BOOL)hold callUUID:(NSUUID * _Nonnull)callUUID completion:(SipCallKitManagerCompletion _Nullable)completion;

/*!
    @brief       Perform end call action.

    @discussion  Initializes a new end call action for a call identified by a given UUID.
 
    @param       callUUID
                 The unique identifier for the associated SipCallInfo object.
    @param       completion
                 Code to be executed after the transaction is completed.
 
    @see         CXEndCallAction
*/

/// Perform end call action.
///
/// Initializes a new end call action for a call identified by a given UUID.
///
/// @param callUUID: The unique identifier for the associated SipCallInfo object.
/// @param completion: Code to be executed after the transaction is completed.
///
/// - See: CXEndCallAction
///
- (void)endCall:(NSUUID * _Nonnull)callUUID completion:(SipCallKitManagerCompletion _Nullable)completion;

/*!
    @brief       Reports a new incoming call with the specified SipCallInfo object.

    @discussion  An incoming call may be disallowed by the system if, for example the user has Do Not Disturb enabled.
 
    @param       callInfo
                 The SipCallInfo object of the call.
    @param       callCompleted
                 A block to be executed once the call is allowed or disallowed by the system.
 
    @see         CXCallUpdate
*/

/// Reports a new incoming call with the specified SipCallInfo object.
///
/// An incoming call may be disallowed by the system if, for example the user has Do Not Disturb enabled.
///
/// @param callInfo: The SipCallInfo object of the call.
/// @param callCompleted: A block to be executed once the call is allowed or disallowed by the system.
///
/// - See: CXCallUpdate
///
- (void)reportIncomingCallWithCallInfo:(SipCallInfo* _Nonnull)callInfo withCompletionHandler:(void(^_Nullable)(void))callCompleted;

/*!
    @brief       Reports a new incoming call with the specified unique identifier of the call.

    @discussion  An incoming call may be disallowed by the system if, for example the user has Do Not Disturb enabled.
 
    @param       UUID
                 The unique identifier of the call.
    @param       callerName
                 The localized name of the caller.
    @param       callerNumber
                 The number of the caller.
    @param       callCompleted
                 A block to be executed once the call is allowed or disallowed by the system.
 
    @see         CXCallUpdate
*/

/// Reports a new incoming call with the specified unique identifier of the call.
///
/// An incoming call may be disallowed by the system if, for example the user has Do Not Disturb enabled.
///
/// @param UUID: The unique identifier of the call.
/// @param callerName: The localized name of the caller.
/// @param callerNumber: The number of the caller.
/// @param callCompleted: A block to be executed once the call is allowed or disallowed by the system.
///
/// - See: CXCallUpdate
///
- (void)reportIncomingCallWithcallUUID:(NSString* _Nonnull)UUID callerName:(NSString*)callerName callerNumber:(NSString*)callerNumber withCompletionHandler:(void(^)(void))callCompleted;

/*!
    @brief       Reports a new incoming call with the specified number of the caller.

    @discussion  An incoming call may be disallowed by the system if, for example the user has Do Not Disturb enabled.
 
    @param       number
                 The number of the caller.
    @param       callCompleted
                 A block to be executed once the call is allowed or disallowed by the system.
 
    @see         CXCallUpdate
*/

/// Reports a new incoming call with the specified number of the caller.
///
/// An incoming call may be disallowed by the system if, for example the user has Do Not Disturb enabled.
///
/// @param number: The number of the caller.
/// @param callCompleted: A block to be executed once the call is allowed or disallowed by the system.
///
/// - See: CXCallUpdate
///
- (NSUUID * _Nonnull)reportIncomingCallWithNumber:(NSString * _Nonnull )number completion:(SipCallKitManagerCompletion _Nullable)completion;

/*!
    @brief       Perform new call

    @discussion  Initializes a new action to start a call with the specified SipCallInfo object to a recipient with the specified handle.
 
    @param       callInfo
                 The SipCallInfo object of the call.
    @param       callCompleted
                 A block to be executed once the call is allowed or disallowed by the system.
 
    @see         CXStartCallAction
*/

/// Perform new call
///
/// Initializes a new action to start a call with the specified SipCallInfo object to a recipient with the specified handle.
///
/// @param callInfo: The SipCallInfo object of the call.
/// @param callCompleted: A block to be executed once the call is allowed or disallowed by the system.
///
/// - See: CXCallUpdate
///
- (NSUUID * _Nonnull)reportOutgoingCallUsingCallInfo:(SipCallInfo* _Nonnull)callInfo
                                          completion:(SipCallKitManagerCompletion _Nullable )completion;

/*!
    @brief       Update call state to the provider with the specified unique identifier started connecting at a particular time.
 
    @param       callUUID
                 The unique identifier of the call.
    @param       callCompleted
                 A block to be executed once the call is allowed or disallowed by the system.
 
    @see         CallKitCallState
*/

/// Update call state to the provider with the specified unique identifier started connecting at a particular time.
///
/// @param callUUID: The unique identifier of the call.
/// @param callCompleted: A block to be executed once the call is allowed or disallowed by the system.
///
/// - See: CXCallUpdate
///
- (void)updateCall:(NSUUID *_Nonnull)callUUID state:(CallKitCallState)state withCompletionHandler:(void(^_Nullable)(void))callCompleted;


/// Handle unwanted calls to avoid crash on device
///
/// @param callUUID: The unique identifier of the call.
/// @param callCompleted: A block to be executed once the call is allowed or disallowed by the system.
///
/// - See: CXCallUpdate
///
- (void)reportIncomingCallToAvoidCrashWithUUID:(NSUUID * _Nonnull )callUUID completion:(void(^_Nonnull)(void))callCompleted;


/// Reports to the provider that an active call updated its information.
///
/// @param callInfo: SipCallInfo call object
///
/// - See: CXCallUpdate
///
- (void)updateCallInfo:(NSUUID *_Nonnull)callUUID callInfo:(SipCallInfo *_Nonnull)callInfo;

@end
