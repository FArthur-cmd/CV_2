#pragma once
#include "IMedianFilter.h"

namespace MedianFilter {

/**
 * Create a window that will slide over the picture. Unlike the original
 * implementation, the window will move in zigzags (this avoids unnecessary
 * creation of matrices when moving to a new line)
 */
class HuangMedianFilter : public IMedianFilter {
public:
  HuangMedianFilter()
      : window_size_(1), shift_(window_size_ / 2),
        window_sub_shift_(window_size_ - shift_) {}
  explicit HuangMedianFilter(int64_t window_size)
      : window_size_(window_size), shift_(window_size_ / 2),
        window_sub_shift_(window_size - shift_) {}

  virtual cv::Mat process_image(const cv::Mat &matrix) override final;

  ~HuangMedianFilter() = default;

private:
  int64_t window_size_;

  /// count of elements to the left or above
  int64_t shift_;
  /// count of elements to the right or below
  int64_t window_sub_shift_;
};

} // namespace MedianFilter
