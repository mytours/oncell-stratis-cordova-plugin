package com.oncell;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.PluginResult;
import org.apache.cordova.PluginResult.Status;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;

import java.lang.Runnable;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.HashMap;

import android.util.Log;
import android.content.Context;
import android.os.Handler;

import com.stratisiot.stratissdk.StratisSDK;
import com.stratisiot.stratissdk.constants.ServerEnvironment;
import com.stratisiot.stratissdk.model.Configuration;
import com.stratisiot.stratissdk.error.StratisError;
import com.stratisiot.stratissdk.listener.DeviceActivationEvent;
import com.stratisiot.stratissdk.listener.StratisDeviceAccessListener;
import com.stratisiot.stratissdk.listener.StratisDeviceActivationListener;
import com.stratisiot.stratissdk.listener.StratisDeviceDiscoveryListener;
import com.stratisiot.stratissdk.model.lock.StratisLock;
import com.stratisiot.stratissdk.model.lock.BLELock;

import com.bugsnag.android.*;

public class OnCellStratis extends CordovaPlugin {
    private static final String TAG = "OnCellStratis";
    private StratisSDK stratisSDK;
    private Collection<StratisLock> accessibleLocks;
    private HashSet<StratisLock> discoveredLocks;

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
                String propertyId = args.getString(2);
                this.initSDK(serverEnvironmentString, accessToken, propertyId, callbackContext);
                return true;
            case getLocks:
                this.getLocks(callbackContext);
                return true;
            case scanLocks:
                this.scanLocks(callbackContext);
//                this.scanLocksAfterDelay(callbackContext, 5); // Use for testing purposes
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

    public void initSDK(String serverEnvironmentString, String accessToken, String propertyId, CallbackContext callbackContext) {
        Log.d(TAG, "initSDK");

        if (stratisSDK == null) { // Only initialize once
            Bugsnag.leaveBreadcrumb("Initializing StratisSDK serverEnvironmentString: " + serverEnvironmentString + ", accessToken: " + accessToken + ", propertyId: " + propertyId);
            
            if (isValidServerEnvironment(serverEnvironmentString) && accessToken != null && propertyId != null) {
                MainActivity mainActivity = (MainActivity) cordova.getActivity();
                Context appContext = mainActivity.getApplicationContext();
                Map<String, String> logMap = new HashMap<String, String>();
                logMap.put("app", "OnCell");

                Configuration configuration = new Configuration(
                        ServerEnvironment.valueOf(serverEnvironmentString),
                        accessToken,
                        true,
                        logMap,
                        propertyId
                );

                stratisSDK = new StratisSDK(appContext, configuration);

                // return successfully
                callbackSuccess(callbackContext, null);
            } else { // return with error
                callbackError(callbackContext, "Missing or invalid parameters when initializing Stratis SDK");
            }
        } else {
            // if SDK is already initialized, just refresh the access token and property ID
            Bugsnag.leaveBreadcrumb("Refreshing Stratis SDK accessToken: " + accessToken + ", propertyId: " + propertyId);
            stratisSDK.setAccessToken(accessToken);
            stratisSDK.setPropertyID(propertyId);
            callbackSuccess(callbackContext, null);
        }
    }


    public void getLocks(CallbackContext callbackContext) {
        Log.d(TAG, "getLocks");
        stratisSDK.setDeviceAccessListener(new OnCellStratisDeviceAccessListener(callbackContext));
        stratisSDK.fetchAccessibleDevices();
    }

    private class OnCellStratisDeviceAccessListener implements StratisDeviceAccessListener {

        private CallbackContext callbackContext;

        public OnCellStratisDeviceAccessListener(CallbackContext cc) {
            super();
            this.callbackContext = cc;
        }

        @Override
        public void stratisDeviceAccessRequestCompleted(@NotNull StratisSDK stratisSDK, @NotNull Collection<? extends StratisLock> collection, @Nullable StratisError stratisError) {
            Log.d(TAG, "stratisDeviceAccessRequestCompleted");
            if (stratisError == null) {
                accessibleLocks = (Collection<StratisLock>) collection;
                JSONArray locksJson = new JSONArray();
                if (!accessibleLocks.isEmpty()) {
                    locksJson = getLocksAsJson(accessibleLocks);
                    Log.d(TAG, "accessibleLocks: " + locksJson.toString());
                    Bugsnag.leaveBreadcrumb("accessibleLocks: " + locksJson.toString());
                } else {
                    bugsnagNotify("No accessible locks found");
                    Log.d(TAG, "No accessible locks found");
                }
                callbackSuccess(callbackContext, locksJson);
            } else {
                callbackError(callbackContext, stratisError.getDebugMessage());
            }
        }
    }

    public void scanLocksAfterDelay(CallbackContext callbackContext, Integer secondsDelay) {
        // Used only for testing purposes
        Log.d(TAG, "Delaying scanLocks...");
        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                Log.d(TAG, "Calling scanLocks now");
                    scanLocks(callbackContext);
            }
        };
        Handler handler = new Handler();
        handler.postDelayed(runnable, secondsDelay*1000);
    }


    public void scanLocks(CallbackContext callbackContext) {
        Log.d(TAG, "scanLocks");
        if (accessibleLocks != null) {
            discoveredLocks = new HashSet<StratisLock>();
            stratisSDK.setDeviceDiscoveryListener(new OnCellStratisDeviceDiscoveryListener(callbackContext));
            stratisSDK.discoverActionableDevices(accessibleLocks);
        } else {
            callbackError(callbackContext, "Cannot scan locks before getting lock authorization");
        }
    }

    private class OnCellStratisDeviceDiscoveryListener implements StratisDeviceDiscoveryListener {

        private CallbackContext callbackContext;

        public OnCellStratisDeviceDiscoveryListener(CallbackContext cc) {
            super();
            this.callbackContext = cc;
        }

        @Override
        public void stratisDiscoveredDevices(@NotNull StratisSDK stratisSDK, @NotNull Collection<? extends StratisLock> collection) {
            Log.d(TAG, "stratisDiscoveredDevices");
            Log.d(TAG, collection.toString());
            discoveredLocks.addAll(collection);
        }

        @Override
        public void stratisDiscoveryCompleted(@NotNull StratisSDK stratisSDK) {
            Log.d(TAG, "stratisDiscoveryCompleted");
            JSONArray locksJson = new JSONArray();
            if (!discoveredLocks.isEmpty()) {
                ArrayList sortedDiscoveredLocks = new ArrayList<>(discoveredLocks);
                // Sort in descending order with highest RSSI (closest lock) first
                Comparator<BLELock> compareByRssi = (BLELock l1, BLELock l2) -> l2.getRssi().intValue() - l1.getRssi().intValue();
                Collections.sort(sortedDiscoveredLocks, compareByRssi);
                locksJson = getLocksAsJson(sortedDiscoveredLocks);
                Log.d(TAG, "discoveredLocks: " + locksJson.toString());
                Bugsnag.leaveBreadcrumb("discoveredLocks: " + locksJson.toString());
            } else {
                bugsnagNotify("No scanned locks discovered");
                Log.d(TAG, "No scanned locks discovered");
            }
            callbackSuccess(callbackContext, locksJson);
        }

        @Override
        public void stratisDiscoveryEncounteredError(@NotNull StratisSDK stratisSDK, @NotNull StratisError stratisError) {
            Log.e(TAG, "stratisDiscoveryEncounteredError");
            callbackError(callbackContext, stratisError.getDebugMessage());
        }
        
        @Override
        public void stratisDiscoveryDevicesOutOfRange(@NotNull StratisSDK stratisSDK, @NotNull Collection<? extends StratisLock> collection) {
            
        }

        @Override
        public void stratisDiscoveryUpdatedRSSI(@NotNull StratisSDK stratisSDK, @NotNull Collection<? extends StratisLock> collection) {
            Log.d(TAG, "stratisDiscoveryCompleted");
            JSONArray locksJson = new JSONArray();
            if (!discoveredLocks.isEmpty()) {
                ArrayList sortedDiscoveredLocks = new ArrayList<>(discoveredLocks);
                // Sort in descending order with highest RSSI (closest lock) first
                Comparator<BLELock> compareByRssi = (BLELock l1, BLELock l2) -> l2.getRssi().intValue() - l1.getRssi().intValue();
                Collections.sort(sortedDiscoveredLocks, compareByRssi);
                locksJson = getLocksAsJson(sortedDiscoveredLocks);
                Log.d(TAG, "discoveredLocks: " + locksJson.toString());
                Bugsnag.leaveBreadcrumb("discoveredLocks: " + locksJson.toString());
            } else {
                bugsnagNotify("No scanned locks discovered");
                Log.d(TAG, "No scanned locks discovered");
            }
            callbackSuccess(callbackContext, locksJson);
          }
    }


    public void activateLock(String lockId, String appointmentId, CallbackContext callbackContext) {
        Log.d(TAG, "activateLock");
        Bugsnag.leaveBreadcrumb("lockId: " + lockId);
        // appointmentId is no longer necessary for the Stratis SDK, but I'm leaving it here for debugging purposes
        Bugsnag.leaveBreadcrumb("appointmentId: " + appointmentId);

        if (discoveredLocks != null ) {
            StratisLock deviceToActivate = null;
            for (StratisLock lock : discoveredLocks) {
                if (lock.getIdentifier().equals(lockId)) {
                    deviceToActivate = lock;
                }
            }
            if (deviceToActivate != null) {
                OnCellStratisDeviceActivationListener listener = new OnCellStratisDeviceActivationListener(callbackContext);
                deviceToActivate.setListener(listener);
                deviceToActivate.activate();
                // return error to JS and send log to Bugsnag if we haven't unlocked device in 20 seconds
                listener.startActivationTimer(20);
            } else {
                callbackError(callbackContext, "Cannot find lock to activate");
            }
        } else {
            callbackError(callbackContext, "Cannot activate lock before scanning for locks");
        }
    }

    private class OnCellStratisDeviceActivationListener implements StratisDeviceActivationListener {

        private CallbackContext callbackContext;
        private Boolean responseSent = false;

        public OnCellStratisDeviceActivationListener(CallbackContext cc) {
            super();
            this.callbackContext = cc;
        }

        public void startActivationTimer(Integer maxSeconds) {
            // if we haven't sent a response to the front-end after X seconds, return error and log to Bugsnag
            Runnable runnable = new Runnable() {
                @Override
                public void run() {
                    Log.d(TAG, "activateLock responseSent: " + responseSent);
                    if (!responseSent) {
                        callbackError(callbackContext,"Lock activation took too long to complete");
                    }
                }
            };
            Handler handler = new Handler();
            handler.postDelayed(runnable, maxSeconds*1000);
        }

        @Override
        public void stratisDeviceActivationDidPostEvent(@NotNull StratisLock stratisLock, @NotNull DeviceActivationEvent deviceActivationEvent, @Nullable StratisError stratisError) {
            Log.d(TAG, "stratisDeviceActivationDidPostEvent");
            if (stratisError == null) {
                Log.d(TAG, deviceActivationEvent.toString());
                if (deviceActivationEvent == DeviceActivationEvent.COMPLETE) {
                    callbackSuccess(callbackContext, null);
                    responseSent = true;
                }
            } else {
                callbackError(callbackContext, stratisError.getDebugMessage());
                responseSent = true;
            }
        }
    }

    /* End command functions */

    /* Begin utility functions */

    private boolean isValidServerEnvironment(String serverEnvironmentString) {
        // Valid serverEnvironmentStrings:
        // DEV, SANDBOX, TEST, PROD
        // see https://developer.stratisiot.com/sdk/v4/android/com.stratisiot.stratissdk.constants/-server-environment/ for more info
        try {
            ServerEnvironment.valueOf(serverEnvironmentString);
            return true;
        } catch (IllegalArgumentException e) {
            return false;
        }
    }


    private JSONArray getLocksAsJson(Collection<StratisLock> locks) {
        Log.d(TAG, "getLocksAsJson");
        Bugsnag.leaveBreadcrumb("getLocksAsJson");

        JSONArray locksJsonArray = new JSONArray();

        for (StratisLock lock : locks) {
            Log.d(TAG, "serializing lock to JSON...");
            Bugsnag.leaveBreadcrumb("serializing lock to JSON...");
            JSONObject jsonObject = new JSONObject();
            try {
                jsonObject.put("isActionable", lock.isActionable());
            } catch (JSONException e) {
                e.printStackTrace();
            }
            try {
                jsonObject.put("identifier", lock.getIdentifier());
            } catch (JSONException e) {
                e.printStackTrace();
            }
            try {
                jsonObject.put("name", lock.getName());
            } catch (JSONException e) {
                e.printStackTrace();
            }
            try {
                jsonObject.put("model", lock.getModel());
            } catch (JSONException e) {
                e.printStackTrace();
            }
            locksJsonArray.put(jsonObject);
        }

        Log.d(TAG, "getLocksAsJson done");
        Bugsnag.leaveBreadcrumb("getLocksAsJson done");

        return locksJsonArray;
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
        Log.e(TAG, message);
        bugsnagNotify(message);
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
