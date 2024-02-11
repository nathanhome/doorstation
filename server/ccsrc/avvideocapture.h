/*****
 * Implementation of a stream recording from a video source
 * e.g. camera. The source is expected to deliver ready encoded packets and frames.
 * In case of a raspberry cam, this is an h264 stream (with clock based timestamps)
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 * @author brederle <rbe.git@magenta.de>
 */
#pragma once

struct AVFormatContext;

namespace avstreams {

class AvVideoCapture : public Napi::ObjectWrap<AvVideoCapture> {
    public:
        static Napi::Object DeclareClass(Napi::Env env, Napi::Object exports);

        AvVideoCapture(const Napi::CallbackInfo& params);
        Napi::Value open(const Napi::CallbackInfo& params);
        Napi::Value close(const Napi::CallbackInfo& params);
        Napi::Value readFrame(const Napi::CallbackInfo& params);

    private:
        AVFormatContext* _context;
};

}
