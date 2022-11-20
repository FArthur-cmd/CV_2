#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>

#include "ConstantTimeMedianFilter.h"

namespace MedianFilter {

using Columns = std::vector<Utils::Column>;

cv::Mat ConstTimeMedianFilter::process_image(const cv::Mat &matrix) {
  cv::Mat result = matrix.clone();
  int64_t height = matrix.rows;
  int64_t width = matrix.cols;

  Utils::RGB *result_data = reinterpret_cast<Utils::RGB *>(result.data);
  Utils::RGB *matrix_data = reinterpret_cast<Utils::RGB *>(matrix.data);

  /// Init columns
  Columns columns_for_window;
  columns_for_window.reserve(width + window_size_);
  for (int64_t col = -shift_; col < width + window_sub_shift_; ++col) {
    columns_for_window.emplace_back(matrix_data, -shift_, col, width, height,
                                    window_size_);
  }

  /// Init window
  Utils::Window moving_window(matrix_data, width, height, window_size_);
  for (int64_t col = -shift_; col < window_sub_shift_; ++col) {
    moving_window += columns_for_window[col + shift_];
  }

  bool current_direction_is_right = true;
  int64_t y;

  for (int64_t x = 0; x < height; ++x) {
    if (current_direction_is_right) {
      for (y = 0; y < width; ++y) {
        result_data[x * width + y] = moving_window.find_median();

        /// move window right
        if (y < width - 1) {
          moving_window -= columns_for_window[y];
          moving_window += columns_for_window[y + window_size_];
        }
      }
    } else {
      for (y = width - 1; y >= 0; --y) {
        result_data[x * width + y] = moving_window.find_median();

        /// move window left
        if (y > 0) {
          moving_window -= columns_for_window[y + 2 * shift_];
          moving_window += columns_for_window[y + shift_ - window_sub_shift_];
        }
      }
    }

    current_direction_is_right ? --y : ++y;
    current_direction_is_right = !current_direction_is_right;

    /// move window down
    if (x < height - 1) {
      for (int64_t k = -shift_; k < window_sub_shift_; ++k) {
        moving_window.add_pixel(x + window_sub_shift_, y + k);
        moving_window.remove_pixel(x - shift_, y + k);
      }
    }

    /// move each column down by removing top element and adding bottom element
    for (int64_t col = 0; col < width + window_size_; ++col) {
      columns_for_window[col].add_pixel(x + window_sub_shift_);
    }
    for (int64_t col = 0; col < width + window_size_; ++col) {
      columns_for_window[col].remove_pixel(x - shift_);
    }
  }

  return result;
}

} // namespace MedianFilter
