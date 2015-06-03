package ch.aimservices.android.proxy;

import android.util.Log;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 16.07.14
 * Time: 11:17
 */
public final class ConfiguratorRegistry {

    private static final String LOG_TAG = "ConfiguratorRegistry";

    private final String applicationClassName;

    private final static ConfiguratorRegistry instance = new ConfiguratorRegistry();

    // One configurator per supported version
    private final Map<Integer, ProxyConfigurator> registeredConfigurators = new HashMap<Integer, ProxyConfigurator>();

    private ConfiguratorRegistry() {
        // TODO: search application class name in some properties file
        applicationClassName = "android.app.Application";
    }

    public static ConfiguratorRegistry getInstance() {
        return instance;
    }

    public final ProxyConfigurator find(final int version) {
        int maxVersion = 0;
        for (final int curVersion : registeredConfigurators.keySet()) {
            if (curVersion <= version) {
                maxVersion = Math.max(maxVersion, curVersion);
            }
        }
        return registeredConfigurators.get(maxVersion);
    }

    public final void registerAll(final Set<ProxyConfigurator> configurators) {
        for (final ProxyConfigurator configurator : configurators) {
            register(configurator);
        }
    }
    public final void register(final ProxyConfigurator configurator) {
        registeredConfigurators.put(configurator.getMaxSupportedVersion(), configurator);
    }

    public final void registerAllClasses(Set<Class<? extends ProxyConfigurator>> classes) {
        for (final Class<? extends ProxyConfigurator> cls : classes) {
            registerClass(cls);
        }
    }

    public final void registerClass(final Class<? extends ProxyConfigurator> cls) {
        try {
            final Constructor<? extends ProxyConfigurator> constructor = getConstructor(cls);
            if (constructor == null) {
                Log.e(LOG_TAG, "Unable to find a constructor for ProxyConfigurator class: " + cls.getName());
            } else {
                // ensure we can call constructor
                constructor.setAccessible(true);
                register(invokeConstructor(constructor));
            }
        } catch (Exception e) {
            // TODO: more precise error handling
            Log.e(LOG_TAG, e.getMessage(), e);
        }
    }

    private <T> T invokeConstructor(Constructor<T> constructor) throws InstantiationException, IllegalAccessException, InvocationTargetException {
        final T instance;
        if (constructor.getParameterTypes().length == 1) {
            instance = constructor.newInstance(applicationClassName);
        } else {
            instance = constructor.newInstance();
        }
        return instance;
    }

    private <T> Constructor<T> getConstructor(Class<T> cls, Class<?>... args) {
        final boolean withArsguments = args != null && args.length > 0;
        final Constructor<T> constructor;
        try {
            if (withArsguments) {
                constructor = cls.getConstructor(args);
            } else {
                constructor = cls.getConstructor();
            }
            return constructor;
        } catch (NoSuchMethodException e) {
            if (!withArsguments) {
                return getConstructor(cls, String.class);
            }
        }
        return null;
    }
    
}
