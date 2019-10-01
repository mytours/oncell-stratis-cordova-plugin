#import "OnCellStratis.h"
// #import <StratisSDK/StratisSDK.h>

@implementation OnCellStratis {
    NSString *accessToken;
}

- (void) pluginInitialize {
    NSLog(@"OnCellStratis plugin initialize");
}

- (void)setServerEnvironment:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString* serverEnvironment = [command.arguments objectAtIndex:0];
    [self _setServerEnvironment:serverEnvironment];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"{\"success\": 1}"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)setAccessToken:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString* accessToken = [command.arguments objectAtIndex:0];
    [self _setAccessToken:accessToken];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"{\"success\": 1}"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)getLocks:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString* property = [command.arguments objectAtIndex:0];
    [self _getLocks:property];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"{\"success\": 1}"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)scanLocks:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString* seconds = [command.arguments objectAtIndex:0];
    [self _scanLocks:seconds];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"{\"success\": 1}"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)activateLock:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString* lockId = [command.arguments objectAtIndex:0];
    [self _activateLock:lockId];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"{\"success\": 1}"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void) _setServerEnvironment:(NSString*) serverEnvironment
{
    // call StratisSDK setServerEnvironment
}

- (void) _setAccessToken:(NSString*) accessToken
{
    NSLog(@"OnCellStratis setAccessToken %@", accessToken);
    self->accessToken = accessToken;
    // call StratisSDK setAccessToken
}

- (void) _getLocks:(NSString*) property
{
    // call StratisSDK getLocks
}

- (void) _scanLocks:(NSString*) seconds
{
    // cast seconds to Long
    // call StratisSDK setServerEnvironment
}

- (void) _activateLock:(NSString*) lockId
{
    // call StratisSDK activateLock
}

@end
