//
//  IncomingPushCallObject.h
//  MobileOffice
//
//  Created by Dheeraj Katarya on 4/5/17.
//  Copyright © 2017 Phone.Com. All rights reserved.
//

#import <Foundation/Foundation.h>
/// Modal object to store incoming push information
@interface IncomingPushCallObject : NSObject

/*! @brief is call answered on other device */
/// is call answered on other device.
@property (nonatomic,readwrite)BOOL answered;

/// has call status update available
@property (nonatomic,readwrite)BOOL callStatusUpdate;

/*! @brief call canceled on other device */
/// call canceled on other device
@property (nonatomic,readwrite)BOOL canceled;

/// Unique id (string) to identify device
@property (nonatomic,strong) NSString *deviceUUidString;

/*! @brief caller number */
/// caller number
@property (nonatomic,strong) NSString *from;

/*! @brief unique id to identify call */
/// unique id to identify call
@property (nonatomic,strong) NSString *linkedUUidString;

/*! @brief voip server */
/// voip server
@property (nonatomic,strong) NSString *server;

/*! @brief call parking ID - user can park call using this ID */
/// call parking ID - user can park call using this ID
@property (nonatomic,strong) NSString *slot;

/*! @brief call state like - @"calling", @"ringing" */
/// call state like - @"calling", @"ringing"
@property (nonatomic,strong) NSString *state;

/*! @brief call status like - @"answered" and @"canceled" */
/// call status like - @"answered" and @"canceled"
@property (nonatomic,strong) NSString *status;

/*! @brief It contains call type like - @"outgoing", @"incoming" */
/// It contains call type like - @"outgoing", @"incoming"
@property (nonatomic,strong) NSString *type;

/// unique id to identify device
@property (nonatomic,strong) NSUUID *deviceUUid;

/*! @brief unique id to identify call */
/// unique id to identify call
@property (nonatomic,strong) NSUUID *linkedUUID;

/*! @brief caller name */
/// caller name
@property (nonatomic,strong) NSString *callerName;

/*! @brief caller name */
/// caller
@property (nonatomic,strong) NSString *caller;


/*!
   @brief       Initializes and returns IncomingPushCallObject object.

   @param       pushPayloadDictionary
                Contains all info like server, slot, status - to populate IncomingPushCallObject object
 
  @return       An initialized IncomingPushCallObject object.
*/

/// Initializes and returns IncomingPushCallObject object.
///
/// @param pushPayloadDictionary: Contains all info like server, slot, status - to populate IncomingPushCallObject object
///
/// - Returns: An initialized IncomingPushCallObject object.
/// 
- (instancetype)initWithPushNotifyPayload:(NSDictionary *)pushPayloadDictionary;

@end
