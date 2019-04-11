const dpapi = require ('./build/Release/node-windpapi');
const sum = dpapi.test(1, 6);
console.log(`1 + 6 = ${sum}`);

const buffer = Buffer.from("Hello World", "utf-8");

const result = dpapi.protect(buffer, null, 'user');
console.log(`Result '${result}'`);