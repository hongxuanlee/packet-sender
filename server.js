'use strict';

const addon = require('./build/Release/addon');
const net = require('net');
let remain = 0;
let remainData = '';

let server = net.createServer((c) => {
  console.log('client connected');

  console.log(c.localAddress, c.localPort,
    c.remoteAddress, c.remotePort);

  c.on('end', () => {
    console.log('client disconnected');
  });

  c.on('data', (chunk) => {
    console.log('----------data----------');
    console.log(chunk);

    let len = chunk.slice(0, 4).readInt32LE();
    let message = chunk.slice(4);
    let buStr;
    console.log('len', len);
    let prefix = message.toString('ascii', 0, 10);
    console.log(prefix, typeof prefix, 'config'.length, prefix.length, prefix == 'config');

    if (prefix == 'config') {
      let config = chunk.slice(10).toString('ascii');
      console.log('config:', config);
      let str = 'Welcome!';
      buStr = Buffer.from(str, 'utf-8');
    }else{
      console.log('msg', message);
      buStr = Buffer.from('0', 'utf-8');
    }
    console.log('content:', message);
    const bufLength = Buffer.allocUnsafe(4);
    const bufIdentifier = Buffer.allocUnsafe(4);
    bufLength.writeInt32LE(buStr.length + 8, 0);
    bufIdentifier.writeInt32LE(1234, 0);
    let cb_msg = Buffer.concat([bufLength, bufIdentifier, buStr]);
    console.log('send message:');
    console.log(cb_msg);
    c.write(cb_msg);
      
  });
});

server.on('error', (err) => {
  console.log(err);
});

server.listen(8186, () => {
  console.log('server bound at 8186');
});
