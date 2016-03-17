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
import ch.sysmosoft.sense.android.core.service.context.FileInputStream;
import ch.sysmosoft.sense.android.core.service.context.FileOutputStream;

public class GetItemAction extends AbstractFileSystemAction {

	public GetItemAction(final WebView webview, final CordovaInterface cordova,
			final SenseServicesContext senseServicesContext) {
		super(webview, cordova, senseServicesContext);
	}

	@Override
	public boolean supports(final String action) {
		return "contentsAtPath".equals(action);
	}

	@Override
	void execute(String action, JSONObject options, CallbackContext callbackContext) {
		Log.d(getLogTag(), "contentsAtPath:execute -> " + action + ", " + callbackContext.getCallbackId());
		String path;
		try {
			path = options.getString("path");
		} catch (JSONException e) {
			Log.e(getLogTag(), "Problem retrieving parameters. Returning error.", e);
			this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
			return;
		}
		Log.d(getLogTag(), "retrieving file \"" + path + "\"");
		java.io.File userDir = getSenseContext().getFilesDir();
		File file = new File(userDir, path, getSenseContext());

		try {
			byte[] data = IOUtils
					.toByteArray(new FileInputStream(file, senseServicesContext.getSenseServices().getSenseContext()));
			IOUtils.write(data, new FileOutputStream(file));
			this.callbackContext
					.sendPluginResult(new PluginResult(PluginResult.Status.OK, Base64.encode(data, Base64.DEFAULT)));
		} catch (IOException e) {
			Log.e(getLogTag(), "Problem writing file. Returning error.", e);
			this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
		}
	}
}