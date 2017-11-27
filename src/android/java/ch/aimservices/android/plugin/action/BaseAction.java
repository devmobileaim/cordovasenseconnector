package ch.aimservices.android.plugin.action;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.PluginResult;
import org.json.JSONException;
import org.json.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import android.app.Activity;
import android.content.Context;
import android.webkit.WebView;

import ch.aimservices.android.plugin.SenseServicesContext;
import ch.sysmosoft.sense.android.core.service.Sense;
import ch.sysmosoft.sense.android.core.service.context.SenseContext;

/**
 * Created by Android Studio
 * User: pblanco
 * Date: 03.09.2014
 * Time: 11:36
 */
public abstract class BaseAction implements Action {
	private final Logger logger = LoggerFactory.getLogger(BaseAction.class);

    protected final WebView webview;

    protected final SenseServicesContext senseServicesContext;

    protected final CordovaInterface cordova;

    protected CallbackContext callbackContext;

    // Error codes
    public static final String ERR_RETRIEVING_PARAMS = "ERR_RETRIEVING_PARAMS";
	
    public BaseAction(final WebView webview, final CordovaInterface cordova, final SenseServicesContext senseServicesContext) {
        this.webview = webview;
        this.senseServicesContext = senseServicesContext;
        this.cordova = cordova;
    }

    @Override
    public boolean internal() {
        return false;
    }

	protected Context getContext() {
        return getCordovaActivity().getApplicationContext();
    }

    protected Activity getCordovaActivity() {
        return cordova.getActivity();
    }

    protected Sense.SessionService getSenseSessionService() {
        return this.senseServicesContext.getSessionService();
    }

	protected SenseContext getSenseContext() {
		return this.senseServicesContext.getSenseServices().getSenseContext();
	}

    protected void success(final int code) {
        success(code, null, false);
    }

    protected void success(final int code, final boolean keepCallback) {
        success(code, null, keepCallback);
    }

    protected void success(final int code, final String message) {
        success(code, message, false);
    }

    protected void success(final int code, final String message, final boolean keepCallback) {
        final PluginResult result = new PluginResult(PluginResult.Status.OK, createResponse(code, message));
        result.setKeepCallback(keepCallback);
        callbackContext.sendPluginResult(result);
    }

    protected void error(final String errorType) {
        error(errorType, null);
    }

    protected void error(final String errorType, final String detail) {
        callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, createResponse(errorType, detail)));
    }

    protected <T> JSONObject createResponse(final T code, final String message) {
        final JSONObject response = new JSONObject();
        try {
            response.put("code", code);
            if (message != null) {
                response.put("message", message);
            }
        } catch (JSONException e) {
            logger.error("Error while populating response", e);
        }
        return response;
    }
}
