package ch.aimservices.android.proxy;

import java.lang.reflect.Field;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 16.07.14
 * Time: 10:22
 * To change this template use File | Settings | File Templates.
 */
public abstract class BaseProxyConfigurator implements ProxyConfigurator {

    protected Object getFieldValueSafely(final Field field, final Object classInstance) throws IllegalArgumentException, IllegalAccessException {
        final boolean oldAccessibleValue = field.isAccessible();
        field.setAccessible(true);
        final Object result = field.get(classInstance);
        field.setAccessible(oldAccessibleValue);
        return result;
    }

}
