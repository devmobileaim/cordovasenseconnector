package ch.aimservices.android.plugin;

import ch.sysmosoft.sense.android.core.service.Sense;

import static ch.sysmosoft.sense.android.core.service.Sense.SenseServices;
import static ch.sysmosoft.sense.android.core.service.Sense.SessionService;

/**
 * Created by IntelliJ IDEA.
 * User: pblanco
 * Date: 02.09.2014
 * Time: 17:52
 */
public interface SenseServicesContext {
    public SessionService getSessionService();
    public void setSessionService(final SessionService sessionService);

    public SenseServices getSenseServices();
    public void setSenseServices(final SenseServices services);
}
