package ch.aimservices.android.plugin.action.filesystem;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.PluginResult;
import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;
import android.webkit.WebView;

import ch.aimservices.android.plugin.SenseServicesContext;
import ch.sysmosoft.sense.android.core.service.context.File;

public class ItemExistAction extends AbstractFileSystemAction {

	public ItemExistAction(final WebView webview, final CordovaInterface cordova,
			final SenseServicesContext senseServicesContext) {
		super(webview, cordova, senseServicesContext);
	}

	@Override
	public boolean supports(final String action) {
		return "itemExistsAtPath".equals(action);
	}

	@Override
	void execute(String action, JSONObject options, CallbackContext callbackContext) {
		Log.d(getLogTag(), "itemExistsAtPath:execute -> " + action + ", " + callbackContext.getCallbackId());
		String path;
		try {
			path = options.getString("path");
		} catch (JSONException e) {
			Log.e(getLogTag(), "Problem retrieving parameters. Returning error.", e);
			this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
			return;
		}
		Log.d(getLogTag(), "check if file \"" + path + "\" exist");
		java.io.File userDir = getSenseContext().getFilesDir();
		File file = new File(userDir, path, getSenseContext());
		boolean result = file.exists();
		this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, result));
	}

}