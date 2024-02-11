/*****
 * Wrapper for AVFrame adapting it to the WebRTC video frame structure
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * @author brederle <rbe.git
 */
#pragma once

#include <napi.h>

struct AVFrame;

namespace avstreams {

class AvVideoFrame : public Napi::ObjectWrap<ClassExample> {

public:
  // this is where the meta ("reflection") info for the class is defined
  static Napi::Object DeclareClass(Napi::Env env, Napi::Object exports);
  AvVideoFrame(const Napi::CallbackInfo& info, AVFRame* frame);

 private:
  static Napi::FunctionReference constructor; 
  // wrapped functions
  Napi::Value width(const Napi::CallbackInfo& params);
  Napi::Value height(const Napi::CallbackInfo& params);
  Napi::Value rotation(const Napi::CallbackInfo& params);
  Napi::Value video_frame_buffer(const Napi::CallbackInfo& params);
  // the actual libav structure
  AVFrame* _avframe;
};

} // namespace avstream

