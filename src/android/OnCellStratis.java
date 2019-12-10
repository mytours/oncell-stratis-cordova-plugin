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

import java.util.ArrayList;

import android.util.Log;

import com.stratisiot.stratissdk.StratisSDK;
import com.stratisiot.stratissdk.StratisSDK.ResultCallback;

public class OnCellStratis extends CordovaPlugin {
    private static final String TAG = "OnCellStratis";
    private StratisSDK stratisSDK;
    private ArrayList<JSONObject> locks = new ArrayList<JSONObject>();

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
            callbackError(callbackContext,"Expected a valid server environment");
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
            callbackError(callbackContext, "Expected an access token");
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
                public void error(JSONObject error) {
                    Log.e(TAG, "Error on getLocks:");
                    Log.e(TAG, error.toString());
                    callbackError(callbackContext, error.toString());
                }
                public void result(JSONObject r) {
                    Log.d(TAG, "getLocks result: ");
                    Log.d(TAG, r.toString());
                    try {
                        addLocks((JSONArray) r.get("locks"));
                    } catch (JSONException e) {
                        Log.d(TAG, e.toString());
                    }
                }
                public void done() {
                    Log.d(TAG, "getLocks done");
                    JSONArray locksJSON = new JSONArray(locks);
                    callbackSuccess(callbackContext, locksJSON.toString());
                }
                public void done(JSONObject r) {
                    Log.d(TAG, "getLocks done with result JSON");
                    Log.d(TAG, r.toString());
                    JSONArray locksJSON = new JSONArray(locks);
                    callbackSuccess(callbackContext, locksJSON.toString());
                }
            }
            GetLocksCallback getLocksCallback = new GetLocksCallback();

            stratisSDK.getLocks(property, getLocksCallback);
        } else {
            callbackError(callbackContext, "Expected a property ID");
        }
    }


    public void scanLocks(Long seconds, CallbackContext callbackContext) {
        if (seconds > 0) {

            class ScanLocksCallback implements ResultCallback {
                public void error(JSONObject error) {
                    Log.e(TAG, "Error on scanLocks:");
                    Log.e(TAG, error.toString());
                    callbackError(callbackContext, error.toString());
                }
                public void result(JSONObject r) {
                    Log.d(TAG, "scanLocks result: ");
                    Log.d(TAG, r.toString());
                    try {
                        enableLock((JSONObject) r.get("lock"));
                    } catch (JSONException e) {
                        Log.d(TAG, e.toString());
                    }
                }
                public void done() {
                    Log.d(TAG, "scanLocks done");
                    JSONArray locksJSON = new JSONArray(locks);
                    callbackSuccess(callbackContext, locksJSON.toString());
                }
                public void done(JSONObject r) {
                    Log.d(TAG, "scanLocks done with result JSON");
                    Log.d(TAG, r.toString());
                    JSONArray locksJSON = new JSONArray(locks);
                    callbackSuccess(callbackContext, locksJSON.toString());
                }
            }
            ScanLocksCallback scanLocksCallback = new ScanLocksCallback();

            stratisSDK.scanLocks(seconds, scanLocksCallback);
        } else {
            callbackError(callbackContext, "Expected seconds to scan");
        }
    }


    public void activateLock(String lockId, String appointmentId, CallbackContext callbackContext) {
        if (lockId != null && lockId.length() > 0 && appointmentId != null && appointmentId.length() > 0) {

            class ActivateLockCallback implements ResultCallback {
                public void error(JSONObject error) {
                    Log.e(TAG, "Error on activateLock:");
                    Log.e(TAG, error.toString());
                    callbackError(callbackContext, error.toString());
                }
                public void result(JSONObject r) {
                    Log.d(TAG, "activateLock result: ");
                    Log.d(TAG, r.toString());
                    try {
                        String message = r.get("message").toString();
                        if (message.equals("ACTIVATION_SUCCESS")) {
                            callbackSuccess(callbackContext, null);
                        }
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
                public void done() {
                    Log.d(TAG, "activateLock done");
                }
                public void done(JSONObject r) {
                    Log.d(TAG, "activateLock done with result JSON");
                    Log.d(TAG, r.toString());
                }
            }
            ActivateLockCallback activateLockCallback = new ActivateLockCallback();

            stratisSDK.activateLock(lockId, appointmentId, activateLockCallback);
        } else {
            callbackContext.error("Expected a lock ID and appointment ID");
        }
    }

    /* End command functions */

    /* Begin utility functions */

    private void addLocks(JSONArray locksJSON) {
        Log.d(TAG, "addLocks: " + locksJSON.toString());
        if (locksJSON != null) {
            locks.clear();
            for (int i=0;i<locksJSON.length();i++){
                try {
                    JSONObject lock = locksJSON.getJSONObject(i);
                    // rename some fields from the response to match iOS
                    lock.put("lockId", lock.get("id"));
                    lock.remove("id");
                    lock.put("unlockTechnology", lock.get("unlock_technology"));
                    lock.remove("unlock_technology");
                    lock.put("rssi", 0);
                    lock.put("isEnabled", false);
                    locks.add(lock);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private void enableLock(JSONObject scannedLock) {
        Log.d(TAG, "enableLock: " + scannedLock.toString());
        if (scannedLock != null) {
            try {
                String scannedLockId = scannedLock.getString("id");
                for (int i = 0; i < locks.size(); i++) {
                    JSONObject lock = locks.get(i);
                    String lockId = lock.getString("lockId");
                    if (scannedLockId.equals(lockId)) {
                        lock.put("isEnabled", true);
                        lock.put("rssi", scannedLock.get("rssi"));
                    }
                    locks.set(i, lock);
                }
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
    }

    private boolean isValidServerEnvironment(String serverEnvironmentString) {
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

    private void callbackSuccess(CallbackContext callbackContext, String message) {
        JSONObject r = new JSONObject();
        try {
            r.put("success", 1);
            if (message != null && message.length() > 0) {
                r.put("message", message);
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
        callbackContext.success(r.toString());
    }

    private void callbackError(CallbackContext callbackContext, String message) {
        JSONObject r = new JSONObject();
        try {
            r.put("success", 0);
            if (message != null && message.length() > 0) {
                r.put("error", message);
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
        callbackContext.error(r.toString());
    }

    /* End utility functions*/


}
