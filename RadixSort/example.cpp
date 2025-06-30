#include <chrono>
#include <cstdlib>
#include <random>
#include <fstream>
#include "sequenceIO.h"
#include "parseCommandLine.h"
#include "radixSort.h"
#include "ska_sort.hpp"

using namespace std;
using namespace benchIO;

typedef std::chrono::high_resolution_clock high_res_clock;

typedef pair<uintT,uintT> uintTPair;

template <class F>
void check_sorted(uintT*  array, long length, F f) {
  uintT prev = array[0];
  parallel_for (1, length, [&](size_t i) {
    if(array[i] < array[i-1]) {
      printf("FAIL: ARRAY NOT SORTED!\n");
      exit(0);
    }
  });
  printf("array is sorted!\n");
}

template <class T, class F>
void check_sorted_pairs(pair<uintT,T>* array, long length, F f) {
  bool sorted = true;
  long stability_error = 0;
  parallel_for (1, length, [&](size_t i) {
    if(f(array[i]) < f(array[i-1])) {
      sorted = false;
    }

  });
  if(!sorted){
    printf("FAIL: ARRAY NOT SORTED!\n");
  } else {
    printf("array is sorted!\n");
  }
}


int main(int argc, char **argv) {
  commandLine P(argc,argv,"[-r <rounds>] [-c] [-n <length>] [-s <seed>]");
  //char* iFile = P.getArgument(0);
  int rounds = P.getOptionIntValue("-r",3);
  bool check = P.getOption("-c");
  int length = P.getOptionIntValue("-n", 10000);
  int sd = P.getOptionIntValue("-s", 42);
  //add param for # of threads later

  //seqData D = readSequenceFromFile(iFile);
  //elementType dt = D.dt;
  //long length = D.n;

  //if(dt){ //data type is ints
    uintT* array = new uintT[length];
    uintT* control_array = new uintT[length];
    double avgTime = 0;
    int low = 0, high = 1000;

    parallel_for(0, length, [&](size_t i) {
      std::mt19937_64 rng(sd + i);
      std::uniform_int_distribution<uintT> dist(low, high);
      control_array[i] = dist(rng);
    });
    
    for(long round=0;round<rounds;round++) {
      parallel_for(0, length, [&](size_t i) {array[i] = control_array[i];});
      auto start = high_res_clock::now();
      parallelIntegerSort(array, length, utils::identityF<uintT>());
      auto end = high_res_clock::now();
      std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
      std::cout << "radix sort time: " << diff.count() << " ms" << std::endl;
      avgTime += diff.count();
    }

    std::cout << "average sort time: " << avgTime/3 << std::endl;
  
    if(check) {
      check_sorted(array,length, utils::identityF<uintT>());
    }
    delete[] array; 
    free(control_array);
  /*} else if (dt == intPairT) { //data type is pairs
    uintTPair* array = (uintTPair*) D.A;

    uintTPair* control_array = newA(uintTPair,length);
    parallel_for(0, length, [&](size_t i) {control_array[i] = array[i];});

    for(long round=0;round<rounds;round++){
      parallel_for(0, length, [&](size_t i) {array[i] = control_array[i];});
      auto start = high_res_clock::now();
      parallelIntegerSort(array, length, utils::firstF<uintT,uintT>());
      auto end = high_res_clock::now();
      std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
      std::cout << "radix sort time: " << diff.count() << " ms" << std::endl;
    }
    
    if(check) {
      check_sorted_pairs(array,length, utils::firstF<uintT,uintT>());
    }
    ;
    delete[] array; 
    free(control_array);
  } else if (dt == intStringPairT) {
    cout << "to implement" << endl;
  } else {
    cout << "input file not of right type" << endl;
  }*/

  return 0;
}

