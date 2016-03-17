package ch.aimservices.android.plugin.action.filesystem;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;
import android.webkit.WebView;

import ch.aimservices.android.plugin.SenseServicesContext;
import ch.aimservices.android.plugin.action.BaseAction;

abstract class AbstractFileSystemAction extends BaseAction {

	public AbstractFileSystemAction(final WebView webview, final CordovaInterface cordova,
			final SenseServicesContext senseServicesContext) {
		super(webview, cordova, senseServicesContext);
	}

	@Override
	public boolean supports(String action) {
		return false;
	}

	@Override
	public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) {
		this.callbackContext = callbackContext;
		cordova.getThreadPool().execute(new Runnable() {
			@Override
			public void run() {
				try {
					JSONObject options = args.getJSONObject(0);
					execute(action, options, callbackContext);
				} catch (JSONException e) {
					Log.e(getLogTag(), "Problem retrieving parameters. Returning error.", e);
					callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
				}
			}
		});
		return true;
	}

	abstract void execute(String action, JSONObject args, CallbackContext callbackContext);
}
