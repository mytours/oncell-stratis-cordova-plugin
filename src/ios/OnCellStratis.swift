@objc(OnCellStratis) class OnCellStratis : CDVPlugin {
    
  @objc(setAccessToken:)
  func setAccessToken(command: CDVInvokedUrlCommand) {
    var pluginResult = CDVPluginResult(
      status: CDVCommandStatus_ERROR
    )

    let msg = command.arguments[0] as? String ?? ""

    if msg.characters.count > 0 {
      let toastController: UIAlertController =
        UIAlertController(
          title: "",
          message: msg,
          preferredStyle: .alert
        )
      
      self.viewController?.present(
        toastController,
        animated: true,
        completion: nil
      )

      DispatchQueue.main.asyncAfter(deadline: .now() + 3) {
        toastController.dismiss(
          animated: true,
          completion: nil
        )
      }
        
      pluginResult = CDVPluginResult(
        status: CDVCommandStatus_OK,
        messageAs: msg
      )
    }

    self.commandDelegate!.send(
      pluginResult,
      callbackId: command.callbackId
    )
  }
  
  @objc(setServerEnvironment:)
  func setServerEnvironment(command: CDVInvokedUrlCommand) {
    var pluginResult = CDVPluginResult(
      status: CDVCommandStatus_ERROR
    )
    self.commandDelegate!.send(
      pluginResult,
      callbackId: command.callbackId
    )
  }
  
  @objc(getLocks:)
  func getLocks(command: CDVInvokedUrlCommand) {
    var pluginResult = CDVPluginResult(
      status: CDVCommandStatus_ERROR
    )
    self.commandDelegate!.send(
      pluginResult,
      callbackId: command.callbackId
    )
  }
  
  @objc(scanLocks:)
  func scanLocks(command: CDVInvokedUrlCommand) {
    var pluginResult = CDVPluginResult(
      status: CDVCommandStatus_ERROR
    )
    self.commandDelegate!.send(
      pluginResult,
      callbackId: command.callbackId
    )
  }
  
  @objc(activateLock:)
  func activateLock(command: CDVInvokedUrlCommand) {
    var pluginResult = CDVPluginResult(
      status: CDVCommandStatus_ERROR
    )
    self.commandDelegate!.send(
      pluginResult,
      callbackId: command.callbackId
    )
  }
}
