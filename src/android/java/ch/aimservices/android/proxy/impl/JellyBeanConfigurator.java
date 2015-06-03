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
 * Time: 10:35
 * To change this template use File | Settings | File Templates.
 */
public class JellyBeanConfigurator extends BaseProxyConfigurator implements ProxyConfigurator {

    @Override
    public int getMaxSupportedVersion() {
        return Build.VERSION_CODES.JELLY_BEAN_MR2;
    }

    @Override
    public boolean configure(final WebView webview, final String host, final int port) {
        Log.d(LOG_TAG, "Setting proxy with 4.1 - 4.3 API.");

        try {
            final Class wvcClass = Class.forName("android.webkit.WebViewClassic");
            final Class wvParams[] = new Class[1];
            wvParams[0] = Class.forName("android.webkit.WebView");
            final Method fromWebView = wvcClass.getDeclaredMethod("fromWebView", wvParams);
            final Object webViewClassic = fromWebView.invoke(null, webview);

            final Class wv = Class.forName("android.webkit.WebViewClassic");
            final Field mWebViewCoreField = wv.getDeclaredField("mWebViewCore");
            final Object mWebViewCoreFieldInstance = getFieldValueSafely(mWebViewCoreField, webViewClassic);

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

            final Class jwcjb = Class.forName("android.webkit.JWebCoreJavaBridge");
            final Class params[] = new Class[1];
            params[0] = Class.forName("android.net.ProxyProperties");
            final Method updateProxyInstance = jwcjb.getDeclaredMethod("updateProxy", params);

            updateProxyInstance.invoke(sJavaBridge, ppcont.newInstance(host, port, null));
        } catch (Exception ex) {
            Log.e(LOG_TAG, "Setting proxy with >= 4.1 API failed with error: " + ex.getMessage());
            return false;
        }

        Log.d(LOG_TAG, "Setting proxy with 4.1 - 4.3 API successful!");
        return true;
    }
}
