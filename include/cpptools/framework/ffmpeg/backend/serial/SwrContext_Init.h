#pragma once


extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libavutil/avutil.h>
#include <libavutil/opt.h>
#include <libavutil/channel_layout.h>
#include <libavutil/samplefmt.h>
}

namespace cpptools::framework::ffmpeg::backend::serial {


	bool SwrContext_Init(
		SwrContext*& swrCtx,
		const AVCodecContext* codecCtx,
		int out_sample_rate = 44100,
		AVSampleFormat out_fmt = AV_SAMPLE_FMT_S16,
		int out_channels = 2);


}