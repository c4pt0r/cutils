#include "c_logger.h"

#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

static struct logger logger;

// public api
int  c_log_init(int level,char* filename) {
    struct logger* l = &logger;
    l->level = MAX(LOG_EMERG, MIN(level, LOG_VERB));
    l->name = filename;
    if (filename == NULL || strlen(filename) == 0) {
        l->fd = STDERR_FILENO;
    } else {
        l->fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0664);
        if (l->fd < 0) {
            log_stderr("failed open log file %s failed as : %s", filename, strerror(errno));
            return -1;
        }
    }
    return 0;
}
void c_log_uninit(void) {
    struct logger* l = &logger;
    if (l->fd != STDERR_FILENO) {
        close(l->fd);
    }
}

void c_log_level_up(void) {
    struct logger* l = &logger;
    if (l->level < LOG_VERB) {
        l->level++;
        loga("log level up to %d", l->level);
    }
}

void c_log_level_down(void) {
    struct logger* l = &logger;
    if (l->level > LOG_EMERG) {
        l->level--;
        loga("log level down to %d", l->level);
    }
}

void c_log_level_set(int level) {
    struct logger* l = &logger;
    l->level = MAX(LOG_EMERG, MIN(level, LOG_VERB));
    loga("set log level to %d", l->level);
}

void c_log_reopen(void) {
    struct logger* l = &logger;
    if (l->fd != STDERR_FILENO) {
        close(l->fd);
        l->fd = open(l->name, O_WRONLY | O_APPEND | O_CREAT, 0664);
        if (l->fd < 0) {
            log_stderr("failed open log file %s failed as : %s", l->name, strerror(errno));
        }
    }
}
int c_log_loggable(int level) {
    struct logger* l = &logger;
    if (level > l->level) {
        return 0;
    }
    return 1;
}

// logger inner func
void _c_log(int level, const char* file, int line, int panic, const char* fmt, ...) {
    struct logger* l = &logger;
    int len, size, errno_save;
    char buf[1024] = {0};
    char* timestr;
    va_list args;
    struct tm *local;
    time_t t;
    ssize_t n;

    if (l->fd < 0) {
        return;
    }

    errno_save = errno;
    len = 0;
    size = 1024; /* size of ouput buffer */

    t = time(NULL);
    local = localtime(&t);
    timestr = asctime(local);

    len += snprintf(buf + len, size - len, "[%.*s][%d] %s:%d ",
                    strlen(timestr) - 1, timestr, level, file, line);

    va_start(args, fmt);
    len += vsnprintf(buf + len, size - len, fmt, args);
    va_end(args);

    buf[len++] = '\n';

    n = write(l->fd, buf, len);
    if (n < 0) {
        l->nerror++;
    }

    errno = errno_save;
    if (panic) {
        abort();
    }
}
void _c_log_stderr(const char* fmt, ...) {
    struct logger* l = &logger;
    int len,size, errno_save;
    char buf[1024];
    va_list args;
    ssize_t n;

    errno_save = errno;
    len = 0;
    size = 1024;

    va_start(args, fmt);
    len += vsnprintf(buf, size, fmt, args);
    va_end(args);

    buf[len++] = '\n';
    n = write(STDERR_FILENO, buf, len);
    if (n<0) {
        l->nerror++;
    }
    errno = errno_save;
}

