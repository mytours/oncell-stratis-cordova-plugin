#import <Cordova/CDVPlugin.h>

@interface OnCellStratis : CDVPlugin

- (void)setServerEnvironment:(CDVInvokedUrlCommand*)command;
- (void)setAccessToken:(CDVInvokedUrlCommand*)command;
- (void)getLocks:(CDVInvokedUrlCommand*)command;
- (void)scanLocks:(CDVInvokedUrlCommand*)command;
- (void)activateLock:(CDVInvokedUrlCommand*)command;

@end
