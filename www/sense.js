window.sense = {
	_options: function(options) {
		options = options || {};
		options.success = options.success || function() {};
		options.error = options.error || function() {};

		return options;
	},

	_exec: function(action, params, options) {
		options = this._options(options);
		cordova.exec(options.success, options.error, "SenseConnector", action, params);
	},

	updateApp: function(params) {
		this._exec("updateApp", [params]);
	},

	exitApp: function() {
		this._exec("exitApp", []);
	},

	login: function(options, params) {
		this._exec("login", [params], options);
	},

	enroll: function(options, params) {
		this._exec("enroll", [params], options);
	},
	
	changePassword: function(options, params) {
		this._exec("changePassword", [params], options);
	}
};
