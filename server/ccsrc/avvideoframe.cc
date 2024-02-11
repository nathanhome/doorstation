/*****
 * Wrapper for AVFrame adapting it to the WebRTC video frame structure
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * @author brederle <rbe.git
 */
#include "avvideoframe.h"

#include <avcodec.h>

using namespace avstreams;

Napi::FunctionReference ClassExample::constructor;

Napi::Object AvVideoFrame::DeclareClass(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "AvVideoFrame", {
    InstanceMethod("witdh", &AvVideoFrame::width),
    InstanceMethod("height", &AvVideoFrame::height)),
    InstanceMethod("rotation", &AvVideoFrame::rotation)),
    InstanceMethod("video_frame_buffer", &AvVideoFrame::video_frame_buffer))
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("AvVideoFrame", func);
  return exports;
}

AvVideoFrame::AvVideoFrame(const Napi::CallbackInfo& info, AVFrame* frame) : Napi::ObjectWrap<AvVideoFrame>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  Napi::Number value = info[0].As<Napi::Number>();
  this->_avframe = frame;
}

Napi::Value AvVideoFrame::width(const Napi::CallbackInfo&) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int num = this->_avframe
  return Napi::S::New(env, num);
}

Napi::Value AvVideoFrame::video_frame_buffer(const Napi::CallbackInfo&) {
    int plane = 0;
    AVBufferRef* buffer = av_frame_get_plane_buffer(this->_avframe, plane);
}
