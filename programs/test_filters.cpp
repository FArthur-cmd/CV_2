#include "../include/Utils/process_input.h"
#include "../include/Utils/test_filter.h"

#include <fstream>

int main(int argc, char **argv) {
  cv::Mat image;
  extract_image_from_input(argc, argv, image);
  MedianFilter::IMedianFilter *filter = extract_filter_from_input(argc, argv);
  const size_t number_of_tests = extract_number_of_tests_from_input(argc, argv);
  std::string results_file = extract_path_to_save_result(argc, argv);
  auto results = test_filter_speed(filter, image, number_of_tests);

  std::ofstream out;
  out.open(results_file);
  if (out.is_open()) {
    for (auto result : results) {
      out << result << "\n";
    }
  } else {
    std::cout << "Can't save data to file " << results_file << std::endl;
  }

  delete filter;
  return 0;
}