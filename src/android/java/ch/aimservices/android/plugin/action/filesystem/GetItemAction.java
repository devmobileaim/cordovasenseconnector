package ch.aimservices.android.plugin.action.filesystem;

import java.io.IOException;

import org.apache.commons.io.IOUtils;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.PluginResult;
import org.json.JSONException;
import org.json.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import android.util.Base64;
import android.webkit.WebView;

import ch.aimservices.android.plugin.SenseServicesContext;
import ch.sysmosoft.sense.android.core.service.context.File;
import ch.sysmosoft.sense.android.core.service.context.FileInputStream;
import ch.sysmosoft.sense.android.core.service.context.FileOutputStream;

public class GetItemAction extends AbstractFileSystemAction {
	private final Logger logger = LoggerFactory.getLogger(GetItemAction.class);

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
		logger.debug("contentsAtPath:execute -> " + action + ", " + callbackContext.getCallbackId());
		String path;
		try {
			path = options.getString("path");
		} catch (JSONException e) {
			logger.error("Problem retrieving parameters. Returning error.", e);
			this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
			return;
		}
		logger.debug("retrieving file \"" + path + "\"");
		java.io.File userDir = getSenseContext().getFilesDir();
		File file = new File(userDir, path, getSenseContext());

		try {
			byte[] data = IOUtils
					.toByteArray(new FileInputStream(file, senseServicesContext.getSenseServices().getSenseContext()));
			IOUtils.write(data, new FileOutputStream(file));
			this.callbackContext.sendPluginResult(
					new PluginResult(PluginResult.Status.OK, Base64.encodeToString(data, Base64.DEFAULT)));
		} catch (IOException e) {
			logger.error("Problem writing file. Returning error.", e);
			this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, false));
		}
	}
}