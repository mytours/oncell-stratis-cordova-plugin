import StratisSDK
import Bugsnag

@objc(OnCellStratis) class OnCellStratis : CDVPlugin {
    
    var stratisSdk: StratisSDK!
    var onCellStratisDeviceAccessDelegate: OnCellStratisDeviceAccessDelegate!
    var onCellStratisDeviceDiscoveryDelegate: OnCellStratisDeviceDiscoveryDelegate!
    var accessibleLocks: [StratisLock] = []
    var discoveredLocks: [StratisLock] = []
    
    // Begin command functions
    
    @objc(initSDK:)
    func initSDK(command: CDVInvokedUrlCommand) {
        NSLog("initSDK")
        
        let serverEnvironmentString = command.arguments[0] as? String ?? ""
        let accessToken = command.arguments[1] as? String ?? ""
        let propertyID = command.arguments[2] as? String ?? ""

        Bugsnag.setBreadcrumbCapacity(50)
        Bugsnag.leaveBreadcrumb(withMessage: "Initializing Stratis SDK serverEnvironmentString: \(serverEnvironmentString), accessToken: \(accessToken), propertyId: \(propertyID)")

        var serverEnv = ServerEnvironment.SANDBOX // Sandbox by default
        if serverEnvironmentString == "PROD" {
            serverEnv = ServerEnvironment.PROD;
        }

        let configuration = Configuration(
            serverEnvironment: serverEnv,
            accessToken: accessToken,
            propertyID: propertyID,
            remoteLoggingEnabled: true,
            loggingMetadata: ["app": "OnCell"]
        )

//        if stratisSdk == nil { // workaround for SDK bug where multiple StratisSDK inits cause lock activation to stall
            stratisSdk = StratisSDK(configuration: configuration)
//        }
        
        self.accessibleLocks = [StratisLock]()
        self.discoveredLocks = [StratisLock]()

        callbackSuccess(callbackId: command.callbackId, locksJSON: nil)
    }
    
    @objc(getLocks:)
    func getLocks(command: CDVInvokedUrlCommand) {
        NSLog("getLocks")

        if self.stratisSdk != nil {
            self.accessibleLocks.removeAll()
            
            self.onCellStratisDeviceAccessDelegate = OnCellStratisDeviceAccessDelegate(onCellStratis: self, callbackId: command.callbackId)
            stratisSdk.deviceAccessDelegate = self.onCellStratisDeviceAccessDelegate

            stratisSdk.fetchAccessibleDevices()
        } else {
            callbackError(callbackId: command.callbackId, errorMessage: "Cannot get lock authorization before initializing StratisSDK")
        }
    }
    
    class OnCellStratisDeviceAccessDelegate: StratisDeviceAccessDelegate {
        var onCellStratis: OnCellStratis!
        var callbackId = ""
        
        init(onCellStratis: OnCellStratis, callbackId: String) {
            self.onCellStratis = onCellStratis
            self.callbackId = callbackId
        }
        
        func stratisDeviceAccessRequestCompleted(_ stratisSDK: StratisSDK, devices: [StratisLock], error: StratisError?) {
            NSLog("stratisDeviceAccessRequestCompleted result: \(devices)")
            if error == nil {
                onCellStratis.accessibleLocks = devices
                if onCellStratis.accessibleLocks.isEmpty {
                    onCellStratis.bugsnagNotify(exceptionName: "lockException", exceptionReason: "No accessible locks found")
                }
                let locksJson = onCellStratis.getLocksAsJson(locks: onCellStratis.accessibleLocks)
                Bugsnag.leaveBreadcrumb(withMessage: "accessibleLocks: \(locksJson)")
                onCellStratis.callbackSuccess(callbackId: callbackId, locksJSON: locksJson)
            } else {
                onCellStratis.callbackError(callbackId: callbackId, errorMessage: error!.debugDescription)
            }
        }
    }
    

    @objc(scanLocks:)
    func scanLocks(command: CDVInvokedUrlCommand) {
        NSLog("scanLocks")
        
        if !self.accessibleLocks.isEmpty {
            self.discoveredLocks.removeAll()
            
            self.onCellStratisDeviceDiscoveryDelegate = OnCellStratisDeviceDiscoveryDelegate(onCellStratis: self, callbackId: command.callbackId)
            stratisSdk.deviceDiscoveryDelegate = self.onCellStratisDeviceDiscoveryDelegate
            
            stratisSdk.discoverActionableDevices(self.accessibleLocks)
        } else {
            callbackError(callbackId: command.callbackId, errorMessage: "Cannot scan locks before getting lock authorization")
        }
    }
    
    class OnCellStratisDeviceDiscoveryDelegate: StratisDeviceDiscoveryDelegate {
        var onCellStratis: OnCellStratis!
        var callbackId = ""
        
        init(onCellStratis: OnCellStratis, callbackId: String) {
            self.onCellStratis = onCellStratis
            self.callbackId = callbackId
        }
        
        func stratisDiscoveredDevices(_ stratisSDK: StratisSDK, devices: [StratisLock]) {
            NSLog("stratisDiscoveredDevices result: \(devices)")
            onCellStratis.discoveredLocks.append(contentsOf: devices)
        }

        func stratisDiscoveryEncounteredError(_ stratisSDK: StratisSDK, error: StratisError) {
            NSLog("stratisDiscoveryEncounteredError: \(error)")
            onCellStratis.callbackError(callbackId: callbackId, errorMessage: error.debugDescription)
        }

        func stratisDiscoveryCompleted(_ stratisSDK: StratisSDK) {
            NSLog("stratisDiscoveryCompleted")
            if onCellStratis.discoveredLocks.isEmpty {
                onCellStratis.bugsnagNotify(exceptionName: "lockException", exceptionReason: "No scanned locks discovered")
            }
            let locksJson = onCellStratis.getLocksAsJson(locks: onCellStratis.discoveredLocks)
            Bugsnag.leaveBreadcrumb(withMessage: "discoveredLocks: \(locksJson)")
            onCellStratis.callbackSuccess(callbackId: callbackId, locksJSON: locksJson)
        }
    }

    @objc(activateLock:)
    func activateLock(command: CDVInvokedUrlCommand) {
        
        let lockId = command.arguments[0] as? String ?? ""
        let appointmentId = command.arguments[1] as? String ?? ""
        NSLog("activateLock lockId: \(lockId) appointmentId: \(appointmentId)")
        Bugsnag.leaveBreadcrumb(withMessage: "lockId: \(lockId)")
        Bugsnag.leaveBreadcrumb(withMessage: "appointmentId: \(appointmentId)")
        
        if !self.discoveredLocks.isEmpty {
            var foundLock = false
            for lock in self.discoveredLocks {
                if lock.identifier == lockId {
                    let deviceToActivate = lock
                    foundLock = true
                    let onCellStratisDeviceActivationDelegate = OnCellStratisDeviceActivationDelegate(onCellStratis: self, callbackId: command.callbackId)
                    deviceToActivate.activationDelegate = onCellStratisDeviceActivationDelegate
                    NSLog("Calling activate() on lock \(lockId)...")
                    deviceToActivate.activate()
                    // return error to JS and send log to Bugsnag if we haven't unlocked device in 20 seconds
                    onCellStratisDeviceActivationDelegate.startActivationTimer()
                    break
                }
            }
            if !foundLock {
                callbackError(callbackId: command.callbackId, errorMessage: "Cannot find lock to activate")
            }
        } else {
            callbackError(callbackId: command.callbackId, errorMessage: "No discovered locks to activate")
        }
    }
    
    class OnCellStratisDeviceActivationDelegate: StratisDeviceActivationDelegate {
        var onCellStratis: OnCellStratis!
        var callbackId = ""
        var responseSent = false
        
        init(onCellStratis: OnCellStratis, callbackId: String) {
            self.onCellStratis = onCellStratis
            self.callbackId = callbackId
        }
        
        func stratisDeviceActivationDidPostEvent(_ event: StratisLock.ActivationEvent, forDevice device: StratisLock, withError error: StratisError?) {
            NSLog("stratisDeviceActivationDidPostEvent with callbackId: \(self.callbackId), event: \(event), forDevice: \(device), error: \(String(describing: error))")
            if error == nil {
                if event.rawValue == ActivationEvent.activationStarted.rawValue {
                    NSLog("activationStarted");
                } else if event.rawValue == ActivationEvent.activationComplete.rawValue {
                    NSLog("activationComplete");
                    onCellStratis.callbackSuccess(callbackId: callbackId, locksJSON: nil)
                    responseSent = true;
                } else if event.rawValue == ActivationEvent.presentDeviceToLock.rawValue {
                    NSLog("presentDeviceToLock");
                }
            } else {
                onCellStratis.callbackError(callbackId: callbackId, errorMessage: error.debugDescription)
                responseSent = true;
            }
        }
        
        func startActivationTimer() {
            DispatchQueue.main.asyncAfter(deadline: .now() + 20) {
                if !self.responseSent { // If we haven't responded to the frontend by the timeout (20s)
                    self.onCellStratis.callbackError(callbackId: self.callbackId, errorMessage: "Lock activation took too long")
                }
            }
        }
    }
    
    // End command functions
    
    // Begin utility functions
    
    func callbackSuccess(callbackId: String, locksJSON: String?) {
        var message = "{\"success\": 1}"
        if locksJSON != nil {
            message = "{\"success\": 1, \"locks\": \(locksJSON!)}"
        }
        let pluginResult = CDVPluginResult(
            status: CDVCommandStatus_OK,
            messageAs: message
        )
        self.commandDelegate!.send(
            pluginResult,
            callbackId: callbackId
        )
    }
    
    func callbackError(callbackId: String, errorMessage: String) {
        NSLog(errorMessage)
        bugsnagNotify(exceptionName: "LockException", exceptionReason: errorMessage)
        let message = "{\"success\": 0, \"error\": \"\(errorMessage)\"}"
        let pluginResult = CDVPluginResult(
            status: CDVCommandStatus_ERROR,
            messageAs: message
        )
        self.commandDelegate!.send(pluginResult, callbackId: callbackId)
    }
    
    func bugsnagNotify(exceptionName:String, exceptionReason:String) {
        let exception = NSException(name:NSExceptionName(rawValue: exceptionName),
                                    reason:exceptionReason,
                                    userInfo:nil)
        Bugsnag.notify(exception)
    }
    
    func getLocksAsJson(locks: [StratisLock]) -> String {
        var jsonString = "[]"
        if !locks.isEmpty {
            var codableLocks = locks.compactMap({ $0.toCodable() })
            codableLocks.sort(by: {$0.rssi > $1.rssi}) // sort by RSSI in descending order
            let encoder = JSONEncoder()
            if let jsonData = try? encoder.encode(codableLocks) {
                jsonString = String(data: jsonData, encoding: .utf8) ?? "[]"
            }
        }
        return jsonString
    }
    
    // End utility functions
    
}


struct CodableLock: Codable {
    var identifier: String
    var name: String
    var model: String
    var isActionable: Bool
    var rssi: Int
}


extension StratisLock {
    
    func toCodable() -> CodableLock{
        var rssi = -100;
        // Add rssi to CodableLock if available
        if let bleLock = self as? BLELock {
            rssi = bleLock.rssi?.intValue ?? -100;
        }
        let codableLock = CodableLock(
            identifier: self.identifier,
            name: self.name,
            model: self.model,
            isActionable: self.actionable,
            rssi: rssi
        )
        
        return codableLock
    }
}
