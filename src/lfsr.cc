#include <node.h>
#include <stdint.h>

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Value;
using v8::Exception;
const uint64_t mask = 0x12345678;
//const uint64_t mask = 0x1234;

uint64_t lfsr_next(uint64_t current)
{
  // 32 bit
  uint64_t bit = ((current >> 0) ^ (current >> 2) ^ (current >> 6) ^ (current >> 7)) & 1;
  return (current >> 1) | (bit << 31);

  // 16 bit
  //uint64_t bit = ((current >> 0) ^ (current >> 2) ^ (current >> 3) ^ (current >> 5)) & 1;
  //return (current >> 1) | (bit << 15);
}

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }
  if (!args[0]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }
  uint64_t current = args[0]->NumberValue();
  current ^= mask;
  uint64_t next = lfsr_next(current);
  next ^= mask;
  Local<Number> num = Number::New(isolate, next);
  args.GetReturnValue().Set(num);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "next", Method);
}

NODE_MODULE(addon, init)

}  // namespace demo
