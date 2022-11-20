#pragma once
#include "../Utils/utils.h"
#include <opencv2/opencv.hpp>

namespace MedianFilter {

/// Abstract class for easier work with different algorithms
class IMedianFilter {
public:
  IMedianFilter() : window_size_(0){};
  explicit IMedianFilter(int64_t window_size) : window_size_(window_size) {}

  /// According to documentation process image should return
  /// result after processing
  virtual cv::Mat process_image(const cv::Mat &matrix) = 0;

  virtual ~IMedianFilter() = default;

private:
  int64_t window_size_;
};

} // namespace MedianFilter
