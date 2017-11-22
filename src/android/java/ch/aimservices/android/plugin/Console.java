package ch.aimservices.android.plugin;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.json.JSONArray;
import org.json.JSONException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Console extends CordovaPlugin {

	private final Logger logger = LoggerFactory.getLogger("Console");

	public Console() {
	}

	@Override
	public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) throws 
	JSONException {
		if (args == null) {
			return false;
		}

		String level = args.getString(0);
		String message = args.getString(1);
		if (level == null || message == null) {
			return false;
		}

		if ("LOG".equals(level)) {
			logger.debug(message);
		} else if ("INFO".equals(level)) {
			logger.info(message);
		} else if ("DEBUG".equals(level)) {
			logger.trace(message);
		} else if ("WARN".equals(level)) {
			logger.warn(message);
		} else if ("ERROR".equals(level)) {
			logger.error(message);
		}
		return true;
	}
}
