package ch.aimservices.android.plugin.action;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import ch.sysmosoft.sense.client.exception.DeviceNotCompliantException;
import ch.sysmosoft.sense.client.exception.InvalidNewPasswordException;
import ch.sysmosoft.sense.client.exception.PasswordNotChangedException;
import ch.sysmosoft.sense.client.exception.UserAlreadyEnrolledException;
import ch.sysmosoft.sense.client.exception.UserDisenrolledException;
import ch.sysmosoft.sense.common.server.exception.AccessDeniedException;
import ch.sysmosoft.sense.common.server.exception.AccountLockedException;
import ch.sysmosoft.sense.common.server.exception.AuthenticationException;
import ch.sysmosoft.sense.common.server.exception.ServerException;

/**
 * Created by aim on 05.03.2015.
 */
public class LoginErrorHandler {

    public static final String ERR_WRONG_CREDENTIALS = "ERR_WRONG_CREDENTIALS";
    public static final String ERR_LOGIN_FAILED = "ERR_LOGIN_FAILED";
    public static final String ERR_USER_DISENROLLED = "ERR_USER_DISENROLLED";
    public static final String ERR_USER_ALREADY_ENROLLED = "ERR_USER_ALREADY_ENROLLED";
    public static final String ERR_DEVICE_NOT_COMPLIANT = "ERR_DEVICE_NOT_COMPLIANT";
    public static final String ERR_ACCESS_DENIED = "ERR_ACCESS_DENIED";
    public static final String ERR_ACCOUNT_LOCKED = "ERR_ACCESS_DENIED";
    public static final String ERR_PASSWORD_NOT_CHANGED = "ERR_PASSWORD_NOT_CHANGED";
    public static final String ERR_INVALID_NEW_PASSWORD = "ERR_PASSWORD_NOT_CHANGED";

    private static final class ErrorDescription {
        String code;
        boolean useMessage = false;
        ErrorDescription(final String code) {
            this.code = code;
        }
        ErrorDescription(final String code, final boolean useMessage) {
            this(code);
            this.useMessage = useMessage;
        }
    }

    public static final class Error {
        private final String code;
        private final String message;

        public Error(final String code, final String message) {
            this.code = code;
            this.message = message;
        }

        public String getCode() {
            return code;
        }

        public String getMessage() {
            return message;
        }
    }

    private static final Map<Class<? extends Throwable>, ErrorDescription> loginErrorMap;
    static {
        loginErrorMap = new HashMap<Class<? extends Throwable>, ErrorDescription>();
        loginErrorMap.put(AuthenticationException.class, new ErrorDescription(ERR_WRONG_CREDENTIALS));
        loginErrorMap.put(UserDisenrolledException.class, new ErrorDescription(ERR_USER_DISENROLLED));
        loginErrorMap.put(UserAlreadyEnrolledException.class, new ErrorDescription(ERR_USER_ALREADY_ENROLLED));
        loginErrorMap.put(DeviceNotCompliantException.class, new ErrorDescription(ERR_DEVICE_NOT_COMPLIANT));
        loginErrorMap.put(AccessDeniedException.class, new ErrorDescription(ERR_ACCESS_DENIED));
        loginErrorMap.put(AccountLockedException.class, new ErrorDescription(ERR_ACCOUNT_LOCKED));
        loginErrorMap.put(ServerException.class, new ErrorDescription(ERR_LOGIN_FAILED));
        loginErrorMap.put(PasswordNotChangedException.class, new ErrorDescription(ERR_PASSWORD_NOT_CHANGED));
        loginErrorMap.put(InvalidNewPasswordException.class, new ErrorDescription(ERR_INVALID_NEW_PASSWORD));
        loginErrorMap.put(IOException.class, new ErrorDescription(ERR_LOGIN_FAILED));
    }

    public Error handleError(final Throwable cause) {
        final Class<? extends Throwable> causeCls = cause.getClass();
        final String errorCode;
        String errorMessage = null;
        if (loginErrorMap.containsKey(causeCls)) {
            final ErrorDescription description = loginErrorMap.get(causeCls);
            errorCode = description.code;
            if (description.useMessage) {
                errorMessage = cause.getMessage();
            }
        } else {
            errorCode = ERR_LOGIN_FAILED;
        }

        return new Error(errorCode, errorMessage);
    }
}
