package ch.aimservices.android.plugin.action;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.json.JSONArray;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import android.webkit.WebView;

import ch.aimservices.android.plugin.SenseServicesContext;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 03.09.2014
 * Time: 11:29
 */
public class ExitAppAction extends BaseAction {
	private final Logger logger = LoggerFactory.getLogger(ExitAppAction.class);

    public ExitAppAction(final WebView webview, final CordovaInterface cordova, final SenseServicesContext senseServicesContext) {
        super(webview, cordova, senseServicesContext);
    }

    @Override
    public boolean supports(final String action) {
        return "exitApp".equals(action);
    }

    @Override
    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) {
        logger.debug("ExitAppAction:execute -> " + action);
        getCordovaActivity().finish();
		System.exit(0);
        return true;
    }
}
