#pragma once
#include <ctime>
#include <iostream>
#include <vector>

#include "../Filters/IMedianFilter.h"

std::vector<double> test_filter_speed(MedianFilter::IMedianFilter *filter,
                                      const cv::Mat &image,
                                      size_t number_of_tests) {
  std::vector<double> times;
  times.reserve(number_of_tests);
  clock_t start, end;
  std::cout << "Starting " << number_of_tests << " tests" << std::endl;
  for (size_t test = 0; test < number_of_tests; ++test) {
    start = clock();
    filter->process_image(image);
    end = clock();
    times.push_back((double)(end - start) / CLOCKS_PER_SEC);
    if (test % 10 == 0) {
      std::cout << "Current test " << test << std::endl;
    }
  }
  return times;
}