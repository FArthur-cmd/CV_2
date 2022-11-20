#include "HuangMedianFilter.h"

namespace MedianFilter {

cv::Mat HuangMedianFilter::process_image(const cv::Mat &matrix) {
  cv::Mat result = matrix.clone();
  int64_t height = matrix.rows;
  int64_t width = matrix.cols;

  Utils::RGB *result_data = reinterpret_cast<Utils::RGB *>(result.data);
  Utils::RGB *matrix_data = reinterpret_cast<Utils::RGB *>(matrix.data);

  /// Init window
  Utils::Window moving_window(matrix_data, -shift_, -shift_, width, height,
                              window_size_);
  bool current_direction_is_right = true;

  /// y - current row
  /// first_border and second_border are used to avoid additional calculation of
  /// borders. When window moves iteration is made only by one coordinate. Fixed
  /// coordinate will be written into border variable.
  int64_t y, first_border, second_border;

  for (int64_t x = 0; x < height; ++x) {
    if (current_direction_is_right) {
      for (y = 0; y < width; ++y) {
        result_data[x * width + y] = moving_window.find_median();

        /// move window horizontaly
        if (y < width - 1) {
          first_border = y - shift_;
          second_border = y + window_sub_shift_;

          for (int64_t k = -shift_; k < window_sub_shift_; ++k) {
            moving_window.remove_pixel(x + k, first_border);
            moving_window.add_pixel(x + k, second_border);
          }
        }
      }
    } else {
      for (y = width - 1; y >= 0; --y) {
        result_data[x * width + y] = moving_window.find_median();

        /// move window horizontaly
        if (y > 0) {
          first_border = y - window_sub_shift_;
          second_border = y + shift_;
          for (int64_t k = -shift_; k < window_sub_shift_; ++k) {
            moving_window.add_pixel(x + k, first_border);
            moving_window.remove_pixel(x + k, second_border);
          }
        }
      }
    }

    current_direction_is_right ? --y : ++y;
    current_direction_is_right = !current_direction_is_right;

    /// move window down
    if (x < height - 1) {
      first_border = x + window_sub_shift_;
      second_border = x - shift_;
      for (int64_t k = -shift_; k < window_sub_shift_; ++k) {
        moving_window.add_pixel(first_border, y + k);
        moving_window.remove_pixel(second_border, y + k);
      }
    }
  }

  return result;
}

} // namespace MedianFilter
