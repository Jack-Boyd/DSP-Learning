#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

constexpr double PI = 3.14159265358979323846;

void print(const std::string& name, const std::vector<double>& vector) {
  std::cout << name << " = [";
  for (size_t i = 0; i < vector.size(); ++i) {
    std::cout << std::fixed << std::setprecision(4) << vector[i];
    if (i < vector.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

//Synthesis equation for real DFT as of Chpt 8 of Scientisst and Engineers guide to DSP
void inverse_dft(
  std::vector<double> &x, 
  const std::vector<double> &re_x, 
  const std::vector<double> &im_x) {
  size_t N = (re_x.size() - 1) * 2;
  x.assign(N, 0.0);

  std::vector<double> re_x_amps(N / 2 + 1);
  std::vector<double> im_x_amps(N / 2 + 1);

  double N_half = static_cast<double>(N) / 2.0;

  for (size_t k = 0; k <= N / 2; ++k) {
    re_x_amps[k] = re_x[k] / N_half;
    im_x_amps[k] = -im_x[k] / N_half;
  }
 
  re_x_amps[0] /= 2.0;
  if (N % 2 == 0) {
    re_x_amps[N / 2] /= 2.0;
  }

  for (size_t k = 0; k <= N / 2; ++k) {
    for (size_t i = 0; i < N; ++i) {
      double angle = 2.0 * PI * static_cast<double>(k * i) / static_cast<double>(N);
      x[i] += re_x_amps[k] * std::cos(angle);
      x[i] += im_x_amps[k] * std::sin(angle);
    }
  }
}

//DFT for just the real component as per Chpt 8 of Scientisst and Engineers guide to DSP
void dft(
  const std::vector<double> &signal, 
  std::vector<double> &re_x, 
  std::vector<double> &im_x) {
  size_t N = signal.size();

  re_x.assign(N / 2 + 1, 0.0);
  im_x.assign(N / 2 + 1, 0.0);

  for (size_t k = 0; k <= N / 2; ++k) {
    for (size_t i = 0; i < N; ++i) {
      double angle = 2.0 * PI * static_cast<double>(k * i) / static_cast<double>(N);
      re_x[k] += signal[i] * std::cos(angle);
      im_x[k] -= signal[i] * std::sin(angle);
    }
  }
}

int main() {
  const int N = 64;
  std::vector<double> input_signal(N);
  double frequency = 1.0;
  double amplitude = 2.4;

  for (int i = 0; i < N; ++i) {
    input_signal[i] = amplitude * std::cos(2.0 * PI * frequency * static_cast<double>(i) / static_cast<double>(N));
  }
  print("Input Signal", input_signal);
  std::cout << '\n';

  std::vector<double> re_x(N / 2 + 1);
  std::vector<double> im_x(N / 2 + 1);

  dft(input_signal, re_x, im_x);

  print("Re_X", re_x);
  print("Im_X", im_x);
  std::cout << '\n';

  std::vector<double> synthesized_input_signal;
  inverse_dft(synthesized_input_signal, re_x, im_x);

  std::cout << "Synthesized" << std::endl;
  print("Input Signal", synthesized_input_signal);
  std::cout << '\n';

  double total_error = 0.0;
  for (size_t i = 0; i < N; ++i) {
    total_error += std::abs(input_signal[i] - synthesized_input_signal[i]);
  }
  std::cout << "Total Error: " << total_error << std::endl;


  return 0;
}