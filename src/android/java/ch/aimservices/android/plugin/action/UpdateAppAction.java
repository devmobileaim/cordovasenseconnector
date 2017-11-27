package ch.aimservices.android.plugin.action;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;


import android.app.DownloadManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.Uri;
import android.os.Environment;
import android.webkit.WebView;
import android.widget.Toast;

import ch.aimservices.android.plugin.SenseServicesContext;

import static android.app.DownloadManager.Request;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 17.07.14
 * Time: 08:21
 */
public class UpdateAppAction extends BaseAction {
	private final Logger logger = LoggerFactory.getLogger(UpdateAppAction.class);

    private final DownloadManager downloadManager;

    private long downloadReference;

    //broadcast receiver to get notification about ongoing downloads
    private final BroadcastReceiver downloadReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(final Context context, final Intent intent) {
            //check if the broadcast message is for our Enqueued download
            final long referenceId = intent.getLongExtra(DownloadManager.EXTRA_DOWNLOAD_ID, -1);
            if (downloadReference == referenceId) {
            	logger.debug("Downloading application update complete");
                //start the installation of the latest version
                final Intent installIntent = new Intent(Intent.ACTION_VIEW);
                final Uri downloadUri = downloadManager.getUriForDownloadedFile(downloadReference);
                logger.debug("Download uri: " + downloadUri);
                installIntent.setDataAndType(downloadUri, "application/vnd.android.package-archive");
                installIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);

                getContext().startActivity(installIntent);

                // Finished so unregister broadcast receiver
                UpdateAppAction.this.unregisterReceiver();
            }
        }
    };

    public UpdateAppAction(final WebView webview, final CordovaInterface cordova, final SenseServicesContext senseServicesContext) {
        super(webview, cordova, senseServicesContext);
        downloadManager = (DownloadManager) getCordovaActivity().getSystemService(Context.DOWNLOAD_SERVICE);
    }

    @Override
    public boolean supports(final String action) {
        return "updateApp".equals(action);
    }

    @Override
    public boolean execute(final String action, final JSONArray args, final CallbackContext callbackContext) {
    	logger.debug("UpdateAppAction:execute -> " + action);
        try {
            this.callbackContext = callbackContext;

            final JSONObject options = args.getJSONObject(0);
            final String url = options.getString("url");

            startDownload(url);
            success(0);
        } catch (final JSONException e) {
            logger.error("Problem retrieving parameters. Returning error.", e);
            error(ERR_RETRIEVING_PARAMS);
        }
        return true;
    }

    private void startDownload(final String url) {
        registerReceiver();

        final Uri downloadUri = Uri.parse(url);
        final Request request = new Request(downloadUri);
        request.setTitle("Application update");
        request.setDestinationInExternalFilesDir(getCordovaActivity(), Environment.DIRECTORY_DOWNLOADS, "MainActivity.apk");

        Toast.makeText(getContext(), "Launching application update, please wait...", Toast.LENGTH_LONG).show();

        downloadReference = downloadManager.enqueue(request);
    }

    private void registerReceiver() {
        // Broadcast receiver for the download manager
        final IntentFilter filter = new IntentFilter(DownloadManager.ACTION_DOWNLOAD_COMPLETE);
        getCordovaActivity().registerReceiver(downloadReceiver, filter);
    }

    private void unregisterReceiver() {
        // Finished receiving broadcast for downloads
        getCordovaActivity().unregisterReceiver(downloadReceiver);
    }
}
