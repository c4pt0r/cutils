#ifndef C_LOGGER_H_
#define C_LOGGER_H_

struct logger {
    char* name;
    int   level;
    int   fd;
    int   nerror;
};

enum {
    LOG_EMERG = 0,
    LOG_ALERT,
    LOG_ERROR,
    LOG_WARN,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG,
    LOG_VERB,
    LOG_MAX = 256,
    LOG_ALL = 257,
};

#if defined C_DEBUG_LOG && C_DEBUG_LOG == 1

#define log_debug(_level, ...) do {  \
    if (c_log_loggable(_level)) { \
       _c_log(_level, __FILE__, __LINE__, 0, __VA_ARGS__); \
    } \
} while (0)

#else

#define log_debug(_level, ...)

#endif


#define log_stderr(...) do { \
   _c_log_stderr(__VA_ARGS__); \
} while (0)

// loga means "log all"
#define loga(...) do { \
   _c_log(LOG_ALL, __FILE__, __LINE__, 0, __VA_ARGS__); \
} while (0)

// logger funcs
#define log_error(...) do { \
    if (c_log_loggable(LOG_ALERT)) { \
       _c_log(LOG_ALERT, __FILE__, __LINE__, 0, __VA_ARGS__); \
    } \
}while(0)

#define log_warn(...) do { \
    if (c_log_loggable(LOG_WARN)) { \
       _c_log(LOG_WARN, __FILE__, __LINE__, 0, __VA_ARGS__); \
    } \
}while(0)

#define log_panic(...) do { \
    if (c_log_loggable(LOG_EMERG)) { \
       _c_log(LOG_EMERG,__FILE__, __LINE__, 1, __VA_ARGS__); \
    } \
}while(0)

// public api
int  c_log_init(int level, char* filename);
void c_log_uninit(void);

void c_log_level_up(void);
void c_log_level_down(void);
void c_log_level_set(int level);
void c_log_reopen(void);
int  c_log_loggable(int level);

// logger inner func
void _c_log(int level, const char* file, int line, int panic, const char* fmt, ...);
void _c_log_stderr(const char* fmt, ...);

#endif
