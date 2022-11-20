#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../Filters/ConstantTimeMedianFilter.h"
#include "../Filters/HuangMedianFilter.h"
#include "../Filters/SortMedianFilter.h"

/// Extract image from input. Path to image is first argument.
/// Image will be read from file to image matrix.
bool extract_image_from_input(int argc, char **argv, cv::Mat &image) {
  if (argc < 2) {
    std::cout << "Program received not enough arguments. First argument should "
                 "be path to picture.\n"
              << std::endl;
    return false;
  }
  image = cv::imread(argv[1], cv::IMREAD_COLOR);
  if (image.empty()) {
    std::cout << "Something went wrong during reading the image. No image data "
                 "was found."
              << std::endl;
    return false;
  }
  return true;
}

/// Second argument for program is kind of algorithm.
/// Third argument is size of window.
MedianFilter::IMedianFilter *extract_filter_from_input(int argc, char **argv) {
  if (argc < 4) {
    std::cout
        << "Program received not enough arguments. Second argument "
           "should be filter type and fourth argument should be window size.\n"
        << std::endl;
    return nullptr;
  }

  int64_t window_size = strtoll(argv[3], nullptr, 10);
  if (strcmp(argv[2], "Sort") == 0) {
    std::cout << "Chosen filter is Sort with window size " << window_size
              << std::endl;
    return reinterpret_cast<MedianFilter::IMedianFilter *>(
        new MedianFilter::SortMedianFilter(window_size));
  }

  if (strcmp(argv[2], "Huang") == 0) {
    std::cout << "Chosen filter is Huang " << std::endl;
    return reinterpret_cast<MedianFilter::IMedianFilter *>(
        new MedianFilter::HuangMedianFilter(window_size));
  }

  if (strcmp(argv[2], "Const") == 0) {
    std::cout << "Chosen filter is Const " << std::endl;
    return reinterpret_cast<MedianFilter::IMedianFilter *>(
        new MedianFilter::ConstTimeMedianFilter(window_size));
  }

  std::cout
      << "Unknown filter type. Expected one of: Sort, Const, Huang. Received: "
      << argv[2] << std::endl;
  return nullptr;
}

/// Fourth argument is number of test (only in test_filter)
size_t extract_number_of_tests_from_input(int argc, char **argv) {
  if (argc < 5) {
    std::cout
        << "Program received not enough arguments. Fourth argument should "
           "be number of tests.\n"
        << std::endl;
    return 0; /// Won't run any tests
  }
  return strtoull(argv[4], nullptr, 10);
}

/// Last argument is path to save result (blur image or time for each test)
std::string extract_path_to_save_result(int argc, char **argv) {
  return std::string(argv[argc - 1]);
}
