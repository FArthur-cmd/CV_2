#include "../include/Utils/process_input.h"

int main(int argc, char **argv) {
  /// Process input by extracting from input image,
  /// filter and path to save results
  cv::Mat image;
  extract_image_from_input(argc, argv, image);
  MedianFilter::IMedianFilter *filter = extract_filter_from_input(argc, argv);
  std::string path_to_save = extract_path_to_save_result(argc, argv);

  /// Apply filter and save result
  cv::Mat result = filter->process_image(image);
  if (!cv::imwrite(path_to_save, result)) {
    std::cout << "Can't write to " << path_to_save << std::endl;
  }

  delete filter;
  return 0;
}