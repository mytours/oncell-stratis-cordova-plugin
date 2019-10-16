import StratisSDK

@objc(OnCellStratis) class OnCellStratis : CDVPlugin {
    
    @objc(pluginInitialize)
    override func pluginInitialize() {
        
    }
    
    @objc(setAccessToken:)
    func setAccessToken(command: CDVInvokedUrlCommand) {
        
        //    let arg = command.arguments[0] as? String ?? ""
        
        //    var pluginResult = CDVPluginResult(
        //      status: CDVCommandStatus_ERROR
        //    )
        
        let message = "{\"success\": 1, \"accessToken\": \"test-access-token\"}"
        
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
        let pluginResult = CDVPluginResult(
            status: CDVCommandStatus_ERROR
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
