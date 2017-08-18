var mosca = require('mosca')
var settings = {
    port: 1883,
    host: '192.168.0.11'
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
    //console.log(packet.payload.topic);
    //console.log(packet.payload.qos);

    var temp = packet.payload[0] + packet.payload[1] * 256;
    //console.log(client);
    console.log(' Published: ' + temp);
});

/* 订阅主题 */
server.on('subscribed', function(topic, client) {
    console.log(client.id + ' subscribed ' + topic);
});

/* 取消订阅主题 */
server.on('unsubscribed', function(topic, client) {
    console.log(client.id + ' unsubscribed ' + topic);
});

var message = {
    topic: 'time',
    payload: 'abcde', // or a Buffer
    qos: 0, // 0, 1, or 2
    retain: false // or true
};

server.publish(message, function() {
    console.log('done!');
});