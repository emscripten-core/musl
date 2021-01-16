#include <time.h>
#include "syscall.h"
#if __EMSCRIPTEN__
#include <errno.h>
#include <emscripten/threading.h>
#endif

int nanosleep(const struct timespec *req, struct timespec *rem)
{
#if __EMSCRIPTEN__
	if (!req || req->tv_nsec < 0 || req->tv_nsec > 999999999L || req->tv_sec < 0) {
		errno = EINVAL;
		return -1;
	}
	emscripten_thread_sleep(req->tv_sec * 1000.0 + req->tv_nsec / 1e6);
	return 0;
#else
	return __syscall_ret(-__clock_nanosleep(CLOCK_REALTIME, 0, req, rem));
#endif
}
