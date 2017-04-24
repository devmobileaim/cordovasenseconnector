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

	logout: function(){
		this._exec("logout", []);
	},

	enroll: function(options, params) {
		this._exec("enroll", [params], options);
	},
	
	changePassword: function(options, params) {
		this._exec("changePassword", [params], options);
	},

	createItemAtPath: function(options, params) {
		this._exec("createItemAtPath", [params], options);
	},

	itemExistsAtPath: function(options, params) {
		this._exec("itemExistsAtPath", [params], options);
	},

	contentsAtPath: function(options, params) {
		this._exec("contentsAtPath", [params], options);
	},

	moveItemAtPath: function(options, params) {
		this._exec("moveItemAtPath", [params], options);
	},

	removeItemAtPath: function(options, params) {
		this._exec("removeItemAtPath", [params], options);
	}
  
};
