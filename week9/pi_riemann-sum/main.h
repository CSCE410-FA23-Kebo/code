/*
Approximate Pi using the Leibniz formula
*/

#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#define NUM_THREADS 1 // adjust this to change the number of threads

#define PAD 8 // prevent false sharing

static long long int num_steps = 1000000000;
double step;

// Mutex synchronization primitive
mutex mtx;

void single_sum_thread(int id, int num_threads, double sum[NUM_THREADS][PAD])
{
    double x;
    sum[id][0] = 0.0;
    for (long long int i = id; i < num_steps; i = i + num_threads)
    {
        x = (i + 0.5) * step;
        sum[id][0] += 4.0 / (1.0 + x * x);
    }
}

// This function must be thread safe
void pi_sum_thread(int id, double step, double *pi, double sum[NUM_THREADS][PAD])
{
    // add synchronization here
    mtx.lock();  // Acquire a mutex
    *pi += sum[id][0] * step;
    mtx.unlock(); // Release
    sleep(1); // simulate a long running task
}