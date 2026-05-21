// Define a logging macro that automatically prints the caller function name
#define LOG(msg, ...) log_message(__func__, msg, ...)

void log_message(const char *func, const char *msg, ...);