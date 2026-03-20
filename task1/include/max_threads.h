//
// Created by nosokvkokose on 12.03.26. and kinda used AI to find the funcs
//

#ifndef MAX_THREADS_H
#define MAX_THREADS_H

#ifdef __linux__
#include <unistd.h>
#define MAX_THREADS sysconf(_SC_NPROCESSORS_ONLN)

#elif _WIN32
#include <windows.h>

static inline int get_max_threads_win() {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return (int)sysinfo.dwNumberOfProcessors;
}
#define MAX_THREADS get_max_threads_win()

#elif __APPLE__
#include <unistd.h>
#include <sys/sysctl.h>

#define MAX_THREADS sysconf(_SC_NPROCESSORS_ONLN)

#else

#define MAX_THREADS 12
#endif

#endif //MAX_THREADS_H
