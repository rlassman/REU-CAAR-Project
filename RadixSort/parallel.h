#ifndef _PARALLEL_H
#define _PARALLEL_H

#include<parlay/primitives.h>
#include<parlay/parallel.h>
#include <iostream>

#define parallel_main main
#define parallel_for(par_lo, par_hi, par_body) \
    parlay::parallel_for(par_lo, par_hi, par_body)
#define parallel_for_1(par_lo, par_hi, par_body) \
    parlay::parallel_for(par_lo, par_hi, par_body, 1)
#define parallel_for_256(par_lo, par_hi, par_body) \
    parlay::parallel_for(par_lo, par_hi, par_body, 256)
#define parallel_for_swap(par_lo, par_hi, par_body) \
    parlay::parallel_for(par_lo, par_hi, par_body, 4000)
#define parallel_for_extract(par_lo, par_hi, par_body) \
    parlay::parallel_for(par_lo, par_hi, par_body, 256)

static int getWorkers() {
  return parlay::num_workers();
}

static int getWorkerId() {
  return parlay::worker_id();
}

#include <limits.h>
//#define LONG
#if defined(LONG)
typedef long intT;
typedef unsigned long uintT;
#define INT_T_MAX LONG_MAX
#define UINT_T_MAX ULONG_MAX
#else
typedef int intT;
typedef unsigned int uintT;
#define INT_T_MAX INT_MAX
#define UINT_T_MAX UINT_MAX
#endif

#endif // _PARALLEL_H
