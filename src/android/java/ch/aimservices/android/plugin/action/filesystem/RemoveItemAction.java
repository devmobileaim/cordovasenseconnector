package ch.aimservices.android.plugin.action.filesystem;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.PluginResult;
import org.json.JSONException;
import org.json.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import android.webkit.WebView;

import ch.aimservices.android.plugin.SenseServicesContext;
import ch.sysmosoft.sense.android.core.service.context.File;

public class RemoveItemAction extends AbstractFileSystemAction {
	private final Logger logger = LoggerFactory.getLogger(RemoveItemAction.class);

	public RemoveItemAction(final WebView webview, final CordovaInterface cordova,
			final SenseServicesContext senseServicesContext) {
		super(webview, cordova, senseServicesContext);
	}

	@Override
	public boolean supports(final String action) {
		return "removeItemAtPath".equals(action);
	}

	@Override
	void execute(String action, JSONObject options, CallbackContext callbackContext) {
		logger.debug("removeItemAtPath:execute -> " + action + ", " + callbackContext.getCallbackId());
		String path;
		try {
			path = options.getString("path");
		} catch (JSONException e) {
			logger.error("Problem retrieving parameters. Returning error.", e);
			this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
			return;
		}
		logger.debug("removing file \"" + path + "\"");
		java.io.File userDir = getSenseContext().getFilesDir();
		File file = new File(userDir, path, getSenseContext());
		boolean result = file.delete();
		this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, result));
	}
}