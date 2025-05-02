#include "filePathManager.hpp"
#include "timeBuffer.hpp"
#include "timeFinder.hpp"
#include "netcdfReader.hpp"
#include "field.hpp"
#include "netcdfField.hpp"

#include <iostream>
#include <memory>
#include <vector>

using FieldPtr = std::shared_ptr<Field>;

template <typename T> class FieldTimeBuffer : public TimeBuffer<FieldPtr> {
public:
  explicit FieldTimeBuffer(size_t num_files = 3)
      : TimeBuffer<FieldPtr>(num_files) {}

protected:
  FieldPtr load(const TimeKey &k) override {
    return std::make_shared<NetCDFField<T>>(k.file, k.var, k.time);
  }
};


int main(int argc, char **argv) {
  FilePathManager files("test_data/data");
  const size_t STEPS_PER_FILE =
      2;

  TimeFinder tf(files, STEPS_PER_FILE);
  FieldTimeBuffer<float> tb(
      3);

  size_t t = 0;
  size_t num_files = 3;

  while (t < num_files * STEPS_PER_FILE) {
    auto [path, local_t] = tf.find_local(t);
    auto field = tb.get(path, "test_value", local_t);

    // Note: Field is just an example class. Any class can be used with the loader and/or buffer
    auto data = field->data();
    float v = *reinterpret_cast<float *>(data) +
              field->index(0, 0, 0) * sizeof(float);
    std::cout << "T(" << t << ") = " << v << std::endl;

    t++;
  }

  return 0;
}
