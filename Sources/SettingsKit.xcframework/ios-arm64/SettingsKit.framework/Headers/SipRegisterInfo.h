//
//  SipRegisterInfo.h
//  PhoneSipManager
//
//  Created by vTechnolabs on 03/03/20.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SipRegisterInfo : NSObject <NSCopying>

/// voip server like - "stage.sip.phone.com"
@property (nonatomic, copy) NSString* _Nonnull domain;

/// user id
@property (nonatomic, copy) NSString* _Nonnull user;

/// user password
@property (nonatomic, copy) NSString* _Nonnull password;

/// transport protocol like "tcp"
@property (nonatomic, copy) NSString* _Nonnull protocol;

/// unique device identifier
@property (nonatomic, copy) NSString* _Nonnull deviceToken;

/// A value that indicates whether debugMode is ON or OFF. On = 1, Off = 0
@property (nonatomic, copy) NSString* _Nonnull debugMode;

/// device type like "iphone"
@property (nonatomic, copy) NSString* _Nonnull deviceType;

/// app version
@property (nonatomic, copy) NSString* _Nonnull appVersion;

/// app bundle identifier, use - Bundle.main.bundleIdentifier
@property (nonatomic, copy) NSString* _Nonnull applicationBundleID;

/// device info, use - UIDevice.current.identifierForVendor!.uuidString
@property (nonatomic, copy) NSString* _Nonnull deviceInfo;

/// application ID like "arn:aws:sns:us-west-2:467525865813:app/APNS_VOIP/Liftmaster"
@property (nonatomic, copy) NSString* _Nonnull applicationId;

@property (nonatomic, copy) NSString* _Nonnull voipID;
@property (nonatomic, copy) NSString* _Nonnull voipPhoneID;
@property (nonatomic, copy) NSString* _Nonnull logFileName;
@property (nonatomic) BOOL srtp;

@end

NS_ASSUME_NONNULL_END
