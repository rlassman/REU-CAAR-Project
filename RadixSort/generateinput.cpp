#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <parlay/parallel.h>
#include <parlay/primitives.h>

int main() {
    
    size_t n = 100'000'000;

    parlay::sequence<int> nums(n);
    parlay::parallel_for(0, n, [&](size_t i) {
        std::mt19937 rng(i); // different seed per thread
        std::uniform_int_distribution<int> dist(0, 99999);
        nums[i] = dist(rng);
    });

    // Write to file serially
    std::ofstream outputFile("output.txt");
    outputFile << "sequenceInt\n";
    for (size_t i = 0; i < n; ++i) {
        outputFile << nums[i] << '\n';
    }
    outputFile.close();
    
    /*srand(time(0));
    int randNum;
    std::ofstream outputFile("input100m.txt");

    outputFile << "sequenceInt\n";

    for(int i = 0; i < 100'000'000; ++i) {
        randNum = rand() % 1000000;
        outputFile << randNum << std::endl;
    }
    outputFile.close();*/
}



