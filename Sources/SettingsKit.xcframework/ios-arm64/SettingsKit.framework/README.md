# Video SDK

HI THIS IS THE SUMMARY
## Topics
1. [SDK Installation](#sdk-installation)
2. [Xcode configration](#xcode-configration)
3. [Apple Framework](#apple-framework)
   1. [Pushkit](#pushkit)
   2. [Callkit](#callkit)
4. [Push Configration](#push-configration)
5. [SDK Usage](#sdk-usage)
    1. [SDK initialization](#sdk-initialization)
    2. [SIP Registration](#sip-registration)
    3. [Incoming call](#incoming-call)
    4. [Answer call](#answer-call)
    5. [Reinvite Flow](#reinvite-flow)
    6. [HangUP Flow](#hangup-flow)
    7. [Enter Background](#enter-background)
    8. [Enter foreground](#enter-foreground)
6. [Debugging](#debugging)


## SDK Installation

Create a pod file and add following source.

### Private Repo for Phone.com SDK
```shell
source 'git@github.com:theappscience/phonesipspec.git' 
```

### Default Pod Specs
```shell
source 'https://github.com/CocoaPods/Specs.git'
```

The sdk is installed using CocoaPods.

  ```shell 
  pod repo update
  ``` 
  
  ```shell
   pod install 
   ``` 
  Sample Pod file
![The SDK can be installed using Cocos pods.](/Users/vtechnolabs/Documents/Gaurav/C/LiftMaster/Documentation/pods.png)

## Xcode configration

 ![The SDK can be installed using Cocos pods.](/Users/vtechnolabs/Documents/Gaurav/C/LiftMaster/Documentation/xcode.png)

## Apple Framework

## Pushkit

The PushKit framework supports specialized notifications for updating your watchOS complications, responding to file provider changes, and receiving incoming Voice-over-IP (VoIP) calls. PushKit notifications differ from the ones you handle with the User Notifications framework. Instead of displaying an alert, badging your app’s icon, or playing a sound, PushKit notifications wake up or launch your app and give it time to respond. Both PushKit and User Notifications use the Apple Push Notification service (APNs) to deliver push notifications to user devices.

To receive PushKit notifications, your app creates a PKPushRegistry object and uses it to configure the notification types it supports. When registration is successful, PushKit delivers a unique data token to your app that contains the identity of the current device and the push type. Forward that token along to the server, and include it in any notifications you send to the user. APNs uses the token to deliver the correct type of notification to the user's device.
  
## Callkit
Use CallKit to integrate your calling services with other call-related apps on the system. CallKit provides the calling interface, and you handle the back-end communication with your VoIP service. For incoming and outgoing calls, CallKit displays the same interfaces as the Phone app, giving your app a more native look and feel. CallKit also responds appropriately to system-level behaviors such as Do Not Disturb.

In addition to handling calls, you can provide a Call Directory app extension to provide caller ID information and a list of blocked numbers associated with your service.

## Push Configration

## SDK Usage


### SDK initialization
First set up CallKitManager
After that initailze SipRegisterInfo object and call - (void)initSipSystem:(SipRegisterInfo *_Nonnull)registerInfo;

    
```swift 
func getRegisterInfo() -> SipRegisterInfo {
    
    var registerInfo: SipRegisterInfo = SipRegisterInfo.init()
             
    registerInfo.deviceToken = UserDefaults.standard.string(forKey: deviceTokenKey) ?? ""
    registerInfo.domain = "stage.sip.phone.com"
    registerInfo.user = "227641"
    registerInfo.password = "uctN2%Cpyge5j3"
    registerInfo.protocol = "tcp"
        
    registerInfo.voipID = "2444564"
    registerInfo.voipPhoneID = "2009201"
    registerInfo.srtp = false
             
    #if DEBUG
        registerInfo.debugMode = "1"
        registerInfo.applicationId = "arn:aws:sns:us-west-2:467525865813:app/APNS_VOIP_SANDBOX/LiftMaster-testing"
    #else
        registerInfo.debugMode = "0"
        registerInfo.applicationId = "arn:aws:sns:us-west-2:467525865813:app/APNS_VOIP/Liftmaster"
    #endif
         
    registerInfo.deviceType = "iphone"
    registerInfo.appVersion = Bundle.main.infoDictionary?["CFBundleShortVersionString"] as! String
    registerInfo.applicationBundleID = Bundle.main.bundleIdentifier!
    registerInfo.deviceInfo = UIDevice.current.identifierForVendor!.uuidString
        
    return registerInfo
}
        
func setUpSipSystem() {
                    
    // Must call this method to manage call activities properly.
    SipManagerBridge.sharedManager().setUpCallKit()
            
    // Save values - will requires to create sip account
    // Must call this function before 'checkVOIPSystemStatus'.
    SipManagerBridge.sharedManager().initSipSystem(self.getRegisterInfo())
}
        
``` 

### SIP Registration
Once SipRegisterInfo object values saved in system then call - (void)checkVOIPSystemStatus; 

```swift 
func setUpSipSystem() {
        
    // Must call this method to manage call activities properly.
    SipManagerBridge.sharedManager().setUpCallKit()
            
    // Save values - will requires to create sip account
    // Must call this function before 'checkVOIPSystemStatus'.
    SipManagerBridge.sharedManager().initSipSystem(self.getRegisterInfo())
            
    // Will check application registered to SIP server or not.
    // If application is not registered then this method will register it automatically.
    SipManagerBridge.sharedManager().checkVOIPSystemStatus()
}
           
``` 
    
### Incoming call
For incoming calls we need to configured PushRegistryManager 
    
```swift 
class AppDelegate: UIResponder, UIApplicationDelegate {
     
    var pushRegistry: PKPushRegistry?
    var callUUID: String?
        
        
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {

        // Registers the PKPushRegistry object for type 'PKPushTypeVoIP'
        // Must call this function in Appdelegate, the success of the request is reported to delegate object. For a successful registration, PushRegistryManager delivers a device token to the delegate.
        // Implement PushRegistryManagerDelegate Protocol 
        PushRegistryManager.shared().registerForPushKit()
        PushRegistryManager.shared().delegate = self
        
        // Highly recommended to save PKPushRegistry object in Appdelegate for smooth functioning 
        self.pushRegistry = PushRegistryManager.shared().pushRegistry()
            
        setUpSipSystem()
        
        return true
    }
        
    func setUpSipSystem() {
        
        // Must call this method to manage call activities properly.
        SipManagerBridge.sharedManager().setUpCallKit()
            
        // Save values - will requires to create sip account
        // Must call this function before 'checkVOIPSystemStatus'.
        SipManagerBridge.sharedManager().initSipSystem(self.getRegisterInfo())
            
        // Will check application registered to SIP server or not.
        // If application is not registered then this method will register it automatically.
        SipManagerBridge.sharedManager().checkVOIPSystemStatus()
    }
}
    
extension AppDelegate: PushRegistryManagerDelegate {
    
    func didReceivedIncomingCall(_ payload: PKPushPayload, forType type: PKPushType, 
                            withCompletionHandler callDidCompleted: @escaping () -> Void) {
        
        // Never block main thread on Incoming call delegate method, blocking of main thread would crash the application. 
        if SipManagerBridge.sharedManager().getStoreAccountState() == SIP_STORE_ACCOUNT_STATE_UNREGISTERED {

            SipManagerBridge.sharedManager().registerationHandler = { (state : SIP_STORE_ACCOUNT_STATE) -> () in
                if (state == SIP_STORE_ACCOUNT_STATE_REGISTERED) {
                        SipManagerBridge.sharedManager().registerationHandler = nil
                        return
                }
            }

            SipManagerBridge.sharedManager().initSipSystem(self.getRegisterInfo())
        }
        SipManagerBridge.sharedManager().processIncomingCallForpayLoad(payload, forType: type, withCompletionHandler: callDidCompleted)
    }
}
           
``` 
    
### Answer call

```swift 
class AppDelegate: UIResponder, UIApplicationDelegate {
     
    var pushRegistry: PKPushRegistry?
    var callUUID: String?
        
        
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {

        // Registers the PKPushRegistry object for type 'PKPushTypeVoIP'
        // Must call this function in Appdelegate, the success of the request is reported to delegate object. For a successful registration, PushRegistryManager delivers a device token to the delegate.
        // Implement PushRegistryManagerDelegate Protocol 
        PushRegistryManager.shared().registerForPushKit()
        PushRegistryManager.shared().delegate = self
        
        // Highly recommended to save PKPushRegistry object in Appdelegate for smooth functioning 
        self.pushRegistry = PushRegistryManager.shared().pushRegistry()
            
        setUpSipSystem()
        
        return true
    }
        
    func setUpSipSystem() {
        
        // Must call this method to manage call activities properly.
        SipManagerBridge.sharedManager().setUpCallKit()
            
        // Save values - will requires to create sip account
        // Must call this function before 'checkVOIPSystemStatus'.
        SipManagerBridge.sharedManager().initSipSystem(self.getRegisterInfo())
            
        // Will check application registered to SIP server or not.
        // If application is not registered then this method will register it automatically.
        SipManagerBridge.sharedManager().checkVOIPSystemStatus()
            
        // Set up call receiver handler
        setCallHandler()
    }
        
    func setCallHandler() {
        let sipBridge: SipManagerBridge = SipManagerBridge.sharedManager()
              
        // Incoming call receiver handler
        // Closure will pass received call object - SipCallInfo
        sipBridge.incomingCallRecievedHandler = { callinfo in
            
            // save call identifier for future refernce 
            self.callUUID = callinfo.callUUID
        
            // once call object available, set up call object handlers
            // Set up Call accepted handler
            callinfo.callAcceptedHandler = { _ in
                // call accepted 
            }
        }
    }
}
           
``` 
    
### Reinvite Flow
    
```swift 
func applicationDidBecomeActive(_ application: UIApplication) {
    
    // When application entered in background - current call video will be stopped. 
    // Call "reinviteCall" to start the video again
    if let callID = self.callUUID {
            SipManagerBridge.sharedManager().reinviteCall(callID)
        }
    }
``` 
    
### HangUP Flow
    
```swift 
class AppDelegate: UIResponder, UIApplicationDelegate {
     
    var pushRegistry: PKPushRegistry?
    var callUUID: String?
        
        
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {

        // Registers the PKPushRegistry object for type 'PKPushTypeVoIP'
        // Must call this function in Appdelegate, the success of the request is reported to delegate object. For a successful registration, PushRegistryManager delivers a device token to the delegate.
        // Implement PushRegistryManagerDelegate Protocol 
        PushRegistryManager.shared().registerForPushKit()
        PushRegistryManager.shared().delegate = self
        
        // Highly recommended to save PKPushRegistry object in Appdelegate for smooth functioning 
        self.pushRegistry = PushRegistryManager.shared().pushRegistry()
            
        setUpSipSystem()
        
        return true
    }
        
    func setUpSipSystem() {
        
        // Must call this method to manage call activities properly.
        SipManagerBridge.sharedManager().setUpCallKit()
            
        // Save values - will requires to create sip account
        // Must call this function before 'checkVOIPSystemStatus'.
        SipManagerBridge.sharedManager().initSipSystem(self.getRegisterInfo())
            
        // Will check application registered to SIP server or not.
        // If application is not registered then this method will register it automatically.
        SipManagerBridge.sharedManager().checkVOIPSystemStatus()
            
        // Set up call receiver handler
        setCallHandler()
    }
        
    func setCallHandler() {
        
        let sipBridge: SipManagerBridge = SipManagerBridge.sharedManager()
              
        // Incoming call receiver handler
        // Closure will pass received call object - SipCallInfo
        sipBridge.incomingCallRecievedHandler = { callinfo in
            
            // save call identifier for future refernce 
            self.callUUID = callinfo.callUUID
        
            // once call object available, set up call object handlers
            // Set up Call accepted handler
            callinfo.callAcceptedHandler = { _ in
                // call accepted 
            }
        }
                
        // Set up Call disconnected handler
        callinfo.callDiconnectedHandler = { _ in
            // call disconnected 
        }
    }
}
           
``` 
    
### Enter Background
    
```swift 
func applicationDidEnterBackground(_ application: UIApplication) {
        
    DispatchQueue.main.async {
        // Once application entered in background, prefer to destroy SIP stack if no current call available 
        // Highly recommended to destroy SIP stack on main thread
        self.configureForBackground()
    }
}
    
func configureForBackground() {
        
    let currentState = SipManagerBridge.sharedManager().getStoreAccountState()
    let calls = SipDataManager.shared().arrVoipCalls.count
        
    if
        calls == 0,
        currentState == SIP_STORE_ACCOUNT_STATE_REGISTERED,
        !SipManagerBridge.isApplicationInForeGround() {
        SipManagerBridge.sharedManager().destroyStack()
    }
}
           
``` 
    
### Enter foreground
    
```swift 
func applicationWillEnterForeground(_ application: UIApplication) {
       
    DispatchQueue.main.async {
        // Will check application registered to SIP server or not.
        // If application is not registered then this method will register it automatically..
        // Call this function when application will enter foreground
        SipManagerBridge.sharedManager().checkVOIPSystemStatus()
    }
}
           
``` 
    
### Debugging
    
          ```swift 
           
       ``` 


## Debugging
