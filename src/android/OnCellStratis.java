package com.oncell.oncellstratis;

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

// import com.stratisiot.stratissdk.StratisSDK
// import com.stratisiot.stratissdk.ServerEnvironment

public class OnCellStratis extends CordovaPlugin {
    private static final String TAG = "OnCellStratis";
    private String manifestUrl;
  
    public OnCellStratis() {
        super();
        this.accessToken = "";
    }
  
    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        Log.d(TAG, "OnCellStratis plugin initialize");
        super.initialize(cordova, webView);
    }
    
    private enum Commands {
        setServerEnvironment, setAccessToken, getLocks, scanLocks, activateLock
    }
    
    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        Commands cmd = Commands.valueOf(action);
        switch (cmd) {
            case setServerEnvironment:
                String serverEnvironment = args.getString(0);
                this.setServerEnvironment(serverEnvironment, callbackContext);
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
                Long seconds = args.getLong(0)
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
    
    public void setServerEnvironment(String serverEnvironment, CallbackContext callbackContext) {
        if (serverEnvironment != null && serverEnvironment.length() > 0) {
            this._setServerEnvironment(serverEnvironment);
            JSONObject r = new JSONObject();
            try {
                r.put("success", 1);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.success(r.toString());
        } else {
            callbackContext.error("Expected a server environment");
        }
    }
    
    public void setAccessToken(String accessToken, CallbackContext callbackContext) {
        if (accessToken != null && accessToken.length() > 0) {
            this._setAccessToken(accessToken);
            JSONObject r = new JSONObject();
            try {
                r.put("success", 1);
            } catch (JSONException e) {
                e.printStackTrace();
            }
            callbackContext.success(r.toString());
        } else {
            callbackContext.error("Expected an access code");
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
    
    public void scanLocks(int seconds, CallbackContext callbackContext) {
        if (seconds != null && seconds > 0) {
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
    
    public void _setServerEnvironment(String serverEnvironmentString) {
        // create ServerEnvironment object from string
        // StratisSDK.setServerEnvironment(serverEnvironment, setServerEnvironmentCallback);
    }
    
    public void _setAccessToken(String accessToken) {
        Log.d(TAG, "setAccessToken " + accessToken);
        this.accessToken = accessToken;
        // StratisSDK.setAccessToken(accessToken, setAccessTokenCallback);
    }
    
    public void _getLocks(String property) {
        // StratisSDK.getLocks(property, getLocksCallback);
    }
    
    public void _scanLocks(Long seconds) {
        // StratisSDK.scanLocks(seconds, scanLocksCallback);
    }
    
    public void _activateLock(String lockId) {
        // StratisSDK.activateLock(lockId, activateLockCallback);
    }
}
