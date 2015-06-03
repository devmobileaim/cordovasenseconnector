package ch.aimservices.android.proxy.impl;

import android.content.Context;
import android.os.Build;
import android.util.Log;
import android.webkit.WebView;

import org.apache.http.HttpHost;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

import ch.aimservices.android.proxy.BaseProxyConfigurator;
import ch.aimservices.android.proxy.ProxyConfigurator;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 16.07.14
 * Time: 10:13
 * To change this template use File | Settings | File Templates.
 */
public class HoneycombConfigurator extends BaseProxyConfigurator implements ProxyConfigurator {

    @Override
    public int getMaxSupportedVersion() {
        return Build.VERSION_CODES.HONEYCOMB_MR2;
    }

    @Override
    public boolean configure(final WebView webview, final String host, final int port) {
        Log.d(LOG_TAG, "Setting proxy with <= 3.2 API.");

        final HttpHost proxyServer = new HttpHost(host, port);
        // Getting network
        final Class networkClass;
        Object network = null;
        try {
            networkClass = Class.forName("android.webkit.Network");
            if (networkClass == null) {
                Log.e(LOG_TAG, "failed to get class for android.webkit.Network");
                return false;
            }
            final Method getInstanceMethod = networkClass.getMethod("getInstance", Context.class);
            if (getInstanceMethod == null) {
                Log.e(LOG_TAG, "failed to get getInstance method");
            }
            network = getInstanceMethod.invoke(networkClass, new Object[]{webview.getContext()});
        } catch (Exception ex) {
            Log.e(LOG_TAG, "error getting network: " + ex);
            return false;
        }
        if (network == null) {
            Log.e(LOG_TAG, "error getting network: network is null");
            return false;
        }
        Object requestQueue = null;
        try {
            Field requestQueueField = networkClass.getDeclaredField("mRequestQueue");
            requestQueue = getFieldValueSafely(requestQueueField, network);
        } catch (Exception ex) {
            Log.e(LOG_TAG, "error getting field value");
            return false;
        }
        if (requestQueue == null) {
            Log.e(LOG_TAG, "Request queue is null");
            return false;
        }
        Field proxyHostField = null;
        try {
            final Class requestQueueClass = Class.forName("android.net.http.RequestQueue");
            proxyHostField = requestQueueClass.getDeclaredField("mProxyHost");
        } catch (Exception ex) {
            Log.e(LOG_TAG, "error getting proxy host field");
            return false;
        }

        final boolean temp = proxyHostField.isAccessible();
        try {
            proxyHostField.setAccessible(true);
            proxyHostField.set(requestQueue, proxyServer);
        } catch (Exception ex) {
            Log.e(LOG_TAG, "error setting proxy host");
        } finally {
            proxyHostField.setAccessible(temp);
        }

        Log.d(LOG_TAG, "Setting proxy with <= 3.2 API successful!");
        return true;
    }
}
