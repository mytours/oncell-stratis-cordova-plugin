var exec = require('cordova/exec');

var PLUGIN_NAME = 'OnCellStratis';

// Implements the methods at https://developer.stratisiot.com/sdk/ios/classes/StratisSDK/#methods and
// https://developer.stratisiot.com/sdk/android/com.stratisiot.stratissdk/-stratis-s-d-k/
var OnCellStratis = {
               
   initSDK: function(serverEnvironment, accessToken, callback) {
     exec(function(response) {
       /* return format:
        * {"success": "1"} */
       callback(JSON.parse(response));
     }, function(err) {
       callback({"status": 0, "error": "Unable to init SDK"});
     }, PLUGIN_NAME, "initSDK", [serverEnvironment, accessToken]);
   },
  
  getLocks: function(property, callback) {
    exec(function(response) {
      /* return format:
       * {"success": "1", "locks": ?} */
      callback(JSON.parse(response));
    }, function(err) {
      /* return format:
       * {"success": "1", "error": "error"} */
      callback(JSON.parse(err));
    }, PLUGIN_NAME, "getLocks", [property]);
  },
  
  scanLocks: function(seconds, callback) {
    exec(function(response) {
      /* return format:
       * {"success": "1", "locks": ?} */
      callback(JSON.parse(response));
    }, function(err) {
      /* return format:
       * {"success": "1", "error": "error"} */
      callback(JSON.parse(err));
    }, PLUGIN_NAME, "scanLocks", [seconds]);
  },
  
  activateLock: function(lockId, appointmentId, callback) {
    exec(function(response) {
      /* return format:
       * {"success": "1"} */
      callback(JSON.parse(response));
    }, function(err) {
      /* return format:
       * {"success": "1", "error": "error"} */
      callback(JSON.parse(err));
    }, PLUGIN_NAME, "activateLock", [lockId, appointmentId]);
  },
    
};

module.exports = OnCellStratis;
