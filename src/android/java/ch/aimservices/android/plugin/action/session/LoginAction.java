package ch.aimservices.android.plugin.action.session;

import java.util.List;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import android.util.Base64;
import android.webkit.WebView;

import ch.aimservices.android.plugin.SenseServicesContext;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 02.09.2014
 * Time: 15:37
 */
public class LoginAction extends AbstractSessionAction {
	private final Logger logger = LoggerFactory.getLogger(LoginAction.class);

    public LoginAction(final WebView webview, final CordovaInterface cordova, final SenseServicesContext senseServicesContext) {
        super(webview, cordova, senseServicesContext);
    }

    @Override
    public boolean supports(final String action) {
        return "login".equals(action);
    }

    @Override
    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) {
        logger.debug("LoginAction:execute -> " + action + ", " + callbackContext.getCallbackId());
        try {
            this.callbackContext = callbackContext;
            final JSONObject options = args.getJSONObject(0);
            final String username = options.getString("username");
            final String password = new String(Base64.decode(options.getString("password"), Base64.DEFAULT));

            if (isUserEnrolled(username)) {
            	logger.debug("Openning Sense session");
                getSenseSessionService().openSession(username, password.toCharArray(), this);
            } else {
            	logger.debug("User " + username + " is not enrolled. Asking for enrollment.");
                success(LOGIN_PINCODE_REQUIRED);
            }
        } catch (final JSONException e) {
        	logger.error("Problem retrieving parameters. Returning error.", e);
            error(ERR_RETRIEVING_PARAMS);
        }
        return true;
    }

    private boolean isUserEnrolled(final String username) {
        final List<String> enrolledUsers = getSenseSessionService().getEnrolledUsers();
        return enrolledUsers != null && enrolledUsers.contains(username);
    }

}
