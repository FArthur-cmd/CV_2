#include "utils.h"
#include <cassert>
#include <ctime>

namespace Utils {

///============================HistSctructure=================================

void HistSctructure::add_value(uint8_t value) { ++hist_[value]; }

void HistSctructure::remove_value(uint8_t value) {
  --hist_[value];
  assert(hist_[value] >= 0);
}

uint8_t HistSctructure::get_median() {
  /// simple find of median. Complexity O(N) where N = 256 - max value for
  /// colour
  current_median = 0;
  int32_t less_than_median = 0;
  while (hist_[current_median] == 0 || less_than_median < median_count_) {
    less_than_median += hist_[current_median];
    ++current_median;
  }

  return current_median;
}

HistSctructure &HistSctructure::operator+=(const HistSctructure &other) {
  assert(size_ == other.size_);
  for (uint16_t i = 0; i < size_; ++i) {
    if (other.hist_[i] != 0) {
      hist_[i] += other.hist_[i];
    }
  }
  return *this;
}

HistSctructure &HistSctructure::operator-=(const HistSctructure &other) {
  assert(size_ == other.size_);
  for (uint16_t i = 0; i < size_; ++i) {
    if (other.hist_[i] != 0) {
      hist_[i] -= other.hist_[i];
      assert(hist_[i] >= 0);
    }
  }
  return *this;
}

///===============================Column========================================

Column::Column(Utils::RGB *image, int64_t start_row, int64_t column,
               int64_t width, int64_t height, int64_t diam)
    : red_(diam), green_(diam), blue_(diam), width_(width), height_(height),
      diam_(diam), column_(std::min(std::max(column, 0ll), width_ - 1)),
      current_row_(start_row), image_(image) {
  for (int64_t row = current_row_; row < current_row_ + diam_; ++row) {
    add_pixel(row);
  }
}

void Column::add_pixel(int64_t row_number) {
  /// to avoid errors with padding
  int64_t clip_row = std::min(std::max(row_number, 0ll), height_ - 1);
  int64_t pos = clip_row * width_ + column_;
  red_.add_value(image_[pos].get_colour(Colours::RED));
  green_.add_value(image_[pos].get_colour(Colours::GREEN));
  blue_.add_value(image_[pos].get_colour(Colours::BLUE));
}

void Column::remove_pixel(int64_t row_number) {
  /// to avoid errors with padding
  int64_t clip_row = std::min(std::max(row_number, 0ll), height_ - 1);
  int64_t pos = clip_row * width_ + column_;
  red_.remove_value(image_[pos].get_colour(Colours::RED));
  green_.remove_value(image_[pos].get_colour(Colours::GREEN));
  blue_.remove_value(image_[pos].get_colour(Colours::BLUE));
}

///===============================Window========================================

Window::Window(Utils::RGB *image, int64_t width, int64_t height,
               int64_t window_edge)
    : diam_(window_edge), red_(diam_ * diam_), green_(diam_ * diam_),
      blue_(diam_ * diam_), width_(width), height_(height), image_(image) {}

Window::Window(Utils::RGB *image, int64_t start_row, int64_t start_column,
               int64_t width, int64_t height, int64_t window_edge)
    : diam_(window_edge), red_(diam_ * diam_), green_(diam_ * diam_),
      blue_(diam_ * diam_), width_(width), height_(height), image_(image) {
  for (int64_t col = start_column; col < start_column + diam_; ++col) {
    for (int64_t row = start_row; row < start_row + diam_; ++row) {
      add_pixel(col, row);
    }
  }
}

void Window::add_pixel(int64_t x, int64_t y) {
  /// to avoid errors with padding
  int64_t clip_row = std::min(std::max(x, 0ll), height_ - 1);
  int64_t clip_col = std::min(std::max(y, 0ll), width_ - 1);
  int64_t pos = clip_row * width_ + clip_col;
  red_.add_value(image_[pos].get_colour(Colours::RED));
  green_.add_value(image_[pos].get_colour(Colours::GREEN));
  blue_.add_value(image_[pos].get_colour(Colours::BLUE));
}

void Window::remove_pixel(int64_t x, int64_t y) {
  /// to avoid errors with padding
  int64_t clip_row = std::min(std::max(x, 0ll), height_ - 1);
  int64_t clip_col = std::min(std::max(y, 0ll), width_ - 1);
  int64_t pos = clip_row * width_ + clip_col;
  red_.remove_value(image_[pos].get_colour(Colours::RED));
  green_.remove_value(image_[pos].get_colour(Colours::GREEN));
  blue_.remove_value(image_[pos].get_colour(Colours::BLUE));
}

Window &Window::operator+=(const Column &column) {
  red_ += column.get_red();
  green_ += column.get_green();
  blue_ += column.get_blue();
  return *this;
}

Window &Window::operator-=(const Column &column) {
  red_ -= column.get_red();
  green_ -= column.get_green();
  blue_ -= column.get_blue();
  return *this;
}

} // namespace Utils
