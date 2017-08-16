var mosca = require('mosca')
var settings = {
    port: 1883

};
var server = new mosca.Server(settings);
server.on('ready', setup);

function setup() {
    console.log('Mosca server is up & running');
}

/* client 连接上的事件，client作为参数 */
server.on('clientConnected', function(client) {
    console.log('Client Connected: ', client.id);
});

/* client 正在断开连接的事件，client作为参数 */
server.on('clientDisconnecting', function(client) {
    console.log('Client Disconnecting: ', client.id);
});

/* client 断开连接的事件，client作为参数 */
server.on('clientDisconnected', function(client) {
    console.log('Client Disconnected: ', client.id);
});

/* 接收到新的消息 */
server.on('published', function(packet, client) {
    console.log('Published', packet.payload);
});

/* 订阅主题 */
server.on('subscribed', function(topic, client) {
    console.log('subscribed', client.id);
    console.log(topic);
});

/* 取消订阅主题 */
server.on('unsubscribed', function(topic, client) {
    console.log('unsubscribed', client.id);
    console.log(topic);
});