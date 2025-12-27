
#include <cpptools/framework/ffmpeg/backend/serial/FormatContext_init.h>
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

	bool FormatContext_init(AVFormatContext*& fmtCtx, const char* path) {
		// 如果之前有内容就先释放
		if (fmtCtx) {
			avformat_close_input(&fmtCtx);
			fmtCtx = nullptr;
		}

		// 读取文件的来源和类型
		if (avformat_open_input(&fmtCtx, path, nullptr, nullptr) < 0) {
			std::cout << "Failed to open file\n"; return false;
		}

		// 读取全部流的信息
		if (avformat_find_stream_info(fmtCtx, nullptr) < 0) {
			std::cout << "Failed to find stream info\n"; return false;
		}
		return true;
	}

}