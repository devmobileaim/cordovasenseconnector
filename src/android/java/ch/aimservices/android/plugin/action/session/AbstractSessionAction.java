package ch.aimservices.android.plugin.action.session;

import android.os.Build;
import android.util.Log;
import android.webkit.WebView;

import org.apache.cordova.CordovaInterface;

import java.net.InetSocketAddress;
import java.net.Proxy;
import java.net.SocketAddress;

import ch.aimservices.android.plugin.action.BaseAction;
import ch.aimservices.android.plugin.SenseServicesContext;
import ch.aimservices.android.plugin.action.LoginErrorHandler;
import ch.aimservices.android.proxy.ConfiguratorRegistry;
import ch.aimservices.android.proxy.ProxyConfigurator;
import ch.aimservices.android.reflection.Reflections;
import ch.sysmosoft.sense.client.api.SessionStatusListener;

import static ch.sysmosoft.sense.android.core.service.Sense.SenseServices;
import static ch.sysmosoft.sense.android.core.service.Sense.SenseSessionEstablishmentListener;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 02.09.2014
 * Time: 17:20
 */
public abstract class AbstractSessionAction extends BaseAction implements SenseSessionEstablishmentListener, SessionStatusListener {

    // Result codes
    public static final int LOGIN_OK = 0;
    public static final int LOGIN_PINCODE_REQUIRED = 1;
    public static final int LOGIN_UPDATE_AVAILABLE = 2;
    public static final int SESSION_EXPIRED = 3;
    public static final int SESSION_LOCKED = 4;

    // Error codes
    public static final String ERR_LOGIN_FAILED = "ERR_LOGIN_FAILED";
    public static final String ERR_NO_PROXY_CONFIGURATOR = "ERR_NO_PROXY_CONFIGURATOR";
    public static final String ERR_PROXY_CONFIGURATION = "ERR_PROXY_CONFIGURATION";

    private final ConfiguratorRegistry registry = ConfiguratorRegistry.getInstance();

    private final LoginErrorHandler loginErrorHandler = new LoginErrorHandler();

    public AbstractSessionAction(final WebView webview, final CordovaInterface cordova, final SenseServicesContext senseServicesContext) {
        super(webview, cordova, senseServicesContext);
        initializeConfiguratorRegistry();
    }

    private void initializeConfiguratorRegistry() {
        final Reflections reflections = new Reflections(getContext(), "ch.aimservices.android.proxy.impl");
        registry.registerAllClasses(reflections.getSubTypesOf(ProxyConfigurator.class));
    }

    private boolean configure(final String host, final int port) {
        final ProxyConfigurator configurator = registry.find(Build.VERSION.SDK_INT);
        if (configurator == null) {
            return false;
        }
        return configurator.configure(webview, host, port);
    }

    /* ==================================================== */
    /* = SenseSessionEstablishmentListener Implementation = */
    /* ==================================================== */

    @Override
    public void onLoginSuccessful(final SenseServices senseServices) {
        Log.d(getLogTag(), "Login successful");

        final Proxy proxy = senseServices.getProxyConfig().getProxy();
        final SocketAddress proxyAddress = proxy.address();

        if (proxyAddress instanceof InetSocketAddress) {
            senseServicesContext.setSenseServices(senseServices);

            final InetSocketAddress isa = (InetSocketAddress) proxyAddress;
            final String host = isa.getHostString();
            final int port = isa.getPort();

            if (configure(host, port)) {
			    senseServices.addSessionStatusListener(this);
                Log.d(getLogTag(), "Proxy configured successfully");
                success(LOGIN_OK, true);
            } else {
                Log.d(getLogTag(), "No proxy configurator found");
                error(ERR_NO_PROXY_CONFIGURATOR);
            }
        } else {
            Log.d(getLogTag(), "Unable to understand proxy configuration");
            getSenseSessionService().closeSession();
            error(ERR_PROXY_CONFIGURATION);
        }
    }

    @Override
    public void onApplicationUpToDate() {
    	// Do nothing
    }
    
    @Override
    public void onUpdateAvailable(final String update) {
        Log.d(getLogTag(), "Update available. " + update);
        success(LOGIN_UPDATE_AVAILABLE, update, true);
    }

    @Override
    public void onLoginFailed(final Throwable cause) {
        Log.d(getLogTag(), "Login failed.", cause);
        final LoginErrorHandler.Error error = loginErrorHandler.handleError(cause);
        error(error.getCode(), error.getMessage());
    }

    /* ======================================== */
    /* = SessionStatusListener Implementation = */
    /* ======================================== */

    @Override
    public void willExpire() {
    	Log.d(getLogTag(), "Session is about to expire.");
    }
    
    @Override
    public void hasExpired() {
        Log.d(getLogTag(), "Session has expired.");
		senseServicesContext.setSenseServices(null);
		success(SESSION_EXPIRED);
    }

    @Override
    public void hasLocked() {
        Log.d(getLogTag(), "Session has been locked.");
        success(SESSION_LOCKED);
    } 
}
