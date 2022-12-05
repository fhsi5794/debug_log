/*****************************************************************************
 * Include files
 ****************************************************************************/
#include <log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 * Private types/enumerations/variables/define
 ****************************************************************************/
#ifdef DEBUG
static log_level g_log_user_level = LOG_ALL;
#else /* RELEASE mode */
static log_level g_log_user_level = LOG_WARN;
#endif

static char *g_level_str_list[] = { "ALL", "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL", "OFF" };

/*****************************************************************************
 * Public functions
 ****************************************************************************/
void log_set_user_level(log_level level)
{
    g_log_user_level = level;
}

log_level log_get_user_level(void)
{
    return g_log_user_level;
}

log_level log_get_level_by_str(const char *str)
{
    log_level level;

    for (level = 0; level < sizeof(g_level_str_list) / sizeof(g_level_str_list[0]); level++)
    {
        if (!strncmp(g_level_str_list[level], str, strlen(g_level_str_list[level])))
        {
            return level;
        }
    }

    return g_log_user_level;
}

const char *log_get_level_str(log_level level)
{
    return g_level_str_list[level];
}

void log_init(void)
{
    const char *log_env;

    log_env = getenv(LOG_USER_LEVEL_ENV_STR);

    if (log_env)
    {
        log_level env_level;
        env_level = log_get_level_by_str(log_env);
        log_set_user_level(env_level);
    }
}
