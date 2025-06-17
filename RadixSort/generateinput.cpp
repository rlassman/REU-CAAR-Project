#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));
    int randNum;
    std::ofstream outputFile("input10m.txt");

    outputFile << "sequenceInt\n";

    for (int i = 0; i < 10000000; ++i) {
        randNum = rand() % 100000;
        outputFile << randNum << std::endl;
    }
    outputFile.close();
}



