const dpapi = require('bindings')('node-windpapi');

module.exports.protect = dpapi.protect;
module.exports.unprotect = dpapi.unprotect;
