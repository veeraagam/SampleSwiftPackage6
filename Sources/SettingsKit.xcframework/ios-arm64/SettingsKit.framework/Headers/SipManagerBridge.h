//
//  VOIPStore.h
//  MobileOffice

//  Copyright (c) 2014 Phone.com. All rights reserved.
//


/*!
    @class    SipManagerBridge
    @abstract SipManagerBridge is a singletn class.
    @discussion A SipManagerBridge singleton instance use to handle Sip activites like Sip Regiatration, Incoming and OutGoing call,
                all activities related to calls like hold, mute....
*/


#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "SipCallInfo.h"
#import "SipRegisterInfo.h"
#import "PushRegistryManager.h"

@class IncomingPushCallObject;

@interface SipManagerBridge : NSObject  {
  SIP_CALL_STATE _callState;
}

#pragma mark *** Sip call handlers ***

/// Call back to handle updated state of Sip Store Account
/// - See: SIP_STORE_ACCOUNT_STATE
@property (copy, nonatomic) OnSipAccountRegistered _Nullable registerationHandler;

/// Call back to handle incoming audio and video call.
@property (copy, nonatomic) OnIncomingCallRecieved _Nullable incomingCallRecievedHandler;

/// Call back to capture UIView of incoming video call
@property (copy, nonatomic) OnIncomingVideoCaptured _Nullable incomingVideoCapturedHandler;

/// Call back to handle when application registered to SIP server and ready to make a call.
@property (copy, nonatomic) OnIntialisedToMakeCall _Nullable sipIntialisedToMakeCallHandler;

/// Call back to manage updated media event.
/// - See: SIP_CALL_MEDIA_EVENT
@property (copy, nonatomic) OnMediaInfoUpadted _Nullable mediaInfoUpdatedHandler;


#pragma mark *** Intialise singleton object ***


/// Class funtion to creates singleton instance of SipManagerBridge
///
/// A SipManagerBridge singleton instance use to handle Sip activites like Sip Regiatration, Incoming and OutGoing call,
/// all activities related to calls like hold, mute....
///
/// - Returns: The singleton instance.

+ (SipManagerBridge *_Nonnull)sharedManager;


/// Class funtion to tell about application state
///
/// This function returns bool to know about application current state state
///
/// To use it, simply call [SipManagerBridge isApplicationInForeGround];
///
/// - Returns: Return true if application state is UIApplicationStateBackground else return false.
///
+ (BOOL)isApplicationInForeGround;


#pragma mark *** Intialise and destroy sip system ***

/// Will check application registered to SIP server or not.
///
/// If application is not registered then this method will register it automatically.
/// This method will call "registerationHandler" and "sipIntialisedToMakeCallHandler"
///
/// Call initSipSystem - (void)initSipSystem:(SipRegisterInfo *_Nonnull)registerInfo before this.
///
/// - See: - (void)initSipSystem:(SipRegisterInfo *_Nonnull)registerInfo;
///
- (void)checkVOIPSystemStatus;


/// Perform unregistration and destroy pjsua.
///
/// Destroy pjsua. Application is recommended to perform graceful shutdown before calling this method (such as unregister the account from the
/// SIP server, terminate presense subscription, and hangup active calls), however, this method will do all of these if it finds there are
/// active sessions that need to be terminated.
///
- (void)destroyStack;

/// Save values - will requires to create sip account
///
/// Must call this function before 'checkVOIPSystemStatus'.
///
/// @param registerInfo: The input value conatins domain, user, password...
///
/// - See: SipRegisterInfo
/// - See: - (void)checkVOIPSystemStatus;
///
- (void)initSipSystem:(SipRegisterInfo *_Nonnull)registerInfo;


/// Setup CallKit
///
/// Must call this method to manage call activities properly.
///
- (void)setUpCallKit:(NSString * _Nullable )appName;


/// Perform unregistration.
///
/// Application normally only needs to call this method if it wants to manually to unregister from the server.
///
- (void)unRegister;
- (void)unRegisterFromPush;


#pragma mark *** Get caller info ***

- (NSString *_Nullable)getCallerCNAM:(NSString *_Nonnull)callUUID; // if the name via caller ID exists, return it here
- (NSString *_Nullable)getCallerDID:(NSString *_Nonnull)callUUID;
- (NSString *_Nullable)getSipDomain;
- (NSString *_Nullable)getSipProtocol;


#pragma mark *** Get account state ***

- (SIP_STORE_ACCOUNT_STATE)getStoreAccountState;
- (SIP_STORE_SYSTEM_STATE)getStoreSystemState;


#pragma mark *** Find SipCallInfo object ***

/// Perform Search for SipCallInfo object
///
/// This method will find and return the object of SipCallInfo from active calls array.
///
/// @param callUUID: UUID of call
///
/// - Returns: SipCallInfo object
///
- (SipCallInfo *_Nonnull)findSipCallForUUID:(NSString*_Nonnull)callUUID;


#pragma mark *** Hold, unHold, Mute and UnMute Sip call ***

/// Hold the call
///
/// Pass callUUID of SipCallInfo object on which you want to perfom <b>Hold</b> action.
///
/// @param callUUID: UUID of call
/// @param handler: Callback on completion
///
- (void)holdCall:(NSString *_Nonnull)callUUID onCompletion:(OnCallOnHoldCompletion _Nullable )handler;


/// Perform Mute on call
///
/// Pass callUUID of SipCallInfo object on which you want to perfom <b>Mute</b> action.
///
/// @param callUUID: UUID of call
///
- (void)muteOngoingCall:(NSString *_Nonnull)callUUID;


/// Perform unHold on call
///
/// Pass callUUID of SipCallInfo object on which you want to perfom <b>unHold</b> action.
///
/// @param callUUID: UUID of call
/// @param handler: Callback on completion
///
- (void)unHoldCall:(NSString *_Nonnull)callUUID onCompletion:(OnCallUnHoldCompletion _Nullable )handler;


/// Perform unmute on call
///
/// Pass callUUID of SipCallInfo object on which you want to perfom <b>unmute</b> action.
///
/// @param callUUID: UUID of call
///
- (void)unMuteOngoingCall:(NSString *_Nonnull)callUUID;


#pragma mark *** Make outgoing, incoming & Disconect and transfer Sip call ***

//// Perform new call actionl
///
/// Call this function to make new call
///
/// @param voipCallInfo: SipCallInfo object
/// @param parkingSlot: NSString* object
/// @param routingServer: NSString* object sip server
///
/// - See: SipCallInfo
///
- (BOOL)makeCall:(SipCallInfo* _Nonnull )voipCallInfo parkingSlot:(NSString* _Nullable )parkingSlot routingServer:(NSString* _Nullable )routingServer;


/// Perform to answer call
///
/// Call this function to make new call
///
/// @param callUUID: NSString* object
///
- (void)answerIncomingCall:(NSString *_Nonnull)callUUID;

/// Perform hangup call
///
/// Hang up all active calls
///
- (void)hangupAllCalls;


/// Perform hangup call
///
/// Hang up call with specific callUUID
///
/// @param callUUID: UUID of call
///
- (void)hangupCallWithUUID:(NSString *_Nonnull)callUUID;


/// Perform hangup call
///
/// Hang up specific call for SipCallInfo object pass in parameter.
///
/// @param callInfo: SipCallInfo object
///
/// - See: SipRegisterInfo
///
- (void)makeCallUsingCallInfo:(nonnull SipCallInfo *)callInfo;


/// Perform merge opeartion
///
/// Call this method to merge two active calls in the system.
///
/// @param callUuIdA: NSString* object source call
/// @param callUuIdB: NSString* object destination call
/// @param handler: Callback on completion
///
- (void)mergeCalls:(NSString *_Nonnull)callUuIdA localIdxB:(NSString *_Nonnull)callUuIdB onCompletion:(callsMergedCompletion _Nullable )handler;


/// Perform call transfer
///
/// Initiate call transfer to the specified address. This function will send REFER request to instruct remote call party to initiate a new           INVITE session to the specified destination/target.
///
/// @param callUUID: NSString* object source call
/// @param toDestination: NSString* object destination number
/// @param protocol:  NSString* object
///
- (void)transferCallWithId:(NSString *_Nonnull)callUUID toDestination:(nonnull NSString *)toDestination protocol:(NSString *_Nonnull)protocol;


/// Process incoming call from PushKit
///
/// @param payload: PKPushPayload* object
/// @param type: PKPushType object
/// @param callDidCompleted: Callback on completion
///
/// - See: PushKit framework
///
- (void)processIncomingCallForpayLoad:(PKPushPayload *_Nullable)payload
                              forType:(PKPushType _Nullable )type withCompletionHandler:(void(^_Nullable)(void))callDidCompleted;

#pragma mark *** Supporting ***

/// Return total call duration, including set-up time of specific call in seconds
///
/// @param callUUID: UUID of call
///
- (NSInteger)callDurationForCall:(NSString *_Nonnull)callUUID;


/// Return count of all ongoing calls in system
///
- (int)getSipCallsCount;
- (int)getSipCallsCount;


/// Select playback sound device and capture sound device. Application may call this function at any time to replace current sound device. Calling this method will not change the state of the sound device (opened/closed).
///
- (void)activateSoundDev;


/// Disconnect the main conference bridge from any sound devices, and let application connect the bridge to it's own sound device/master port.
///
- (void)deActivateSoundDev;


/// Send DTMF digits to remote.
///
/// @param code:  DTMF string digits to be sent.
/// @param callUUID: UUID of call
///
- (void)sendDTMFCode:(nonnull NSString *)code callUUID:(NSString *_Nonnull)callUUID;


/// Inform the stack that IP address change event was detected.
- (void)updateNetworkTransport;


/// Update sip protocol like "tcp" and "tls"
///
/// @param protocol: new protocol value like "tcp" and "tls"
///
- (void)updateSipProtocol:(NSString *_Nonnull)protocol;


/// Send re-INVITE.
///
/// @param callUUID: UUID of call
///
- (void)reinviteCall:(NSString *_Nonnull)callUUID;

@end




