/**
 * Copyright 2023 Angus.Fenying <i@fenying.net>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <napi.h>

Napi::Value ws_mask(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() != 3)
    {
        Napi::TypeError::New(env, "Incorrect number of arguments")
            .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    if (!info[0].IsBuffer() || !info[1].IsBuffer() || !info[2].IsNumber())
    {
        Napi::TypeError::New(env, "Incorrect type of arguments").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    auto aData = info[0].As<Napi::Buffer<char>>();
    auto aMaskKey = info[1].As<Napi::Buffer<char>>();
    auto iOffset = info[2].As<Napi::Number>().Int32Value();

    if (aMaskKey.Length() != 4)
    {
        Napi::TypeError::New(env, "Length of mask-key must be 4").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    auto len = aData.Length();

    char *pData = aData.Data();
    char *pMaskKey = aMaskKey.Data();

    for (size_t i = 0, o = iOffset; i < len; i++, o++)
    {
        pData[i] = pData[i] ^ pMaskKey[o & 3];
    }

    return info.Env().Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        Napi::String::New(env, "mask"),
        Napi::Function::New(env, ws_mask));
    return exports;
}

NODE_API_MODULE(ws_utils, Init)
