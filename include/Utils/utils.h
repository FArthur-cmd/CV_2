#pragma once
#include <algorithm>
#include <inttypes.h>
#include <vector>

namespace Utils {

enum Colours { BLUE = 0, GREEN = 1, RED = 2 };

/**
 * struct of one pixel according to the documentation,
 * the channels are arranged in order: blue, green, red
 */
struct RGB {
  uint8_t blue;
  uint8_t green;
  uint8_t red;

  uint8_t get_colour(Colours colour) {
    return *(reinterpret_cast<uint8_t *>(this) + colour);
  }
};

///============================HistSctructure=================================

/**
 * some algorithms (e.g. Huang) require histogram to find median value
 * The number of colours is 256 (one byte per channel)
 */
class HistSctructure {
public:
  /**
   * Construct a new Hist Sctructure object
   *
   *  elements_count - max number of elements in histogram.
   * Helps avoid counting the number of elements in place. In our case this is a
   * good solution, because the window size in the algorithms is fixed before
   * construction.
   */
  explicit HistSctructure(int64_t elements_count)
      : hist_(size_, 0),
        median_count_(elements_count / 2 + elements_count % 2) {}

  /**
   * Simply add value into histogram (increase count of elements in hist[value])
   *
   *  value that was found in algorithm
   */
  void add_value(uint8_t value);

  /**
   * Derease count of elements in hist[value].
   * For additional
   *
   *  value that was removed from window
   */
  void remove_value(uint8_t value);

  /**
   * Get the median object
   *
   * @return uint8_t median value from histogram
   */
  uint8_t get_median();

  /**
   * for each element add count from other histogram
   */
  HistSctructure &operator+=(const HistSctructure &other);

  /**
   * for each element subtract count from other histogram
   */
  HistSctructure &operator-=(const HistSctructure &other);

private:
  const uint16_t size_ = 256;
  std::vector<int32_t> hist_;

  int32_t median_count_;
  uint8_t current_median;
};

///===============================Column========================================
/**
 * Column has three histograms (for each channel).
 * Can add pixel from column or remove element from this column
 */
class Column {
public:
  /**
   * Construct a new Column object
   * Fills hists from start_row to start_row + window_edge (diam)
   *
   *  image - source image
   *  start_row - from which line elements should be taken
   *  column - number of column from which elements will be taken
   *  width and  height - shape of image
   *  diam - window edge is diameter for column
   */
  Column(Utils::RGB *image, int64_t start_row, int64_t column, int64_t width,
         int64_t height, int64_t diam);

  /**
   * add pixel from histogram
   *
   *  row_number of element
   */
  void add_pixel(int64_t row_number);

  /**
   * remove pixel from histogram
   *
   *  row_number of element
   */
  void remove_pixel(int64_t row_number);

  /// Getters
  const HistSctructure &get_red() const { return red_; }
  const HistSctructure &get_green() const { return green_; }
  const HistSctructure &get_blue() const { return blue_; }

private:
  /// All histograms
  HistSctructure red_;
  HistSctructure green_;
  HistSctructure blue_;

  /// Image shape to extract data from image
  int64_t width_;
  int64_t height_;
  int64_t diam_;

  /// column number and index of its start
  int64_t column_;
  int64_t current_row_;

  /// source image
  Utils::RGB *image_;
};

///===============================Window========================================

/**
 * window working like counting sort
 * Creates histograms for each channel to find median for each colour
 */
class Window {
public:
  /**
   * Construct a new empty Window
   *
   *  image - source image
   *  width and  height - image params
   *  window_edge - len of window edge
   */
  Window(Utils::RGB *image, int64_t width, int64_t height, int64_t window_edge);

  /**
   * Construct a new Window object filled with elements
   *
   *  image - source image
   *  start_row and  start_column - left upper corner from which elements will
   * be put in histogram width and  height - image params window_edge - len of
   * window edge
   */
  Window(Utils::RGB *image, int64_t start_row, int64_t start_column,
         int64_t width, int64_t height, int64_t window_edge);

  /// add pixel to window
  void add_pixel(int64_t x, int64_t y);

  /// remove pixel from window
  void remove_pixel(int64_t x, int64_t y);

  /// add results from column (useful for constant version of algorithm)
  Window &operator+=(const Column &column);

  /// remove results from column (useful for constant version of algorithm)
  Window &operator-=(const Column &column);

  /// median value in window
  RGB find_median() {
    return {blue_.get_median(), green_.get_median(), red_.get_median()};
  }

private:
  int64_t diam_;
  HistSctructure red_;
  HistSctructure green_;
  HistSctructure blue_;

  int64_t width_;
  int64_t height_;
  Utils::RGB *image_;
};

} // namespace Utils
