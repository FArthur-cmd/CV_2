#pragma once
#include "IMedianFilter.h"

namespace MedianFilter {

/**
 * Create a window that will slide over the picture. Unlike the original
 * implementation, the window will move in zigzags (this avoids unnecessary
 * creation of matrices when moving to a new line)
 *
 * Instead of adding pixels, columns are added. This columns always have actual
 * data, because they move down on each iteration. Because update fow all
 * columns happens at the same time it is more cache friendly
 */
class ConstTimeMedianFilter : public IMedianFilter {
public:
  ConstTimeMedianFilter()
      : window_size_(1), shift_(window_size_ / 2),
        window_sub_shift_(window_size_ - shift_) {}
  explicit ConstTimeMedianFilter(int64_t window_size)
      : window_size_(window_size), shift_(window_size_ / 2),
        window_sub_shift_(window_size - shift_) {}

  virtual cv::Mat process_image(const cv::Mat &matrix) override final;

private:
  int64_t window_size_;

  /// count of elements to the left or above
  int64_t shift_;
  /// count of elements to the right or below
  int64_t window_sub_shift_;
};

} // namespace MedianFilter
