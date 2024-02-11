#include <napi.h>

#include "avvideoframe.h"
#include "avvideocapturestream.h"

Napi::Object InitModule(Napi::Env env, Napi::Object exports) {
    avstreams::AvVideoFrame::DeclareClass(env, exports);
    avstreams::AvVideoCaptureStream::DeclareClass(env, exports);
    return exports;
}

NODE_API_MODULE(libavstreams, InitModule)