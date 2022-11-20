#pragma once
#include "../../contrib/pdqsort/pdqsort.h"
#include "IMedianFilter.h"

namespace MedianFilter {

/**
 * Create window and sort all values in it.
 * Middle value in sorted array is median.
 */
class SortMedianFilter : public IMedianFilter {
public:
  SortMedianFilter()
      : IMedianFilter(0), window_size_(0),
        window_2d_(window_size_ * window_size_),
        median_pos(window_2d_ / 2 + window_2d_ % 2), shift(window_size_ / 2){};
  explicit SortMedianFilter(int64_t size)
      : IMedianFilter(size), window_size_(size),
        window_2d_(window_size_ * window_size_),
        median_pos(window_2d_ / 2 + window_2d_ % 2) {}

  /// For each element process image and save to result
  virtual cv::Mat process_image(const cv::Mat &matrix) override final;

  virtual ~SortMedianFilter() = default;

protected:
  /// create window, sort and return result
  Utils::RGB process_window(Utils::RGB *image, int64_t start_x, int64_t start_y,
                            int64_t width, int64_t height);

private:
  /// Len of edge
  int64_t window_size_;

  /// Window aread
  int64_t window_2d_;
  int64_t median_pos;

  /// Padding len
  int64_t shift;
};

} // namespace MedianFilter