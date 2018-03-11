#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C"
{
void __cyg_profile_func_enter(void *this_fn, void *call_site) __attribute__((no_instrument_function));
void __cyg_profile_func_exit(void *this_fn, void *call_site) __attribute__((no_instrument_function));
unsigned long long get_curr_ms() __attribute__((no_instrument_function));
}
#endif

static FILE *fp;
extern int errno;

unsigned long long get_curr_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    unsigned long long timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void __cyg_profile_func_enter(void *this_fn, void *call_site)
{
    if (fp == NULL)
    {
        fprintf(stderr, "%s", "create trace file.\n");
        fp = fopen( "trace.out", "w" );
    }
    if (fp == NULL)
    {
        fprintf(stderr, "%s", strerror(errno));
        exit(-1);
    }

    unsigned long long timestamp = get_curr_ms();

    void* addrs[1];
    char** results;
    addrs[0] = this_fn;
    // translate address to symbols
    results = backtrace_symbols(addrs, 1);
    fprintf(fp, "e -->> %s -->> %llu\n", results[0], timestamp);
    // free results
    free(results);
}

void __cyg_profile_func_exit(void *this_fn, void *call_site)
{
    unsigned long long timestamp = get_curr_ms();
    void* addrs[1];
    char** results;
    addrs[0] = this_fn;
    // translate address to symbols
    results = backtrace_symbols(addrs, 1);
    fprintf(fp, "x -->> %s -->> %llu\n", results[0], timestamp);
    // free results
    free(results);
}
