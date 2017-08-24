## raw ip packet sender for NodeJs

### usage

```
const dest_ip = '30.8.77.76';
const dest_port = 8124;

let buffer = "4500003c552340003806761f6445a7e01e084d4c8a751fbcd3b00c9300000000a002390822080000020405b40402080a915059b00000000001030307";

const obj = new addon.Sender();

obj.sendPacket(dest_ip, dest_port, buffer, 60);

```

