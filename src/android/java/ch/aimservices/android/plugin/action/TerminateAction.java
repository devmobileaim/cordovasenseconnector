package ch.aimservices.android.plugin.action;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.json.JSONArray;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import android.webkit.WebView;

import ch.aimservices.android.plugin.SenseServicesContext;
import ch.sysmosoft.sense.android.core.service.Sense;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 03.09.2014
 * Time: 11:29
 */
public class TerminateAction extends BaseAction {
	private final Logger logger = LoggerFactory.getLogger(TerminateAction.class);

    public TerminateAction(final WebView webview, final CordovaInterface cordova, final SenseServicesContext senseServicesContext) {
        super(webview, cordova, senseServicesContext);
    }

    @Override
    public boolean supports(final String action) {
        return "terminate".equals(action);
    }

    @Override
    public boolean internal() {
        return true;
    }

    @Override
    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) {
    	logger.debug("TerminateAction:execute -> " + action);
        // Bind sense session
    	logger.debug("Unbinding sense");
        Sense.unbind(getCordovaActivity());

        return true;
    }
}
