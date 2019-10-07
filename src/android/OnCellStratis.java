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
import com.toursphere.oncellstratis.MainActivity;

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
        public void error(JSONObject error) {
            try { Log.e(TAG, "Error on init: " + error.getString("message")); } catch (JSONException e) { e.printStackTrace(); }
        }
        public void result(JSONObject r) {
            try { Log.d(TAG, "Init result: " + r.getString("message")); } catch (JSONException e) { e.printStackTrace(); }
        }
        public void done() { Log.d(TAG, "Init done"); }
        public void done(JSONObject r) { Log.d(TAG, "Init done with result JSON"); }
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
                public void error(JSONObject error) {
                    try { Log.e(TAG, "Error setting server environment: " + error.getString("message")); } catch (JSONException e) { e.printStackTrace(); }
                }
                public void result(JSONObject r) {
                    try { Log.d(TAG, "Server environment set: " + r.getString("message")); } catch (JSONException e) { e.printStackTrace(); }
                }
                public void done() { Log.d(TAG, "Server environment done"); }
                public void done(JSONObject r) { Log.d(TAG, "Server environment done with result JSON"); }
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
                public void error(JSONObject error) {
                    try { Log.e(TAG, "Error setting access token: " + error.getString("message")); } catch (JSONException e) { e.printStackTrace(); }
                }
                public void result(JSONObject r) {
                    try { Log.d(TAG, "Access token set: " + r.getString("message")); } catch (JSONException e) { e.printStackTrace(); }
                }
                public void done() { Log.d(TAG, "Access token done"); }
                public void done(JSONObject r) { Log.d(TAG, "Access token done with result JSON"); }
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
        // StratisSDK.getLocks(property, getLocksCallback);
    }
    
    public void _scanLocks(Long seconds) {
        Log.d(TAG, "_scanLocks: " + seconds);
        // StratisSDK.scanLocks(seconds, scanLocksCallback);
    }
    
    public void _activateLock(String lockId) {
        Log.d(TAG, "_activateLock " + lockId);
        // StratisSDK.activateLock(lockId, activateLockCallback);
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
