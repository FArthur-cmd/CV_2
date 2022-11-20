#include "SortMedianFilter.h"
#include <vector>

namespace MedianFilter {

cv::Mat SortMedianFilter::process_image(const cv::Mat &matrix) {
  cv::Mat result = matrix.clone();
  int64_t height = matrix.rows;
  int64_t width = matrix.cols;

  Utils::RGB *result_data = reinterpret_cast<Utils::RGB *>(result.data);
  Utils::RGB *matrix_data = reinterpret_cast<Utils::RGB *>(matrix.data);

  for (int64_t x = 0; x < height; ++x) {
    for (int64_t y = 0; y < width; ++y) {
      result_data[x * width + y] =
          process_window(matrix_data, x - shift, y - shift, width, height);
    }
  }

  return result;
}

Utils::RGB SortMedianFilter::process_window(Utils::RGB *image, int64_t start_x,
                                            int64_t start_y, int64_t width,
                                            int64_t height) {
  Utils::RGB result;

  std::vector<uint8_t> red;
  std::vector<uint8_t> green;
  std::vector<uint8_t> blue;

  red.reserve(window_2d_);
  green.reserve(window_2d_);
  blue.reserve(window_2d_);

  int64_t x, y, pos;

  for (int64_t i = start_x; i < start_x + window_size_; ++i) {
    for (int64_t j = start_y; j < start_y + window_size_; ++j) {
      x = std::min(std::max(i, 0ll), height - 1);
      y = std::min(std::max(j, 0ll), width - 1);
      pos = width * x + y;
      red.push_back(image[pos].get_colour(Utils::Colours::RED));
      green.push_back(image[pos].get_colour(Utils::Colours::GREEN));
      blue.push_back(image[pos].get_colour(Utils::Colours::BLUE));
    }
  }

  pdqsort(red.begin(), red.end());
  pdqsort(green.begin(), green.end());
  pdqsort(blue.begin(), blue.end());

  result.red = red[median_pos];
  result.green = green[median_pos];
  result.blue = blue[median_pos];

  return result;
}

} // namespace MedianFilter
