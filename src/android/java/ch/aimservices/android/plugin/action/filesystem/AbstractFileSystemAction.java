package ch.aimservices.android.plugin.action.filesystem;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import android.webkit.WebView;

import ch.aimservices.android.plugin.SenseServicesContext;
import ch.aimservices.android.plugin.action.BaseAction;

abstract class AbstractFileSystemAction extends BaseAction {
	private final Logger logger = LoggerFactory.getLogger(AbstractFileSystemAction.class);

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
		if (this.senseServicesContext.getSenseServices() == null) {
			callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
			return true;
		}
		cordova.getThreadPool().execute(new Runnable() {
			@Override
			public void run() {
				try {
					JSONObject options = args.getJSONObject(0);
					execute(action, options, callbackContext);
				} catch (JSONException e) {
					logger.error("Problem retrieving parameters. Returning error.", e);
					callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
				}
			}
		});
		return true;
	}

	abstract void execute(String action, JSONObject args, CallbackContext callbackContext);
}
