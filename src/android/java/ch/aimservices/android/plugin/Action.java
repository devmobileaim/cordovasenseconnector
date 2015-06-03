package ch.aimservices.android.plugin;

import org.apache.cordova.CallbackContext;
import org.json.JSONArray;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 17.07.14
 * Time: 08:21
 */
public interface Action {
    public abstract boolean supports(final String action);
    public abstract boolean internal();
    public abstract boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext);
}
