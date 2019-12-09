package com.oncell;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.PluginResult;
import org.apache.cordova.PluginResult.Status;

import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;

import android.util.Log;

import com.stratisiot.stratissdk.StratisSDK;
import com.stratisiot.stratissdk.StratisSDK.ResultCallback;

public class OnCellStratis extends CordovaPlugin {
    private static final String TAG = "OnCellStratis";
    private StratisSDK stratisSDK;

    public OnCellStratis() {
        super();
    }

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        Log.d(TAG, "OnCellStratis plugin initialize");
        super.initialize(cordova, webView);
    }
    
    private enum Commands {
        initSDK, getLocks, scanLocks, activateLock
    }
    
    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        Commands cmd = Commands.valueOf(action);
        switch (cmd) {
            case initSDK:
                String serverEnvironmentString = args.getString(0);
                String accessToken = args.getString(1);
                this.initSDK(serverEnvironmentString, accessToken, callbackContext);
                return true;
            case getLocks:
                String property = args.getString(0);
                this.getLocks(property, callbackContext);
                return true;
            case scanLocks:
                Long seconds = args.getLong(0);
                this.scanLocks(seconds, callbackContext);
                return true;
            case activateLock:
                String lockId = args.getString(0);
                String appointmentId = args.getString(1);
                this.activateLock(lockId, appointmentId, callbackContext);
                return true;
            default:
                return false;
        }
    }

    /* Begin command functions */

    // Currently uses the deprecated method for initialization; will be simplified with new method
    public void initSDK(String serverEnvironmentString, String accessToken, CallbackContext callbackContext) {

        // Create new stratisSDK object
        MainActivity mainActivity = (MainActivity) cordova.getActivity();

        class InitCallback implements ResultCallback {
            public void error(JSONObject error) { Log.e(TAG, "Error on StratisSDK init:"); Log.e(TAG, error.toString()); }
            public void result(JSONObject r) { Log.d(TAG, "StratisSDK init result:"); Log.d(TAG, r.toString()); }
            public void done() { Log.d(TAG, "StratisSDK init done"); }
            public void done(JSONObject r) { Log.d(TAG, "StratisSDK init done with result JSON:"); Log.d(TAG, r.toString()); }
        }
        InitCallback initCallback = new InitCallback();

        stratisSDK = new StratisSDK(mainActivity, initCallback);

        // Set server environment
        if (isValidServerEnvironment(serverEnvironmentString)) {
            Log.d(TAG, "setServerEnvironment " + serverEnvironmentString);

            class ServerEnvironmentCallback implements ResultCallback {
                public void error(JSONObject error) { Log.e(TAG, "Error on setServerEnvironment:"); Log.e(TAG, error.toString()); }
                public void result(JSONObject r) { Log.d(TAG, "setServerEnvironment result: "); Log.d(TAG, r.toString()); }
                public void done() { Log.d(TAG, "setServerEnvironment done"); }
                public void done(JSONObject r) { Log.d(TAG, "setServerEnvironment done with result JSON"); Log.d(TAG, r.toString()); }
            }
            ServerEnvironmentCallback serverEnvironmentCallback = new ServerEnvironmentCallback();

            stratisSDK.setServerEnvironment(StratisSDK.ServerEnvironment.valueOf(serverEnvironmentString), serverEnvironmentCallback);

        } else {
            callbackContext.error("Expected a valid server environment");
        }

        // Set access token
        if (accessToken != null && accessToken.length() > 0) {
            Log.d(TAG, "setAccessToken " + accessToken);

            class AccessTokenCallback implements ResultCallback {
                public void error(JSONObject error) { Log.e(TAG, "Error on setAccessToken:"); Log.e(TAG, error.toString()); }
                public void result(JSONObject r) { Log.d(TAG, "setAccessToken result: "); Log.d(TAG, r.toString()); }
                public void done() { Log.d(TAG, "setAccessToken done"); }
                public void done(JSONObject r) { Log.d(TAG, "setAccessToken done with result JSON"); Log.d(TAG, r.toString()); }
            }
            AccessTokenCallback accessTokenCallback = new AccessTokenCallback();

            stratisSDK.setAccessToken(accessToken, accessTokenCallback);
        } else {
            callbackContext.error("Expected an access token");
        }

        // Return successfully
        JSONObject r = new JSONObject();
        try {
            r.put("success", 1);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        callbackContext.success(r.toString());

    }
    
    public void getLocks(String property, CallbackContext callbackContext) {

        if (property != null && property.length() > 0) {

            class GetLocksCallback implements ResultCallback {
                public void error(JSONObject error) { Log.e(TAG, "Error on getLocks:"); Log.e(TAG, error.toString()); } // TODO return error in callback here
                public void result(JSONObject r) { Log.d(TAG, "getLocks result: "); Log.d(TAG, r.toString()); } // TODO save locks returned
                public void done() { Log.d(TAG, "getLocks done"); } // TODO return response in callback here
                public void done(JSONObject r) { Log.d(TAG, "getLocks done with result JSON"); Log.d(TAG, r.toString()); }
            }
            GetLocksCallback getLocksCallback = new GetLocksCallback();

            stratisSDK.getLocks(property, getLocksCallback);

            JSONObject r = new JSONObject();
            try {
                r.put("success", 1); // TODO include locks in callback json
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.success(r.toString());
        } else {
            callbackContext.error("Expected a property");
        }
    }
    
    public void scanLocks(Long seconds, CallbackContext callbackContext) {
        if (seconds > 0) {

            class ScanLocksCallback implements ResultCallback {
                public void error(JSONObject error) { Log.e(TAG, "Error on scanLocks:"); Log.e(TAG, error.toString()); } // TODO return error in callback here
                public void result(JSONObject r) { Log.d(TAG, "scanLocks result: "); Log.d(TAG, r.toString()); } // TODO save locks returned
                public void done() { Log.d(TAG, "scanLocks done"); } // TODO return response in callback here
                public void done(JSONObject r) { Log.d(TAG, "scanLocks done with result JSON"); Log.d(TAG, r.toString()); }
            }
            ScanLocksCallback scanLocksCallback = new ScanLocksCallback();

            stratisSDK.scanLocks(seconds, scanLocksCallback);

            JSONObject r = new JSONObject();
            try {
                r.put("success", 1); // TODO include locks in callback json
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.success(r.toString());
        } else {
            callbackContext.error("Expected seconds to scan");
        }
    }
    
    public void activateLock(String lockId, String appointmentId, CallbackContext callbackContext) {
        if (lockId != null && lockId.length() > 0 && appointmentId != null && appointmentId.length() > 0) {

            class ActivateLockCallback implements ResultCallback {
                public void error(JSONObject error) { Log.e(TAG, "Error on activateLock:"); Log.e(TAG, error.toString()); } // TODO return error in callback here
                public void result(JSONObject r) { Log.d(TAG, "activateLock result: "); Log.d(TAG, r.toString()); } // TODO return response in callback here if ACTIVATION_SUCCESS
                public void done() { Log.d(TAG, "activateLock done"); }
                public void done(JSONObject r) { Log.d(TAG, "activateLock done with result JSON"); Log.d(TAG, r.toString()); }
            }
            ActivateLockCallback activateLockCallback = new ActivateLockCallback();

            stratisSDK.activateLock(lockId, appointmentId, activateLockCallback);

            JSONObject r = new JSONObject();
            try {
                r.put("success", 1);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.success(r.toString());
        } else {
            callbackContext.error("Expected a lock ID and appointment ID");
        }
    }

    /* End command functions */

    /* Begin utility functions */

    public boolean isValidServerEnvironment(String serverEnvironmentString) {
        // Valid serverEnvironmentStrings:
        // DEV, SANDBOX, TEST, PROD
        // see https://developer.stratisiot.com/sdk/android/com.stratisiot.stratissdk/-server-environment/ for more info
        try {
            StratisSDK.ServerEnvironment.valueOf(serverEnvironmentString);
            return true;
        } catch (IllegalArgumentException e) {
            return false;
        }
    }

    /* End utility functions*/


}
