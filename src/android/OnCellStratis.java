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
    private String accessToken;
    private String serverEnvironmentString;

    public OnCellStratis() {
        super();
        this.accessToken = "";
        this.serverEnvironmentString = "";
    }

    class InitCallback implements ResultCallback {
        public void error(JSONObject error) { Log.e(TAG, "Error on StratisSDK init:"); Log.e(TAG, error.toString()); }
        public void result(JSONObject r) { Log.d(TAG, "StratisSDK init result:"); Log.d(TAG, r.toString()); }
        public void done() { Log.d(TAG, "StratisSDK init done"); }
        public void done(JSONObject r) { Log.d(TAG, "StratisSDK init done with result JSON:"); Log.d(TAG, r.toString()); }
    }
  
    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        Log.d(TAG, "OnCellStratis plugin initialize");
        super.initialize(cordova, webView);
        MainActivity mainActivity = (MainActivity) cordova.getActivity();
        InitCallback initCallback = new InitCallback();
        stratisSDK = new StratisSDK(mainActivity, initCallback);
    }
    
    private enum Commands {
        setServerEnvironment, setAccessToken, getLocks, scanLocks, activateLock
    }
    
    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        Commands cmd = Commands.valueOf(action);
        switch (cmd) {
            case setServerEnvironment:
                String serverEnvironmentString = args.getString(0);
                this.setServerEnvironment(serverEnvironmentString, callbackContext);
                return true;
            case setAccessToken:
                String accessToken = args.getString(0);
                this.setAccessToken(accessToken, callbackContext);
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
                this.activateLock(lockId, callbackContext);
                return true;
            default:
                return false;
        }
    }

    /* Begin command functions */
    
    public void setServerEnvironment(String serverEnvironmentString, CallbackContext callbackContext) {

        if (isValidServerEnvironment(serverEnvironmentString)) {
            Log.d(TAG, "setServerEnvironment " + serverEnvironmentString);
            this.serverEnvironmentString = serverEnvironmentString;

            class ServerEnvironmentCallback implements ResultCallback {
                public void error(JSONObject error) { Log.e(TAG, "Error on setServerEnvironment:"); Log.e(TAG, error.toString()); }
                public void result(JSONObject r) { Log.d(TAG, "setServerEnvironment result: "); Log.d(TAG, r.toString()); }
                public void done() { Log.d(TAG, "setServerEnvironment done"); }
                public void done(JSONObject r) { Log.d(TAG, "setServerEnvironment done with result JSON"); Log.d(TAG, r.toString()); }
            }

            ServerEnvironmentCallback serverEnvironmentCallback = new ServerEnvironmentCallback();
            stratisSDK.setServerEnvironment(StratisSDK.ServerEnvironment.valueOf(serverEnvironmentString), serverEnvironmentCallback);

            JSONObject r = new JSONObject();
            try {
                r.put("success", 1);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.success(r.toString());
        } else {
            callbackContext.error("Expected a valid server environment");
        }
    }

    public void setAccessToken(String accessToken, CallbackContext callbackContext) {

        if (accessToken != null && accessToken.length() > 0) {
            Log.d(TAG, "setAccessToken " + accessToken);
            this.accessToken = accessToken;

            class AccessTokenCallback implements ResultCallback {
                public void error(JSONObject error) { Log.e(TAG, "Error on setAccessToken:"); Log.e(TAG, error.toString()); }
                public void result(JSONObject r) { Log.d(TAG, "setAccessToken result: "); Log.d(TAG, r.toString()); }
                public void done() { Log.d(TAG, "setAccessToken done"); }
                public void done(JSONObject r) { Log.d(TAG, "setAccessToken done with result JSON"); Log.d(TAG, r.toString()); }
            }

            AccessTokenCallback accessTokenCallback = new AccessTokenCallback();
            stratisSDK.setAccessToken(accessToken, accessTokenCallback);

            JSONObject r = new JSONObject();
            try {
                r.put("success", 1);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.success(r.toString());
        } else {
            callbackContext.error("Expected an access token");
        }
    }
    
    public void getLocks(String property, CallbackContext callbackContext) {

        if (property != null && property.length() > 0) {

            this._getLocks(property);

            JSONObject r = new JSONObject();
            try {
                r.put("success", 1);
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

            this._scanLocks(seconds);

            JSONObject r = new JSONObject();
            try {
                r.put("success", 1);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.success(r.toString());
        } else {
            callbackContext.error("Expected seconds to scan");
        }
    }
    
    public void activateLock(String lockId, CallbackContext callbackContext) {
        if (lockId != null && lockId.length() > 0) {

            this._activateLock(lockId);

            JSONObject r = new JSONObject();
            try {
                r.put("success", 1);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.success(r.toString());
        } else {
            callbackContext.error("Expected a lock ID");
        }
    }
    
    public void _getLocks(String property) {
        Log.d(TAG, "_getLocks " + property);

        class GetLocksCallback implements ResultCallback {
            public void error(JSONObject error) { Log.e(TAG, "Error on getLocks:"); Log.e(TAG, error.toString()); }
            public void result(JSONObject r) { Log.d(TAG, "getLocks result: "); Log.d(TAG, r.toString()); }
            public void done() { Log.d(TAG, "getLocks done"); }
            public void done(JSONObject r) { Log.d(TAG, "getLocks done with result JSON"); Log.d(TAG, r.toString()); }
        }

        GetLocksCallback getLocksCallback = new GetLocksCallback();
        stratisSDK.getLocks(property, getLocksCallback);
    }
    
    public void _scanLocks(Long seconds) {
        Log.d(TAG, "_scanLocks: " + seconds);

        class ScanLocksCallback implements ResultCallback {
            public void error(JSONObject error) { Log.e(TAG, "Error on scanLocks:"); Log.e(TAG, error.toString()); }
            public void result(JSONObject r) { Log.d(TAG, "scanLocks result: "); Log.d(TAG, r.toString()); }
            public void done() { Log.d(TAG, "scanLocks done"); }
            public void done(JSONObject r) { Log.d(TAG, "scanLocks done with result JSON"); Log.d(TAG, r.toString()); }
        }

        ScanLocksCallback scanLocksCallback = new ScanLocksCallback();
        stratisSDK.scanLocks(seconds, scanLocksCallback);
    }
    
    public void _activateLock(String lockId) {
        Log.d(TAG, "_activateLock " + lockId);

        class ActivateLockCallback implements ResultCallback {
            public void error(JSONObject error) { Log.e(TAG, "Error on activateLock:"); Log.e(TAG, error.toString()); }
            public void result(JSONObject r) { Log.d(TAG, "activateLock result: "); Log.d(TAG, r.toString()); }
            public void done() { Log.d(TAG, "activateLock done"); }
            public void done(JSONObject r) { Log.d(TAG, "activateLock done with result JSON"); Log.d(TAG, r.toString()); }
        }

        ActivateLockCallback activateLockCallback = new ActivateLockCallback();
        stratisSDK.activateLock(lockId, activateLockCallback);
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

    // NOTE do we need functions to get and set status of bluetooth?

    /* End utility functions*/


}
