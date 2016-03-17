package ch.aimservices.android.plugin.action.filesystem;

import java.io.IOException;

import org.apache.commons.io.IOUtils;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.PluginResult;
import org.json.JSONException;
import org.json.JSONObject;

import android.util.Base64;
import android.util.Log;
import android.webkit.WebView;

import ch.aimservices.android.plugin.SenseServicesContext;
import ch.sysmosoft.sense.android.core.service.context.File;
import ch.sysmosoft.sense.android.core.service.context.FileOutputStream;

public class CreateItemAction extends AbstractFileSystemAction {

	public CreateItemAction(final WebView webview, final CordovaInterface cordova,
			final SenseServicesContext senseServicesContext) {
		super(webview, cordova, senseServicesContext);
	}

	@Override
	public boolean supports(final String action) {
		return "createItemAtPath".equals(action);
	}

	@Override
	void execute(String action, JSONObject options, CallbackContext callbackContext) {
		Log.d(getLogTag(), "createItemAtPath:execute -> " + action + ", " + callbackContext.getCallbackId());
		String path;
		byte[] data;
		try {
			path = options.getString("path");
			data = Base64.decode(options.getString("data"), Base64.DEFAULT);
		} catch (JSONException e) {
			Log.e(getLogTag(), "Problem retrieving parameters. Returning error.", e);
			this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
			return;
		}
		Log.d(getLogTag(), "creating file \"" + path + "\" (size : " + data.length + ")");
		java.io.File userDir = getSenseContext().getFilesDir();
		File file = new File(userDir, path, getSenseContext());

		try {
			if (file.createNewFile()) {
				IOUtils.write(data, new FileOutputStream(file));
				this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, true));
			} else {
				this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, false));
				Log.e(getLogTag(), "Problem creating file. Returning false.");
			}
		} catch (IOException e) {
			Log.e(getLogTag(), "Problem writing file. Returning error.", e);
			this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, false));
		}
	}
}
