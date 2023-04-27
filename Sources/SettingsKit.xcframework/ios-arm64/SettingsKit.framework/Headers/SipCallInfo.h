//
//  SipCallInfo.h
//  MobileOffice
//
//  Created by Dheeraj Katarya on 5/10/16.
//  Copyright © 2016 Phone.Com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CToObjCBridge.h"
#import "SIPConstant.h"

/*!
    @class       SipCallInfo
    @discussion  SipCallInfo objects carries all information about any call, each SipCallInfo object is uniquely identified by a callUUID
*/

@interface SipCallInfo : NSObject

#pragma mark *** Intialise and destroy sip system ***

/// Initializes and returns SipCallInfo object.
///
/// @param call: SipCallInfo object
///
/// - Returns: An initialized SipCallInfo object.
///
- (instancetype _Nonnull)initWithIncomingCall:(SipCallInfo *_Nonnull)call;


/// Initializes and returns SipCallInfo object.
///
/// @param number: Number to make call.
///
/// - Returns: An initialized SipCallInfo object.
///
- (instancetype _Nonnull)initWithNumber:(NSString *_Nonnull)number;


/// Initializes and returns SipCallInfo object.
///
/// @param uri: Sip Uri.
/// @param number: Call UUID.
///
/// - Returns: An initialized SipCallInfo object.
///
- (instancetype)initWithSipUri:(NSString *)uri callUUID:(NSString *)uuid;


/// Initializes and returns SipCallInfo object.
///
/// @param number: Number to make call
/// @param uuid: Unique identifier of call object, each SipCallInfo object is uniquely identified by a callUUID
///
/// - Returns: An initialized SipCallInfo object.
///
- (instancetype _Nonnull)initWithNumber:(NSString *_Nonnull)number callUUID:(NSString *_Nonnull)uuid;


#pragma mark *** Sip call state change handlers ***

/// Call back handler when call accepted
@property (copy, nonatomic) OnCallAccepted _Nullable callAcceptedHandler;

/// Call back handler when call disconnected
@property (copy, nonatomic) OnCallDisConnected _Nullable callDiconnectedHandler;

/// Call back handler when call onHold
@property (copy, nonatomic) OnCallOnHoldCompletion _Nullable callOnHoldCompletionHandler;

/// Call back handler when call rejected
@property (copy, nonatomic) OnCallRejected _Nullable callRejectedHandler;
@property (copy, nonatomic) OnCallRejectFullfillHandler _Nullable callRejectFullfillHandler;

/// Call back handler when call unHold
@property (copy, nonatomic) OnCallUnHoldCompletion _Nullable callUnHoldCompletionHandler;

/// Call back handler when call state changes
@property (copy, nonatomic) OnOutgoingCallStateChanged _Nullable callStateChangedHandler;


#pragma mark *** variables ***

@property (readwrite, nonatomic) BOOL active;

/// Incoming call is ansered or not - populated from IncomingPushCallObject
@property (readwrite, nonatomic) BOOL answered;

/// Incoming call is cancelled or not - populated from IncomingPushCallObject
@property (readwrite, nonatomic) BOOL canceled;
@property (readwrite, nonatomic) BOOL conferenceCall;

/// A Boolean value that indicates whether the provider supports video in addition to audio.
@property (readwrite, nonatomic) BOOL hasVideo;
@property (readwrite, nonatomic) BOOL holdCall;
@property (readwrite, nonatomic) BOOL mute;
@property (readwrite, nonatomic) NSInteger * _Nullable callerContactID;
@property (readwrite, nonatomic) NSInteger callIdx;
@property (readwrite, nonatomic) SIP_CALL_STATE state;

/// It contains call state like - @"calling", @"ringing"
@property (strong, nonatomic) NSString * _Nonnull callState;

/// call status like - @"answered" and @"canceled"
@property (strong, nonatomic) NSString * _Nonnull callStatus;

/// It contains call type like - @"outgoing", @"incoming"
@property (strong, nonatomic) NSString * _Nonnull callType;

/// unique id to identify call
@property (strong, nonatomic) NSString * _Nonnull callUUID;
@property (strong, nonatomic) NSString * _Nonnull callerDID;
@property (strong, nonatomic) NSString * _Nonnull codecName;

/// unique id to identify call
@property (strong, nonatomic) NSString * _Nonnull linkedUUID;

/// call parking ID - user can park call using this ID
@property (strong, nonatomic) NSString * _Nonnull parkingSlot;

/// voip server
@property (strong, nonatomic) NSString * _Nonnull routingServer;

/// caller name
@property (strong, nonatomic) NSString * _Nullable callerCnam;

/// caller number generated for call like - sip:505@stage.sip.phone.com;transport=tcp
@property (strong, nonatomic) NSString * _Nonnull remoteContact;
@property (strong, nonatomic) NSString * _Nonnull pjsuaCallUUID;

@end
