const addon = require('./build/Release/addon');

class Sender{
    constructor(options = {}){
      this.options = options; 
      this.sender = new addon.Sender();
    }
    
    sendPacket(ip, port, buffer, length){
      return this.sender.sendPacket(ip, port, buffer, length);
    }
}

let writeChecksum = function (buffer, offset, checksum) {
    buffer.writeUInt8 ((checksum & 0xff00) >> 8, offset);
    buffer.writeUInt8 (checksum & 0xff, offset + 1);
    return buffer;
}

let htonl = function(n){
    return [
        (n & 0xFF000000) >>> 24,
        (n & 0x00FF0000) >>> 16,
        (n & 0x0000FF00) >>>  8,
        (n & 0x000000FF) >>>  0,
        ];
}

let createSender = function (options) {
    return new Sender (options || {});
};

module.exports = Sender;
