package ch.aimservices.android.reflection;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import android.content.Context;

import java.util.Collections;
import java.util.Enumeration;
import java.util.HashSet;
import java.util.Set;

import dalvik.system.DexFile;

/**
 * Created by pblanco on 21.08.2014.
 */
public class Reflections {
	private final Logger logger = LoggerFactory.getLogger(Reflections.class);

    private final Context context;

    private final Set<String> pkgs = new HashSet<String>();

    public Reflections(Context context, final String... pkgs) {
        this.context = context;
        Collections.addAll(this.pkgs, pkgs);
    }

    public <T> Set<Class<? extends T>> getSubTypesOf(final Class<T> type) {
        final Set<Class<? extends T>> subTypes = new HashSet<Class<? extends T>>();
        try {
            final ClassLoader classLoader = Thread.currentThread().getContextClassLoader();

            final String sourceDir = context.getApplicationInfo().sourceDir;
            final DexFile dexFile = new DexFile(sourceDir);
            final Enumeration<String> entries = dexFile.entries();
            while (entries.hasMoreElements()) {
                // Each entry is a class name, like "foo.bar.MyClass"
                final String entry = entries.nextElement();

                if (!inPackages(entry)) {
                    continue;
                }

                // Load the class
                //final Class<?> entryClass = dexFile.loadClass(entry, classLoader);
                final Class<?> entryClass = classLoader.loadClass(entry);
                if (entryClass != null) {
                    if (type.isAssignableFrom(entryClass)) {
                        subTypes.add(entryClass.asSubclass(type));
                    }
                }
            }
        } catch (Exception e) {
            // TODO: more precise error handling
            logger.error("Error", e);
        }
        return subTypes;
    }

    private boolean inPackages(final String entry) {
        for (final String pkg : pkgs) {
            if (entry.startsWith(pkg)) {
                return true;
            }
        }
        return false;
    }

}
