#include <cpptools/framework/ffmpeg/backend/serial/CodecContext_init.h>
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

	bool CodecContext_init(AVCodecContext*& codecCtx, AVStream* stream, const AVCodec* codec) {
		// AVStream			数据源
		// AVCodec			解码器
		// AVCodecContext	解码工具间
		// 
		codecCtx = avcodec_alloc_context3(codec);

		if (!stream || !stream->codecpar || !codec) {
			std::cout << "Invalid arguments\n";
			return false;
		}

		if (!codecCtx) {
			std::cout << "Failed to allocate codec context\n";
			return false;
		}


		// 在工具间里放入需要的资料
		if (avcodec_parameters_to_context(codecCtx, stream->codecpar) < 0) {
			std::cout << "Failed to copy codec parameters to context \n"; return false;
		}

		// 在工具间里初始化解码实例
		if (avcodec_open2(codecCtx, codec, nullptr) < 0) {
			std::cout << "Failed to open decoder\n"; return false;
		}

		return true;
	}

}