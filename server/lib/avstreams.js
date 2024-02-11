const { Readable } = require("stream")
const { AvVideoFrame, AvVideoCapture } = require('../build/Release/libavstreams')
console.debug('Avstreams exports', nativeAvStreams)

class AvVideosCaptureStream extends Readable {
    constructor(options) {
        super(options);
        this.capture = new AvVideoCapture();
    }

    _read() {
        this.push(this.capture.readFrame());
    }
}

module.exports = {
    "AvVideoFrame": AvVideosFrame,
    "AvVideosCaptureStream", AvVideosCaptureStream
}