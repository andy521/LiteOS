var http     = require('http')
  , httpServ = http.createServer()
  , mosca    = require('mosca')
  , mqttServ = new mosca.Server({});

mqttServ.attachHttpServer(httpServ);

function setup() {
    console.log('Mosca server is up & running');
}

mqttServ.on('ready', setup);

httpServ.listen(3000);


// ArrayBuffer转为字符串，参数为ArrayBuffer对象
function ab2str(buf) {
    return String.fromCharCode.apply(null, new Uint8Array(buf));
}

function setup() {
    console.log('Mosca server is up & running');
}

/* client 连接上的事件，client作为参数 */
mqttServ.on('clientConnected', function(client) {
    console.log('Client Connected: ', client.id);
});

/* client 正在断开连接的事件，client作为参数 */
mqttServ.on('clientDisconnecting', function(client) {
    console.log('Client Disconnecting: ', client.id);
});

/* client 断开连接的事件，client作为参数 */
mqttServ.on('clientDisconnected', function(client) {
    console.log('Client Disconnected: ', client.id);
});

/* 接收到新的消息 */
mqttServ.on('published', function(packet, client) {
    console.log(packet.payload);
    //console.log(packet.payload.qos);
    const name = ab2str(packet.payload.slice(0, 31));
    console.log(packet.payload.length);
    console.log(name);
    var temp = packet.payload[0] + packet.payload[1] * 256;
    //console.log(client);
    console.log(' Published: ' + temp);
});

/* 订阅主题 */
mqttServ.on('subscribed', function(topic, client) {
    console.log(client.id + ' subscribed ' + topic);
});

/* 取消订阅主题 */
mqttServ.on('unsubscribed', function(topic, client) {
    console.log(client.id + ' unsubscribed ' + topic);
});

var message = {
    topic: 'time',
    payload: 'abcde', // or a Buffer
    qos: 0, // 0, 1, or 2
    retain: false // or true
};

mqttServ.publish(message, function() {
    console.log('done!');
});