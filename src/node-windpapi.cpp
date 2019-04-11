#include <node.h>
#include <nan.h>
#include <Windows.h>
#include <dpapi.h>

NAN_METHOD(test)
{
	v8::Isolate* isolate = info.GetIsolate();

	if (info.Length() != 2) {
		isolate->ThrowException(v8::Exception::RangeError(
			v8::String::NewFromUtf8(isolate, "Two arguments are required")));
	}

	if (!info[0]->IsNumber()) {
		isolate->ThrowException(v8::Exception::TypeError(
			v8::String::NewFromUtf8(isolate, "First argument must be a number")));
		return;
	}

	if (!info[1]->IsNumber()) {
		isolate->ThrowException(v8::Exception::TypeError(
			v8::String::NewFromUtf8(isolate, "Second argument must be a number")));
		return;
	}

	double sum = info[0]->NumberValue() + info[1]->NumberValue();

	info.GetReturnValue().Set(sum);
}

// public unsafe static byte[] Protect(byte[] userData, byte[] optionalEntropy, DataProtectionScope scope) 
NAN_METHOD(protect)
{
	v8::Isolate* isolate = info.GetIsolate();

	if (info.Length() != 3) {
		isolate->ThrowException(v8::Exception::RangeError(
			v8::String::NewFromUtf8(isolate, "3 arguments are required")));
	}

	if (info[0]->IsNullOrUndefined() || !info[0]->IsUint8Array())
	{
		isolate->ThrowException(v8::Exception::TypeError(
			v8::String::NewFromUtf8(isolate, "First argument, userData, must be a valid Uint8Array")));
	}

	if (!info[1]->IsNull() && !info[1]->IsArrayBuffer())
	{
		isolate->ThrowException(v8::Exception::TypeError(
			v8::String::NewFromUtf8(isolate, "Second argument, optionalEntropy, must be null or an ArrayBuffer")));
	}

	if (info[2]->IsNullOrUndefined() || !info[2]->IsString())
	{
		isolate->ThrowException(v8::Exception::TypeError(
			v8::String::NewFromUtf8(isolate, "Third argument, scope, must be a string")));
	}

	auto message = v8::String::NewFromUtf8(isolate, "You win");
	info.GetReturnValue().Set(message);

	DATA_BLOB blob;
}

NAN_MODULE_INIT(init)
{
	Nan::Set(
		target,
		Nan::New<v8::String>("test").ToLocalChecked(),
		Nan::GetFunction(Nan::New<v8::FunctionTemplate>(test)).ToLocalChecked());

	Nan::Set(
		target,
		Nan::New<v8::String>("protect").ToLocalChecked(),
		Nan::GetFunction(Nan::New<v8::FunctionTemplate>(protect)).ToLocalChecked());
}

NODE_MODULE(binding, init)