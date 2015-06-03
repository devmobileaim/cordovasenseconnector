package ch.aimservices.android.plugin.action;

import android.util.Base64;
import android.util.Log;
import android.webkit.WebView;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import ch.aimservices.android.plugin.SenseServicesContext;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 02.09.2014
 * Time: 17:27
 */
public class EnrollAction extends AbstractSessionAction {

    public EnrollAction(final WebView webview, final CordovaInterface cordova, final SenseServicesContext senseServicesContext) {
        super(webview, cordova, senseServicesContext);
    }

    @Override
    public boolean supports(final String action) {
        return "enroll".equals(action);
    }

    @Override
    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) {
        Log.d(getLogTag(), "EnrollAction:execute -> " + action + ", " + callbackContext.getCallbackId());
        try {
            this.callbackContext = callbackContext;
            final JSONObject options = args.getJSONObject(0);

            final String username = options.getString("username");
            final String password = new String(Base64.decode(options.getString("password"), Base64.DEFAULT));
            final String pincode = options.getString("pincode");

            getSenseSessionService().enrollUser(username, password.toCharArray(), pincode.toCharArray(), this);
        } catch (JSONException e) {
            Log.e(getLogTag(), "Problem retrieving parameters. Returning error.", e);
            error(ERR_RETRIEVING_PARAMS);
        }
        return true;
    }
}
