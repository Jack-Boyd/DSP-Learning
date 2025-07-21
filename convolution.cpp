#include <iostream>
#include <vector>

template <typename T>
std::vector<T> convolve(const std::vector<T> &x, const std::vector<T> &h) {
  int output_size = x.size() + h.size() - 1;
  std::vector<T> y(output_size, static_cast<T>(0));

  for (int n = 0; n < output_size; ++n) {
    for (int k = 0; k < h.size(); ++k) {
      int i = n - k;
      if (i >= 0 && i < x.size()) {
        y[n] += x[i] * h[k];
      }
    }
  }
  return y;
}

int main() {
  std::vector<int> x = {1, 2, -1, 2, 1, 0, 1, 1};
  std::vector<int> h = {2, -2, -1};

  auto result = convolve(x, h);

  for (const auto& value : result) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  std::vector<double> xd = {1.0, 2.0, -1.0, 2.0};
  std::vector<double> hd = {0.5, -0.5};

  auto result_d = convolve(xd, hd);

  for (const auto& value : result_d) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}