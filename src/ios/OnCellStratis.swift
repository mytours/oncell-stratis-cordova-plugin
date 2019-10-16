import StratisSDK

@objc(OnCellStratis) class OnCellStratis : CDVPlugin {
    
    var stratisSdk: StratisSDK!
    var locks = [Lock]()
    
    @objc(pluginInitialize)
    override func pluginInitialize() {
        let callback = StratisSDKCallback { (message) in
            NSLog(message);
        }
        stratisSdk = StratisSDK(initCallback: callback)
    }
    
    @objc(setAccessToken:)
    func setAccessToken(command: CDVInvokedUrlCommand) {
        
        let accessToken = command.arguments[0] as? String ?? ""
        
        let callback = StratisSDKCallback()
        stratisSdk.setAccessToken(token: accessToken, callback: callback)
        
        //    var pluginResult = CDVPluginResult(
        //      status: CDVCommandStatus_ERROR
        //    )
        
        let message = "{\"success\": 1, \"accessToken\": \"\(accessToken)\"}"
        
        let pluginResult = CDVPluginResult(
            status: CDVCommandStatus_OK,
            messageAs: message
        )
        
        self.commandDelegate!.send(
            pluginResult,
            callbackId: command.callbackId
        )
    }
    
    @objc(setServerEnvironment:)
    func setServerEnvironment(command: CDVInvokedUrlCommand) {
        
        let serverEnvironmentString = command.arguments[0] as? String ?? ""
        let serverEnvironment = ServerEnvironment(rawValue: serverEnvironmentString)!
        
        let callback = StratisSDKCallback()
        stratisSdk.setServerEnvironment(environment: serverEnvironment, callback: callback)
        
        //    var pluginResult = CDVPluginResult(
        //      status: CDVCommandStatus_ERROR
        //    )
        
        let message = "{\"success\": 1, \"serverEnvironment\": \"\(serverEnvironmentString)\"}"
        
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
        let pluginResult = CDVPluginResult(
            status: CDVCommandStatus_ERROR
        )
        self.commandDelegate!.send(
            pluginResult,
            callbackId: command.callbackId
        )
    }
    
    @objc(scanLocks:)
    func scanLocks(command: CDVInvokedUrlCommand) {
        let pluginResult = CDVPluginResult(
            status: CDVCommandStatus_ERROR
        )
        self.commandDelegate!.send(
            pluginResult,
            callbackId: command.callbackId
        )
    }
    
    @objc(activateLock:)
    func activateLock(command: CDVInvokedUrlCommand) {
        let pluginResult = CDVPluginResult(
            status: CDVCommandStatus_ERROR
        )
        self.commandDelegate!.send(
            pluginResult,
            callbackId: command.callbackId
        )
    }
}


struct StratisSDKCallback: ResultCallback {
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
        DispatchQueue.main.async {
            NSLog("Result callback called with: \(res)")
            if let message = res["message"] as? String {
                self.messageCallback?(message)
            }
            self.resultCallback?(res)
        }
    }
    
    func done(done: [String: Any]) {
        DispatchQueue.main.async {
            NSLog("Done callback called with: \(done)")
            self.doneCallback?(done)
        }
    }
    
    func error(err: [String: Any]) {
        DispatchQueue.main.async {
            NSLog("Error callback called with: \(err)")
            if let message = err["message"] as? String {
                self.messageCallback?(message)
            }
            self.errorCallback?(err)
        }
    }
}


class Lock {
    var lockId: String
    var name: String
    var model: String
    var unlockTechnology: String
    var rssi: NSNumber?
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
        rssi = res["rssi"] as? NSNumber
    }
    
    func enable(lock: Lock) {
        isEnabled = true
        rssi = lock.rssi
    }
}
