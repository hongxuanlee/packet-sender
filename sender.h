#ifndef SENDER_OBJECT_H
#define SENDER_OBJECT_H 

#include <node.h>
#include <node_object_wrap.h>
#include "raw.h"
#include <cstdio>

namespace sender{
  class Sender : public node::ObjectWrap {
    public:
      static void Init(v8::Local<v8::Object> exports);
    
    private:
      explicit Sender();
      ~Sender();
      
      static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void sendPacket(const v8::FunctionCallbackInfo<v8::Value>& args);
      static v8::Persistent<v8::Function> constructor;
      int _sork;
  };

}
#endif
