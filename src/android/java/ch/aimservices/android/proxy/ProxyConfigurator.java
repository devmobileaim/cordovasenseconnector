package ch.aimservices.android.proxy;

import android.webkit.WebView;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 16.07.14
 * Time: 10:07
 * To change this template use File | Settings | File Templates.
 */
public interface ProxyConfigurator {
    public int getMaxSupportedVersion();
    public boolean configure(WebView webview, final String host, final int port);
}
