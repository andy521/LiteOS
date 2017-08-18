var mqtt = require('mqtt')
var client = mqtt.connect('http://192.168.0.11')

client.on('connect', function() {
    client.subscribe('temperature')

    //client.publish('presence', 'Hello mqtt')
})

client.on('message', function(topic, message) {
    // message is Buffer
    var temp = message[0] + message[1] * 256;
    console.log(topic + ': ' + temp);
    //client.end()
})