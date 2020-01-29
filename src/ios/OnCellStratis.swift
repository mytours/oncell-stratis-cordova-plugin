import StratisSDK
import Bugsnag

@objc(OnCellStratis) class OnCellStratis : CDVPlugin {
    
    var stratisSdk: StratisSDK!
    var locks = [Lock]()
    var getLocksError = false;
    
    @objc(initSDK:)
    func initSDK(command: CDVInvokedUrlCommand) {
        let serverEnvironmentString = command.arguments[0] as? String ?? ""
        let accessToken = command.arguments[1] as? String ?? ""
        
        Bugsnag.setBreadcrumbCapacity(50)
        Bugsnag.leaveBreadcrumb(withMessage: "serverEnvironent: \(serverEnvironmentString)")
        
        var serverEnv = ServerEnvironment.SANDBOX; // Sandbox by default
        if (serverEnvironmentString == "PROD") {
            serverEnv = ServerEnvironment.PROD;
        }
        
        let configuration = Configuration(
            serverEnvironment: serverEnv,
            accessToken: accessToken,
            remoteLoggingEnabled: true,
            loggingMetadata: ["app": "OnCell"]
        )
        
        stratisSdk = StratisSDK(configuration: configuration)
        
        let message = "{\"success\": 1}"
        let pluginResult = CDVPluginResult(
            status: CDVCommandStatus_OK,
            messageAs: message
        )
        self.commandDelegate!.send(
            pluginResult,
            callbackId: command.callbackId
        )
    }
    
    @objc(getLocks:)
    func getLocks(command: CDVInvokedUrlCommand) {
        
        let propertyId = command.arguments[0] as? String ?? ""
        self.getLocksError = false;
        
        Bugsnag.leaveBreadcrumb(withMessage: "propertyId: \(propertyId)")
        
        let callback = StratisSDKCallback(
                resultCallback: { (res) in
                    Bugsnag.leaveBreadcrumb(withMessage: "getLocks resultCallback: \(res)")
                    guard let locks = res["locks"] as? [[String: Any]] else { return }
                    self.locks = locks.compactMap({ Lock(fromResponse: $0) })
            },
                doneCallback: { (_) in
                    let locksJson = self.getLocksAsJson()
                    if (locksJson == "[]") { self.bugsnagNotify(exceptionName: "getLocksEmpty", exceptionReason: "No locks found by getLocks") }
                    let message = "{\"success\": 1, \"locks\": \(locksJson)}"
                    let pluginResult = CDVPluginResult(
                        status: CDVCommandStatus_OK,
                        messageAs: message
                    )
                    self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
            },
                errorCallback: { (err) in
                    self.getLocksError = true;
                    var message = "{\"success\": 0, \"error\": \"Unable to get locks\"}"
                    if let errorMessage = err["message"] as? String {
                        message = "{\"success\": 0, \"error\": \"\(errorMessage)\"}"
                    }
                    self.bugsnagNotify(exceptionName: "getLocksError", exceptionReason: message)
                    let pluginResult = CDVPluginResult(
                        status: CDVCommandStatus_ERROR,
                        messageAs: message
                    )
                    self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
            }
        )
        
        stratisSdk.getLocks(property: propertyId, callback: callback)
    }
    
    @objc(scanLocks:)
    func scanLocks(command: CDVInvokedUrlCommand) {
        
        let seconds = command.arguments[0] as? Double ?? 0
        var foundLock = false
        
        let callback = StratisSDKCallback(
                resultCallback: { (res) in
                    Bugsnag.leaveBreadcrumb(withMessage: "scanLocks resultCallback: \(res)")
                    guard
                        let lockResponse = res["lock"] as? [String: Any],
                        let scannedLock = Lock(fromResponse: lockResponse),
                        let lock = self.locks.first(where: { $0.lockId == scannedLock.lockId })
                        else { return }
                    lock.enable(lock: scannedLock)
                    foundLock = true
            },
                doneCallback: { (_) in
                    let locksJson = self.getLocksAsJson()
                    if (!foundLock) { self.bugsnagNotify(exceptionName: "scanLocksEmpty", exceptionReason: "No locks found by scanLocks") }
                    let message = "{\"success\": 1, \"locks\": \(locksJson)}"
                    let pluginResult = CDVPluginResult(
                        status: CDVCommandStatus_OK,
                        messageAs: message
                    )
                    self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
            },
                errorCallback: { (err) in
                    var message = "{\"success\": 0, \"error\": \"Unable to scan locks\"}"
                    if let errorMessage = err["message"] as? String {
                        message = "{\"success\": 0, \"error\": \"\(errorMessage)\"}"
                    }
                    self.bugsnagNotify(exceptionName: "scanLocksError", exceptionReason: message)
                    let pluginResult = CDVPluginResult(
                        status: CDVCommandStatus_ERROR,
                        messageAs: message
                    )
                    self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
            }
        )
        
        stratisSdk.scanLocks(seconds: seconds, callback: callback)
    }
    
    @objc(activateLock:)
    func activateLock(command: CDVInvokedUrlCommand) {
        let lockId = command.arguments[0] as? String ?? ""
        let appointmentId = command.arguments[1] as? String ?? ""
        var responseSent = false
        
        Bugsnag.leaveBreadcrumb(withMessage: "lockId: \(lockId)")
        // appointmentId is no longer necessary for the Stratis SDK, but I'm leaving it here for debugging purposes
        Bugsnag.leaveBreadcrumb(withMessage: "appointmentId: \(appointmentId)")
        
        let callback = StratisSDKCallback(
            resultCallback: { (res) in
                Bugsnag.leaveBreadcrumb(withMessage: "activateLock resultCallback: \(res)")
                let resultMessage = res["message"] as? String ?? ""
                if (resultMessage == "ACTIVATION_SUCCESS") {
                    let message = "{\"success\": 1}" //
                    let pluginResult = CDVPluginResult(
                        status: CDVCommandStatus_OK,
                        messageAs: message
                    )
                    self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
                    responseSent = true
                }
            },
            doneCallback: { (_) in
                // Ignore done callbacks here since more than one is sent in the process of activating
                // Use ACTIVATION_SUCCESS result callback instead
            },
            errorCallback: { (err) in
                var message = "{\"success\": 0, \"error\": \"Unable to activate lock\"}"
                if let errorMessage = err["message"] as? String {
                     message = "{\"success\": 0, \"error\": \"\(errorMessage)\"}"
                }
                self.bugsnagNotify(exceptionName: "activateLockError", exceptionReason: message)
                let pluginResult = CDVPluginResult(
                    status: CDVCommandStatus_ERROR,
                    messageAs: message
                )
                self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
                responseSent = true
            }
        )
        
        stratisSdk.activateLock(lockId: lockId, callback: callback)
        
        DispatchQueue.main.asyncAfter(deadline: .now() + 20) {
            if (!responseSent) { // If we haven't responded to the frontend by the timeout (20s)
                let message = "{\"success\": 0, \"error\": \"Lock activation took to long to complete\"}"
                self.bugsnagNotify(exceptionName: "activateLockTimeout", exceptionReason: message)
                let pluginResult = CDVPluginResult(
                    status: CDVCommandStatus_ERROR,
                    messageAs: message
                )
                self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
            }
        }
    }
    
    @objc(getLocksAsJson)
    func getLocksAsJson() -> String {
        var jsonString = "[]"
        if (!self.getLocksError) {
            if (!self.locks.isEmpty) {
                let encoder = JSONEncoder()
                if let jsonData = try? encoder.encode(self.locks) {
                    jsonString = String(data: jsonData, encoding: .utf8) ?? "[]"
                }
            }
        }
        return jsonString
    }
    
    @objc(bugsnagNotify: :)
    func bugsnagNotify(exceptionName:String, exceptionReason:String) {
        let exception = NSException(name:NSExceptionName(rawValue: exceptionName),
                                    reason:exceptionReason,
                                    userInfo:nil)
        Bugsnag.notify(exception)
    }
}

class StratisSDKCallback: ResultCallback {
    let resultCallback: (([String: Any]) -> Void)?
    let doneCallback: (([String: Any]) -> Void)?
    let errorCallback: (([String: Any]) -> Void)?
    let messageCallback: ((String) -> Void)?
    
    init(
        resultCallback: (([String: Any]) -> Void)? = nil,
        doneCallback: (([String: Any]) -> Void)? = nil,
        errorCallback: (([String: Any]) -> Void)? = nil,
        messageCallback: ((String) -> Void)? = nil
        ) {
        self.resultCallback = resultCallback
        self.doneCallback = doneCallback
        self.errorCallback = errorCallback
        self.messageCallback = messageCallback
    }
    
    func result(res: [String: Any]) {
        NSLog("Result callback called with: \(res)")
        if let message = res["message"] as? String {
            self.messageCallback?(message)
        }
        self.resultCallback?(res)
    }
    
    func done(done: [String: Any]) {
        NSLog("Done callback called with: \(done)")
        self.doneCallback?(done)
    }
    
    func error(err: [String: Any]) {
        NSLog("Error callback called with: \(err)")
        if let message = err["message"] as? String {
            self.messageCallback?(message)
        }
        self.errorCallback?(err)
    }
}


class Lock: Codable{
    var lockId: String
    var name: String
    var model: String
    var unlockTechnology: String
    var rssi: Int
    var isEnabled = false
    
    init?(fromResponse res: [String: Any]) {
        guard
            let lockId = res["id"] as? String,
            let name = res["name"] as? String,
            let model = res["model"] as? String,
            let unlockTechnology = res["unlock_technology"] as? String
            else { return nil }
        self.lockId = lockId
        self.name = name
        self.model = model
        self.unlockTechnology = unlockTechnology
        self.rssi = res["rssi"] as? Int ?? 0
    }
    
    func enable(lock: Lock) {
        self.isEnabled = true
        self.rssi = lock.rssi
    }
}
