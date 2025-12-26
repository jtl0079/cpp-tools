find_package(ffmpeg CONFIG REQUIRED)

# 🔑 关键：传播依赖
target_link_libraries(cpptools
  PUBLIC
    ffmpeg::ffmpeg
)