var mosca = require('mosca');
var express = require('express');
var https = require('http');
var fs = require('fs');

var app = express();

var name;
/**
 * CORS support.
 */
app.all('*', function(req, res, next) {
    //console.log("fdsafdsa")
    res.set('Access-Control-Allow-Origin', '*');
    res.set('Access-Control-Allow-Methods', 'GET');
    res.set('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type');
    // res.set('Access-Control-Allow-Max-Age', 3600);
    if ('OPTIONS' == req.method) return res.send(200);
    next();
});

app.get('/iot/temperature', function(req, res) {
    console.log(req);
    res.send(name);
});

/* 启动https */
var options = {
    key: fs.readFileSync('./cert/chyingp-key.pem'),
    cert: fs.readFileSync('./cert/chyingp-cert.pem')
};

https.createServer(app).listen(80);

var settings = {
    port: 1883,
    host: '192.168.0.11'
};
var server = new mosca.Server(settings);
server.on('ready', setup);

// ArrayBuffer转为字符串，参数为ArrayBuffer对象
function ab2str(buf) {
    return String.fromCharCode.apply(null, new Uint8Array(buf));
}

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
    console.log(packet.payload);
    //console.log(packet.payload.qos);
    name = ab2str(packet.payload.slice(0, 31));
    //console.log(packet.payload.length);
    console.log(name);
    //var temp = packet.payload[0] + packet.payload[1] * 256;
    //console.log(client);
    console.log(' Published: ' + name);
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