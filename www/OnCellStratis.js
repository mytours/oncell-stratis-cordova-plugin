var exec = require('cordova/exec');

var PLUGIN_NAME = 'OnCellStratis';

// Implements the methods at https://developer.stratisiot.com/sdk/ios/classes/StratisSDK/#methods and
// https://developer.stratisiot.com/sdk/android/com.stratisiot.stratissdk/-stratis-s-d-k/
var OnCellStratis = {
  
  setServerEnvironment: function(serverEnvironment, callback) {
    /* return format:
     * {"success": "1"} */
    exec(function(response) {
      callback(JSON.parse(response));
    }, function(err) {
      callback({"status": 0, "error": "Unable to set server environment"});
    }, PLUGIN_NAME, "setServerEnvironment", [serverEnvironment]);
  },
  
  setAccessToken: function(accessToken, callback) {
    /* return format:
     * {"success": "1"} */
    exec(function(response) {
      callback(JSON.parse(response));
    }, function(err) {
      callback({"status": 0, "error": "Unable to set access token"});
    }, PLUGIN_NAME, "setAccessToken", [accessToken]);
  },
  
  getLocks: function(property, callback) {
    /* return format:
     * {"success": "1"} */
    exec(function(response) {
      callback(JSON.parse(response));
    }, function(err) {
      callback({"status": 0, "error": "Unable to get locks"});
    }, PLUGIN_NAME, "getLocks", [property]);
  },
  
  scanLocks: function(seconds, callback) {
    /* return format:
     * {"success": "1"} */
    exec(function(response) {
      callback(JSON.parse(response));
    }, function(err) {
      callback({"status": 0, "error": "Unable to scan locks"});
    }, PLUGIN_NAME, "scanLocks", [seconds]);
  },
  
  activateLock: function(lockId, callback) {
    /* return format:
     * {"success": "1"} */
    exec(function(response) {
      callback(JSON.parse(response));
    }, function(err) {
      callback({"status": 0, "error": "Unable to activate lock"});
    }, PLUGIN_NAME, "activateLock", [lockId]);
  },
    
};

module.exports = OnCellStratis;
