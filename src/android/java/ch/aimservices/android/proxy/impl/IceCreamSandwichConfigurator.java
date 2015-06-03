package ch.aimservices.android.proxy.impl;

import android.os.Build;
import android.util.Log;
import android.webkit.WebView;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

import ch.aimservices.android.proxy.BaseProxyConfigurator;
import ch.aimservices.android.proxy.ProxyConfigurator;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 16.07.14
 * Time: 10:30
 * To change this template use File | Settings | File Templates.
 */
public class IceCreamSandwichConfigurator extends BaseProxyConfigurator implements ProxyConfigurator {

    @Override
    public int getMaxSupportedVersion() {
        return Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1;
    }

    @Override
    public boolean configure(final WebView webview, final String host, final int port) {
        Log.d(LOG_TAG, "Setting proxy with 4.0 API.");

        try {
            final Class jwcjb = Class.forName("android.webkit.JWebCoreJavaBridge");
            final Class params[] = new Class[1];
            params[0] = Class.forName("android.net.ProxyProperties");
            final Method updateProxyInstance = jwcjb.getDeclaredMethod("updateProxy", params);

            final Class wv = Class.forName("android.webkit.WebView");
            final Field mWebViewCoreField = wv.getDeclaredField("mWebViewCore");
            final Object mWebViewCoreFieldInstance = getFieldValueSafely(mWebViewCoreField, webview);

            final Class wvc = Class.forName("android.webkit.WebViewCore");
            final Field mBrowserFrameField = wvc.getDeclaredField("mBrowserFrame");
            final Object mBrowserFrame = getFieldValueSafely(mBrowserFrameField, mWebViewCoreFieldInstance);

            final Class bf = Class.forName("android.webkit.BrowserFrame");
            final Field sJavaBridgeField = bf.getDeclaredField("sJavaBridge");
            final Object sJavaBridge = getFieldValueSafely(sJavaBridgeField, mBrowserFrame);

            final Class ppclass = Class.forName("android.net.ProxyProperties");
            final Class pparams[] = new Class[3];
            pparams[0] = String.class;
            pparams[1] = int.class;
            pparams[2] = String.class;
            final Constructor ppcont = ppclass.getConstructor(pparams);

            updateProxyInstance.invoke(sJavaBridge, ppcont.newInstance(host, port, null));

            Log.d(LOG_TAG, "Setting proxy with 4.0 API successful!");
            return true;
        } catch (Exception ex) {
            Log.e(LOG_TAG, "failed to set HTTP proxy: " + ex);
            return false;
        }
    }
}
