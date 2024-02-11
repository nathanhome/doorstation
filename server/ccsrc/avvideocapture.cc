/*****
 * Implementation of a stream recording from a video source
 * e.g. camera. The source is expected to deliver ready encoded packets and frames.
 * In case of a raspberry cam, this is an h264 stream (with clock based timestamps)
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * @author brederle <rbe.git@magenta.de>
 */
#include "avvideoframe.h"

#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
#include <libavutil/time.h>

using namespace avstreams;


static Napi::Object AvVideoCapture::DeclareClass(Napi::Env env, Napi::Object exports) {
    Napi::Function classAvVideoCapture = DefineClass(env, "AvVideoCapture", {
        InstanceMethod("open", &AvVideoCapture::open;
        InstanceMethod("close", &AvVideoCapture::close;
        InstanceMethod("readFrame", &AvVideoCapture::readFrame);
    });
}


AvVideoCapture::AvVideoCapture(const Napi::CallbackInfo& params) : Napi::ObjectWrap<AvVideoCaptureStream>(info) {
    avdevice_register_all();

    this->_context = NULL;
    this->lastPacket = NULL;
}


Napi::Value AvVideoCapture::open(const Napi::CallbackInfo& params) {
    Napi::Env env = params.Env();

    AVFormatContext* input_format_context = NULL;
    this->_context = NULL;
    this->lastPacket = NULL;

    // method parameter extraction for
    // open(device, width, height, framerate=30, format='h264')
    int length = params.Length();
    if (length != 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }

    // Open video input device
    AVInputFormat *input_format = av_find_input_format("video4linux2");
    if (!input_format) {
        throw Napi::Error::New(env, 
            "Cannot find video4linux2 inout format. Does your installed ffmpeg support it?");
    }

    AVDictionary* options = NULL;
    av_dict_set(&options, "input_format", format, 0);
    av_dict_set(&options, "framerate", framerate, 0);
    av_dict_set(&options, "video_size", resolution, 0);

    if (avformat_open_input(&input_format_context, device, input_format, &options) != 0) {
        // TODO: nodejs N-API correct handling
        throw Napi::Error::New(env, "Cannot open the input device");
    }

    this->_context = input_format_context;
}

/**
 * according to the doc for the AVPacket class: For video, it should typically contain one compressed frame. 
 * For audio it may contain several compressed frames.
 * 
 */
Napi::Value AvVideoCapture::readFrame(const Napi::CallbackInfo& params) {
    AVPacket* packet = NULL;
    Napi::Env env = params.Env();

    if (this->_context == NULL) {
         throw Napi::Error::New(env, "You need to open the stream before reading it!");       
    }

    // no packet available; stop stream reading until the next round
    // by returning NULL frame
    if ( packet == NULL) {
        return env.NULL;
    }

    av_packet_unref(&packet);

    Napi::Number num = Napi::Number::New(env, this->currentValue++);

}

Napi::Value AvVideoCapture::close(const Napi::CallbackInfo& params) {
    Napi::Env env = params.Env();
 
    avformat_close_input(&this->_context);

}