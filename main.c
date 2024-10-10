#include <stdio.h>
#include <omp.h>
#include <pthread.h>

int main()
{
    printf("Hello World\n");
    printf("Hello from process: %d\n", omp_get_thread_num());
}