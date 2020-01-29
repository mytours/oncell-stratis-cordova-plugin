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
import android.os.Handler;
import java.lang.Runnable;

import com.stratisiot.stratissdk.StratisSDK;
import com.stratisiot.stratissdk.StratisSDK.ResultCallback;

import com.bugsnag.android.*;
import com.bugsnag.android.Error;

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
            public void error(JSONObject error) { Log.e(TAG, "Error on StratisSDK init:" +  error.toString()); }
            public void result(JSONObject r) { Log.d(TAG, "StratisSDK init result:" + r.toString()); }
            public void done() { Log.d(TAG, "StratisSDK init done"); }
            public void done(JSONObject r) { Log.d(TAG, "StratisSDK init done with result JSON:" + r.toString()); }
        }
        InitCallback initCallback = new InitCallback();

        stratisSDK = new StratisSDK(mainActivity, initCallback);

        // Set server environment
        if (isValidServerEnvironment(serverEnvironmentString)) {
            Log.d(TAG, "setServerEnvironment " + serverEnvironmentString);
            Bugsnag.leaveBreadcrumb("serverEnvironmentString: " + serverEnvironmentString);

            class ServerEnvironmentCallback implements ResultCallback {
                public void error(JSONObject error) { Log.e(TAG, "Error on setServerEnvironment: " + error.toString()); }
                public void result(JSONObject r) { Log.d(TAG, "setServerEnvironment result: " + r.toString()); }
                public void done() { Log.d(TAG, "setServerEnvironment done"); }
                public void done(JSONObject r) { Log.d(TAG, "setServerEnvironment done with result JSON: " + r.toString()); }
            }
            ServerEnvironmentCallback serverEnvironmentCallback = new ServerEnvironmentCallback();

            stratisSDK.setServerEnvironment(StratisSDK.ServerEnvironment.valueOf(serverEnvironmentString), serverEnvironmentCallback);

        } else {
            callbackError(callbackContext,"Expected a valid server environment");
            bugsnagNotify("Expected a valid server environment");
        }

        // Set access token
        if (accessToken != null && accessToken.length() > 0) {
            Log.d(TAG, "setAccessToken " + accessToken);

            class AccessTokenCallback implements ResultCallback {
                public void error(JSONObject error) { Log.e(TAG, "Error on setAccessToken: " + error.toString()); }
                public void result(JSONObject r) { Log.d(TAG, "setAccessToken result: " + r.toString()); }
                public void done() { Log.d(TAG, "setAccessToken done"); }
                public void done(JSONObject r) { Log.d(TAG, "setAccessToken done with result JSON: " + r.toString()); }
            }
            AccessTokenCallback accessTokenCallback = new AccessTokenCallback();

            stratisSDK.setAccessToken(accessToken, accessTokenCallback);
        } else {
            callbackError(callbackContext, "Expected an access token");
            bugsnagNotify("Expected an access token");
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
            Bugsnag.leaveBreadcrumb("property: " + property);

            class GetLocksCallback implements ResultCallback {
                public void error(JSONObject error) {
                    Log.e(TAG, "Error on getLocks: " + error.toString());
                    bugsnagNotify(error.toString());
                    callbackError(callbackContext, error.toString());
                }
                public void result(JSONObject r) {
                    Log.d(TAG, "getLocks result: " + r.toString());
                    Bugsnag.leaveBreadcrumb("getLocks result: " + r.toString());
                    try {
                        boolean gotLocks = addLocks((JSONArray) r.get("locks"));
                        if (!gotLocks) {
                            bugsnagNotify("No locks found by getLocks");
                        }
                    } catch (JSONException e) {
                        Log.d(TAG, e.toString());
                    }
                }
                public void done() {
                    Log.d(TAG, "getLocks done");
                    JSONArray locksJSON = new JSONArray(locks);
                    callbackSuccess(callbackContext, locksJSON);
                }
                public void done(JSONObject r) {
                    Log.d(TAG, "getLocks done with result JSON: " + r.toString());
                    JSONArray locksJSON = new JSONArray(locks);
                    callbackSuccess(callbackContext, locksJSON);
                }
            }
            GetLocksCallback getLocksCallback = new GetLocksCallback();

            stratisSDK.getLocks(property, getLocksCallback);
        } else {
            callbackError(callbackContext, "Expected a property ID");
            bugsnagNotify("Expected a property ID");
        }
    }


    public void scanLocks(Long seconds, CallbackContext callbackContext) {
        if (seconds > 0) {

            class ScanLocksCallback implements ResultCallback {
                boolean foundLock;
                public ScanLocksCallback() {
                    super();
                    foundLock = false;
                }
                public void error(JSONObject error) {
                    Log.e(TAG, "Error on scanLocks: " + error.toString());
                    bugsnagNotify(error.toString());
                    callbackError(callbackContext, error.toString());
                }
                public void result(JSONObject r) {
                    Log.d(TAG, "scanLocks result: " + r.toString());
                    Bugsnag.leaveBreadcrumb("scanLocks result: " + r.toString());
                    try {
                        if (enableLock((JSONObject) r.get("lock"))) {
                            foundLock = true;
                        }
                    } catch (JSONException e) {
                        Log.d(TAG, e.toString());
                    }
                }
                public void done() {
                    Log.d(TAG, "scanLocks done");
                    if (!foundLock) { bugsnagNotify("No locks found by scanLocks"); }
                    JSONArray locksJSON = new JSONArray(locks);
                    callbackSuccess(callbackContext, locksJSON);
                }
                public void done(JSONObject r) {
                    Log.d(TAG, "scanLocks done with result JSON: " + r.toString());
                    if (!foundLock) { bugsnagNotify("No locks found by scanLocks"); }
                    JSONArray locksJSON = new JSONArray(locks);
                    callbackSuccess(callbackContext, locksJSON);
                }
            }
            ScanLocksCallback scanLocksCallback = new ScanLocksCallback();

            stratisSDK.scanLocks(seconds, scanLocksCallback);
        } else {
            callbackError(callbackContext, "Expected seconds to scan");
            bugsnagNotify("Expected seconds to scan");
        }
    }


    public void activateLock(String lockId, String appointmentId, CallbackContext callbackContext) {
        if (lockId != null && lockId.length() > 0 && appointmentId != null && appointmentId.length() > 0) {
            Bugsnag.leaveBreadcrumb("lockId: " + lockId);
            // appointmentId is no longer necessary for the Stratis SDK, but I'm leaving it here for debugging purposes
            Bugsnag.leaveBreadcrumb("appointmentId: " + appointmentId);

            class ActivateLockCallback implements ResultCallback {
                public boolean responseSent;
                public ActivateLockCallback() {
                    super();
                    responseSent = false;
                }
                public void error(JSONObject error) {
                    Log.e(TAG, "Error on activateLock: " + error.toString());
                    bugsnagNotify(error.toString());
                    callbackError(callbackContext, error.toString());
                    responseSent = true;
                }
                public void result(JSONObject r) {
                    Log.d(TAG, "activateLock result: " + r.toString());
                    Bugsnag.leaveBreadcrumb("activateLock result: " + r.toString());
                    try {
                        String message = r.get("message").toString();
                        if (message.equals("ACTIVATION_SUCCESS")) {
                            callbackSuccess(callbackContext, null);
                            responseSent = true;
                        }
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
                public void done() {
                    Log.d(TAG, "activateLock done");
                }
                public void done(JSONObject r) {
                    Log.d(TAG, "activateLock done with result JSON: " + r.toString());
                }
            }
            ActivateLockCallback activateLockCallback = new ActivateLockCallback();

            stratisSDK.activateLock(lockId, activateLockCallback);

            // if we haven't sent a response to the front-end after 20 seconds, return error and log to Bugsnag
            Runnable runnable = new Runnable() {
                @Override
                public void run() {
                    Log.d(TAG, "activateLock responseSent: " + activateLockCallback.responseSent);
                    if (!activateLockCallback.responseSent) {
                        bugsnagNotify("Lock activation took too long to complete");
                        callbackError(callbackContext,"Lock activation took too long to complete");
                    }
                }
            };
            Handler handler = new Handler();
            handler.postDelayed(runnable, 20*1000);

        } else {
            callbackContext.error("Expected a lock ID and appointment ID");
            bugsnagNotify("Expected a lock ID and appointment ID");
        }
    }

    /* End command functions */

    /* Begin utility functions */

    private boolean addLocks(JSONArray locksJSON) {
        Log.d(TAG, "addLocks: " + locksJSON.toString());
        locks.clear();
        if (locksJSON != null) {
            for (int i=0;i<locksJSON.length();i++) {
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
        if (locks.size() > 0) {
            return true;
        }
        return false;
    }

    private boolean enableLock(JSONObject scannedLock) {
        Log.d(TAG, "enableLock: " + scannedLock.toString());
        boolean enabledLock = false;
        if (scannedLock != null) {
            try {
                String scannedLockId = scannedLock.getString("id");
                for (int i = 0; i < locks.size(); i++) {
                    JSONObject lock = locks.get(i);
                    String lockId = lock.getString("lockId");
                    if (scannedLockId.equals(lockId)) {
                        lock.put("isEnabled", true);
                        lock.put("rssi", scannedLock.get("rssi"));
                        enabledLock = true;
                    }
                    locks.set(i, lock);
                }
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
        return enabledLock;
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

    private void callbackSuccess(CallbackContext callbackContext, JSONArray locksJSON) {
        JSONObject r = new JSONObject();
        try {
            r.put("success", 1);
            if (locksJSON != null) {
                r.put("locks", locksJSON);
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

    private void bugsnagNotify(String errorMessage) {
        class lockException extends Exception {
            public lockException(String message) {
                super(message);
            }
        }
        Bugsnag.notify(new lockException(errorMessage));
    }

    /* End utility functions*/


}
