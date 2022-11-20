#include "../include/Utils/process_input.h"
#include <iomanip>
#include <string>
#include <ctime>

int main(int argc, char **argv) {
  cv::Mat image;
  cv::Mat result;

  /// Get imput picture and path for output images
  /// results will save like "path_without_extention + window_size + extention"
  extract_image_from_input(argc, argv, image);
  std::string path_to_save = extract_path_to_save_result(argc, argv);

  /// split by '.' to find extention
  auto extention_index = path_to_save.rfind('.');
  if (extention_index == std::string::npos) {
    std::cout << "No extention" << std::endl;
    return -1;
  }
  std::string extention = path_to_save.substr(extention_index);
  path_to_save = path_to_save.substr(0, extention_index);
  std::string current_path;
  clock_t start, end;

  /// size should be odd according to documentation
  for (int window_size = 1; window_size < 100; window_size += 2) {
    current_path = path_to_save + std::to_string(window_size) + extention;
    start = clock();
    medianBlur(image, result, window_size);
    end = clock();
    std::cout << std::setprecision(8) << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
    if (!cv::imwrite(current_path, result)) {
      std::cout << "Can't write to " << current_path << std::endl;
    }
  }

  return 0;
}