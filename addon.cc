#include <node.h>
#include <node_object_wrap.h>
#include "sender.h"
#include <string>

namespace sender {

    using v8::Local;
    using v8::Object;

    void InitAll(Local<Object> exports) {
        Sender::Init(exports);
    }

    NODE_MODULE(addon, InitAll)

}
