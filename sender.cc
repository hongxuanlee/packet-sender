#include "sender.h"

namespace sender{
    using v8::Context;
    using v8::Function;
    using v8::FunctionCallbackInfo;
    using v8::FunctionTemplate;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Integer;
    using v8::Object;
    using v8::Persistent;
    using v8::String;
    using v8::Value;
    using v8::Exception;

    using namespace std;

    char* hextostr(string hexStr)
    {
        size_t len = hexStr.length();
        cout << "length" << len << endl;
        int k = 0;
        int c;
        char* output = new char[(len/2)+1];
        for (size_t i = 0; i < len; i+=2)
        {
            sscanf(&hexStr.c_str()[i], "%2x", &c); 
            output[k++] = (char) c;
        }
        output[k] = '\0';
        return output;
    }

    const char* ToCString(const String::Utf8Value& value) {
       return *value ? *value : "<string conversion failed>";
    }

    Persistent<Function> Sender::constructor;

    Sender::Sender() {
    }

    Sender::~Sender() {
    }

    void Sender::Init(Local<Object> exports) {
        Isolate* isolate = exports->GetIsolate();
        Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
        tpl->SetClassName(String::NewFromUtf8(isolate, "Sender"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        NODE_SET_PROTOTYPE_METHOD(tpl, "sendPacket", sendPacket);

        constructor.Reset(isolate, tpl->GetFunction());
        exports->Set(String::NewFromUtf8(isolate, "Sender"),
                tpl->GetFunction());
    }

    void Sender::New(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall()) {
            // Invoked as constructor: `new Sender(...)`
            Sender* obj = new Sender();
            obj->Wrap(args.This());
            obj->_sork = createRawSocket();
            args.GetReturnValue().Set(Integer::New(isolate, obj->_sork));
        } else {
            isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "need construct call")));
            return;
        }
    }

    void Sender::sendPacket(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        String::Utf8Value str(args[0]);
        String::Utf8Value datagram(args[2]);
        int port = args[1] -> NumberValue(); 
        int length = args[3] -> NumberValue();
        char* buffer = hextostr(string(*datagram));
        Sender* obj = ObjectWrap::Unwrap<Sender>(args.Holder());
        int res = sendRawPacket(obj -> _sork, ToCString(str), port, buffer, length); 
        args.GetReturnValue().Set(Integer::New(isolate, res));
    }
}
