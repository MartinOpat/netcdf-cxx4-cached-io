#include "filePathManager.hpp"
#include "timeBuffer.hpp"
#include "timeFinder.hpp"

#include <iostream>

int main() {
  FilePathManager files("test_data/data");
  const size_t STEPS_PER_FILE =
      2; // TODO: This should either go into the config or be autodetected

  TimeFinder tf(files, STEPS_PER_FILE);
  TimeBuffer<float> tb(3);

  size_t t = 0;         // global time
  size_t num_files = 3; // This is just for testing

  while (t < num_files * STEPS_PER_FILE) {
    auto [path, local_t] = tf.find_local(t);
    auto field = tb.get(path, "test_value", local_t);

    float v = field->at(0, 0, 0);
    std::cout << "T(" << t << ") = " << v << std::endl;

    t++;
  }

  return 0;
}