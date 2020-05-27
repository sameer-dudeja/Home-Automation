$(function(){
 var client = mqtt.connect('mqtt://try:try@broker.shiftr.io', {
   clientId: 'browser-client'
 });

 client.on('connect', function(){
   console.log('client has connected!');
 });

 client.on('message', function(topic, message) {
  $('#data').text(message.toString());
 });
   client.subscribe('nodemcu/photocell');
})