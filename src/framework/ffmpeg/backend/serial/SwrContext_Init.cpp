#include <cpptools/framework/ffmpeg/backend/serial/SwrContext_Init.h>
#include <iostream>

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
        int out_sample_rate ,
        AVSampleFormat out_fmt ,
        int out_channels 
    ) {
        AVChannelLayout out_layout;
        av_channel_layout_default(&out_layout, out_channels);

        int ret = swr_alloc_set_opts2(
            &swrCtx,
            &out_layout,
            out_fmt,
            out_sample_rate,
            &codecCtx->ch_layout,
            codecCtx->sample_fmt,
            codecCtx->sample_rate,
            0,
            nullptr
        );

        av_channel_layout_uninit(&out_layout);

        if (ret < 0) {
            std::cerr << "swr_alloc_set_opts2 failed\n";
            return false;
        }

        if (swr_init(swrCtx) < 0) {
            std::cerr << "swr_init failed\n";
            swr_free(&swrCtx);
            return false;
        }

        return true;
    }

}