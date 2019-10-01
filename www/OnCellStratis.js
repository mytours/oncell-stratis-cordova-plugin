var exec = require('cordova/exec');

var PLUGIN_NAME = 'OnCellStratis';

// Implements the methods at https://developer.stratisiot.com/sdk/ios/classes/StratisSDK/#methods
var OnCellStratis = {
  
  setServerEnvironment: function(serverEnvironment, callback) {
    /* return format:
     * {"success": "1"} */
    console.log("OnCellStratis.setServerEnvironment");
    exec(function(response) {
      callback(JSON.parse(response));
    }, function(err) {
      callback({"status": 0, "error": "Unable to set server environment"});
    }, PLUGIN_NAME, "setServerEnvironment", [serverEnvironment]);
  },
  
  setAccessToken: function(accessToken, callback) {
    /* return format:
     * {"success": "1"} */
    console.log("OnCellStratis.setAccessToken");
    exec(function(response) {
      callback(JSON.parse(response));
    }, function(err) {
      callback({"status": 0, "error": "Unable to set access token"});
    }, PLUGIN_NAME, "setAccessToken", [accessToken]);
  },
  
  getLocks: function(property, callback) {
    /* return format:
     * {"success": "1"} */
    console.log("OnCellStratis.getLocks");
    exec(function(response) {
      callback(JSON.parse(response));
    }, function(err) {
      callback({"status": 0, "error": "Unable to get locks"});
    }, PLUGIN_NAME, "getLocks", [property]);
  },
  
  scanLocks: function(seconds, callback) {
    /* return format:
     * {"success": "1"} */
    console.log("OnCellStratis.scanLocks");
    exec(function(response) {
      callback(JSON.parse(response));
    }, function(err) {
      callback({"status": 0, "error": "Unable to scan locks"});
    }, PLUGIN_NAME, "scanLocks", [seconds]);
  },
  
  activateLock: function(lockId, callback) {
    /* return format:
     * {"success": "1"} */
    console.log("OnCellStratis.activateLock");
    exec(function(response) {
      callback(JSON.parse(response));
    }, function(err) {
      callback({"status": 0, "error": "Unable to activate lock"});
    }, PLUGIN_NAME, "activateLock", [lockId]);
  },
    
};

module.exports = OnCellStratis;
