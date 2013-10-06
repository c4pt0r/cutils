#include "c_utils.h"
#define C_DEBUG_LOG 1
#include "c_logger.h"

int main() {
    c_log_init(LOG_INFO, NULL);

    log_debug(LOG_INFO, "verb!");
    log_warn("warn");

    c_log_uninit();
}
