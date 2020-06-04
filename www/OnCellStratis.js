var exec = require('cordova/exec');

var PLUGIN_NAME = 'OnCellStratis';

// Implements the methods at https://developer.stratisiot.com/sdk/ios/classes/StratisSDK/#methods and
// https://developer.stratisiot.com/sdk/android/com.stratisiot.stratissdk/-stratis-s-d-k/
var OnCellStratis = {

   initSDK: function(serverEnvironment, accessToken, propertyId, callback) {
     exec(function(response) {
       /* return format:
        * {"success": "1"} */
       callback(JSON.parse(response));
     }, function(err) {
        errMessage = '{"success": 0, "error": "Error initializing Stratis SDK"}';
        try {  errMessage = JSON.parse(err) } catch {}
        callback(errMessage)
     }, PLUGIN_NAME, "initSDK", [serverEnvironment, accessToken, propertyId]);
   },

  getLocks: function(callback) {
    exec(function(response) {
      /* return format:
       * {"success": "1", "locks": ?} */
      callback(JSON.parse(response));
    }, function(err) {
      /* return format:
       * {"success": "1", "error": "error"} */
      errMessage = JSON.parse('{"success": 0, "error": "Error when attempting lock authorization"}');
      try {  errMessage = JSON.parse(err) } catch {}
      callback(errMessage)
    }, PLUGIN_NAME, "getLocks", []);
  },

  scanLocks: function(callback) {
    exec(function(response) {
      /* return format:
       * {"success": "1", "locks": ?} */
      callback(JSON.parse(response));
    }, function(err) {
      /* return format:
       * {"success": "0", "error": "error"} */
      errMessage = JSON.parse('{"success": 0, "error": "Error scanning locks"}');
      try {  errMessage = JSON.parse(err) } catch {}
      callback(errMessage)
    }, PLUGIN_NAME, "scanLocks", []);
  },

  activateLock: function(lockId, appointmentId, callback) {
    exec(function(response) {
      /* return format:
       * {"success": "1"} */
      callback(JSON.parse(response));
    }, function(err) {
      /* return format:
       * {"success": "0", "error": "error"} */
      errMessage = JSON.parse('{"success": 0, "error": "Error activating lock"}');
      try {  errMessage = JSON.parse(err) } catch {}
      callback(errMessage)
    }, PLUGIN_NAME, "activateLock", [lockId, appointmentId]);
  },

};

module.exports = OnCellStratis;
