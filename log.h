#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    LOG_ALL   = 0,
    LOG_TRACE = 1,
    LOG_DEBUG = 2,
    LOG_INFO  = 3,
    LOG_WARN  = 4,
    LOG_ERROR = 5,
    LOG_FATAL = 6,
    LOG_OFF   = 7
} log_level;

/* Set the level of log display */
void log_set_user_level(log_level level);
log_level log_get_user_level(void);
const char *log_get_level_str(log_level level);
log_level log_get_level_by_str(const char *str);
void log_init(void);

#define LOG_USER_LEVEL_ENV_STR "LOG_USER_LEVEL"

#define LOG_COLOR_RED    "\x1b[91m"
#define LOG_COLOR_YELLOW "\x1b[93m"
#define LOG_COLOR_CYAN   "\x1b[96m"
#define LOG_COLOR_GREEN  "\x1b[92m"
#define LOG_COLOR_MAGENTA  "\x1b[35m"
#define LOG_COLOR_RESET  "\x1b[0m"

#define log(level, color, fmt, ...)  \
    do{ \
        if(level >= log_get_user_level())\
        { \
            fprintf(stderr, color);                    \
            fprintf(stderr, "%s: %s(%d): ", log_get_level_str(level), __func__ , __LINE__); \
            fprintf(stderr, fmt, ##__VA_ARGS__); \
            fprintf(stderr, LOG_COLOR_RESET); \
            fflush(stderr); \
        } \
    } while(0)

/* use log_fatal where process would totally crash */
#define log_fatal(fmt, ...) do{log(LOG_FATAL, LOG_COLOR_RED, fmt, ##__VA_ARGS__);}while(0)

/* use log_error where code should not enter (e.g. malloc fails)*/
#define log_error(fmt, ...) do{log(LOG_ERROR, LOG_COLOR_RED, fmt, ##__VA_ARGS__);}while(0)

#ifdef DEBUG /* debug version, show all log level */

/* use log_warn where user operation fails (e.g. parameter is invalid)*/
#define log_warn(fmt, ...) do{log(LOG_WARN, LOG_COLOR_YELLOW, fmt, ##__VA_ARGS__); }while(0)

/* use log_info where main system open/close fails (e.g. socket connect fails)*/
#define log_info(fmt, ...) do{log(LOG_INFO, LOG_COLOR_CYAN, fmt, ##__VA_ARGS__); }while(0)

/* use log_debug where something special for developers */
#define log_debug(fmt, ...) do{log(LOG_DEBUG, LOG_COLOR_GREEN, fmt, ##__VA_ARGS__); }while(0)

/* use log_trace where is normal but has significance */
#define log_trace(fmt, ...) do{log(LOG_TRACE, LOG_COLOR_MAGENTA, fmt, ##__VA_ARGS__); }while(0)

/* use log_all where is normal and no significance */
#define log_all(fmt, ...) do{log(LOG_ALL, LOG_COLOR_MAGENTA,  fmt, ##__VA_ARGS__); }while(0)
#else /* release version, do not show warn~all level */

#define log_warn(...)
#define log_info(...)
#define log_debug(...)
#define log_trace(...)
#define log_all(...)
#endif /* MOXA_DEBUG */

#endif /* _LOG_H_ */
