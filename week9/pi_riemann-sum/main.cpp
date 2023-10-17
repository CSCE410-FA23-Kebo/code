/*
Computing pi as a Riemann sum using threads.
*/

#include "main.h"

int main()
{
    int nthreads = NUM_THREADS;
    double pi = 0.0, sum[NUM_THREADS][PAD];
    double start1, end1, start2, end2;

    step = 1.0 / (double)num_steps;

    // ##### START OF SECTION 1 #####
    start1 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    // create a vector of n threads
    vector<thread> threads1;

    // create n threads and add them to a vector of threads
    for (int i = 0; i < nthreads; i++)
    {
        threads1.push_back(thread(single_sum_thread, i, nthreads, sum));
    }

    // join the threads with the main thread
    for (int i = 0; i < nthreads; i++)
    {
        threads1[i].join();
    }
    end1 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    // ##### END OF SECTION 1 #####

    // ##### START OF SECTION 2 #####
    start2 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();

    // create a vector of n threads
    vector<thread> threads2;

    // create n threads and add them to a vector of threads
    for (int i = 0; i < nthreads; i++)
    {
        threads2.push_back(thread(pi_sum_thread, i, step, &pi, sum));
    }

    // join the threads with the main thread
    for (int i = 0; i < nthreads; i++)
    {
        threads2[i].join();
    }

    end2 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    // ##### END OF SECTION 2 #####
    
    printf("Number of threads: %i\nCache padding for coherency: %i bytes\n---\n", nthreads, PAD * 8);
    printf("Pi approximation: %f\nTime to complete part 1: %f seconds\nTime to complete part 2: %f seconds\n", pi, (end1 - start1) * 1e-9, (end2 - start2) * 1e-9);
    return 0;
}