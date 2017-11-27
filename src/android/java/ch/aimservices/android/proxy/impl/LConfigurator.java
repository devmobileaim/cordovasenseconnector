package ch.aimservices.android.proxy.impl;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import android.content.Context;
import android.content.Intent;
import android.net.Proxy;
import android.os.Parcelable;
import android.util.ArrayMap;
import android.webkit.WebView;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import ch.aimservices.android.proxy.BaseProxyConfigurator;
import ch.aimservices.android.proxy.ProxyConfigurator;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 16.07.14
 * Time: 10:51
 * To change this template use File | Settings | File Templates.
 */
// TODO: rename class with final Android codename
public class LConfigurator extends BaseProxyConfigurator implements ProxyConfigurator {
	private final Logger logger = LoggerFactory.getLogger(LConfigurator.class);

    private final String applicationClassName;

    public LConfigurator(final String applicationClassName) {
        this.applicationClassName = applicationClassName;
    }

    @Override
    public int getMaxSupportedVersion() {
        // TODO: put final version number here
        return 20;
    }

    @Override
    public boolean configure(WebView webview, String host, int port) {
    	logger.debug("Setting proxy with > 4.4 API.");

        final Context appContext = webview.getContext().getApplicationContext();
        System.setProperty("http.proxyHost", host);
        System.setProperty("http.proxyPort", port + "");
        System.setProperty("https.proxyHost", host);
        System.setProperty("https.proxyPort", port + "");
        try {
            final Class applicationCls = Class.forName(applicationClassName);
            final Field loadedApkField = applicationCls.getField("mLoadedApk");
            loadedApkField.setAccessible(true);
            final Object loadedApk = loadedApkField.get(appContext);
            final Class loadedApkCls = Class.forName("android.app.LoadedApk");
            final Field receiversField = loadedApkCls.getDeclaredField("mReceivers");
            receiversField.setAccessible(true);
            final ArrayMap receivers = (ArrayMap) receiversField.get(loadedApk);
            for (final Object receiverMap : receivers.values()) {
                for (final Object rec : ((ArrayMap) receiverMap).keySet()) {
                    final Class clazz = rec.getClass();
                    if (clazz.getName().contains("ProxyChangeListener")) {
                        final Method onReceiveMethod = clazz.getDeclaredMethod("onReceive", Context.class, Intent.class);
                        final Intent intent = new Intent(Proxy.PROXY_CHANGE_ACTION);

                        /*********** optional, may be need in future *************/
                        final String CLASS_NAME = "android.net.ProxyInfo";
                        final Class cls = Class.forName(CLASS_NAME);

                        final Method factoryMethod = cls.getDeclaredMethod("buildDirectProxy", String.class, int.class);

                        final Object proxyProperties = factoryMethod.invoke(null, host, port);
                        intent.putExtra("proxy", (Parcelable) proxyProperties);
                        /*********** optional, may be need in future *************/

                        onReceiveMethod.invoke(rec, appContext, intent);
                    }
                }
            }

            logger.debug("Setting proxy with > 4.4 API successful!");
            return true;
        } catch (ClassNotFoundException e) {
            logger.error(e.getMessage(), e);
        } catch (NoSuchFieldException e) {
            logger.error(e.getMessage(), e);
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage(), e);
        } catch (IllegalArgumentException e) {
            logger.error(e.getMessage(), e);
        } catch (NoSuchMethodException e) {
            logger.error(e.getMessage(), e);
        } catch (InvocationTargetException e) {
            logger.error(e.getMessage(), e);
        }
        return false;
    }
}
