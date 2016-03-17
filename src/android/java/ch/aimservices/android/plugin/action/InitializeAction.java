package ch.aimservices.android.plugin.action;

import android.os.Environment;
import android.util.Log;
import android.webkit.WebView;

import org.apache.commons.io.FileUtils;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.json.JSONArray;

import java.io.File;
import java.util.Collection;

import ch.aimservices.android.plugin.SenseServicesContext;
import ch.sysmosoft.sense.android.core.service.Sense;

import static ch.sysmosoft.sense.android.core.service.Sense.SessionService;
import static ch.sysmosoft.sense.android.core.service.Sense.SessionServiceLifecycleListener;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 17.07.14
 * Time: 08:21
 */
public class InitializeAction extends BaseAction implements SessionServiceLifecycleListener {

    public InitializeAction(final WebView webview, final CordovaInterface cordova, final SenseServicesContext senseServicesContext) {
        super(webview, cordova, senseServicesContext);
    }

    @Override
    public boolean supports(final String action) {
        return "initialize".equals(action);
    }

    @Override
    public boolean internal() {
        return true;
    }

    @Override
    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) {
        Log.d(getLogTag(), "InitializeAction:execute -> " + action);
        // Bind sense session
        Sense.bind(getCordovaActivity(), this);

        cleanupUpdates();
        return true;
    }

    private void cleanupUpdates() {
        final File downloadsFolder = getContext().getExternalFilesDir(Environment.DIRECTORY_DOWNLOADS);
        if (downloadsFolder.isDirectory()) {
            final Collection<File> files = FileUtils.listFiles(downloadsFolder, new String[]{"apk"}, false);
            Log.d(getLogTag(), "Old updates detected: " + files + ". Deleting them...");
            for (File file : files) {
                if (FileUtils.deleteQuietly(file)) {
                    Log.d(getLogTag(), "\tFile: " + file + " deleted");
                }
            }
        }
    }

    @Override
    public void onServiceConnected(final SessionService sessionService) {
        Log.d(getLogTag(), "Session service connected");
        Log.d(getLogTag(), " session is " + (sessionService.isSessionOffline() ? "offline" : "online"));
        senseServicesContext.setSessionService(sessionService);
    }

    @Override
    public void onServiceDisconnected() {
        Log.d(getLogTag(), "Sense service disconnected");
    }
}
