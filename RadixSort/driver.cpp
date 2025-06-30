#include "generator.h"

int main() {
  /*auto in = generate_uniform(1000, 42);
  std::ofstream outputFile("i1-1b-1t.txt");
    outputFile << "sequenceInt\n";
    for (size_t i = 0; i < n; ++i) {
        outputFile << in[i] << '\n';
    }
    outputFile.close();

  auto in2 = generate_uniform(100000, 41);
  std::ofstream outputFile2("i2-1b-100t.txt");
    outputFile2 << "sequenceInt\n";
    for (size_t i = 0; i < n; ++i) {
        outputFile2 << in2[i] << '\n';
    }
    outputFile2.close();*/

  auto in3 = generate_uniform(100000, 40);
  std::ofstream outputFile3("i3-1b-100t.txt");
    outputFile3 << "sequenceInt\n";
    for (size_t i = 0; i < n; ++i) {
        outputFile3 << in3[i] << '\n';
    }
    outputFile3.close();

    return 0;
}