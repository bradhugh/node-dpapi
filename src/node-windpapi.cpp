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

	// auto data = v8::Uint8Arrayinfo[0]->ToObject());
	auto buffer = node::Buffer::Data(info[0]);
	auto len = node::Buffer::Length(info[0]);
	
	DATA_BLOB dataIn;
	DATA_BLOB dataOut;

	// initialize input data
	dataIn.pbData = reinterpret_cast<BYTE*>(buffer);
	dataIn.cbData = len;

	bool success = CryptProtectData(
		&dataIn,
		L"Description string?",
		nullptr, // TODO: entropy
		nullptr, // reserved
		nullptr, // pass null for the prompt structure
		0, // dwFlags
		&dataOut);

	if (!success)
	{
		DWORD errorCode = GetLastError();
		isolate->ThrowException(v8::Exception::Error(
			v8::String::NewFromUtf8(isolate, "Decryption failed. TODO: Error code")));

		return;
	}
	
	info.GetReturnValue().Set(static_cast<int>(dataOut.cbData));
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