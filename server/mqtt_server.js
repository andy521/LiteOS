var mosca = require('mosca')
var settings = {
    port: 1883

};
var server = new mosca.Server(settings);
server.on('ready', setup);

function setup() {
    console.log('Mosca server is up & running');
}

server.on('clientConnected', function(client) {
    console.log('Client Connected: ', client.id);
});

server.on('clientDisconnected', function(client) {
    console.log('Client Disconnected: ', client.id);
});