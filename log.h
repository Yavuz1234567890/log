#include <functional>
#include <string>

enum LogLevel {
	ERR,
	WARNING,
	INFO,
	FATAL,
	SILENT
};

void push_log(std::string msg);
void push_log(const char* msg);
void push_log(int value);
void push_log(double value);
void push_log(float value);
void push_log(bool value);
void push_log(char value);
void push_log_function(std::function<void(int32_t, const char*)> function);
void invoke_log_functions(int32_t level, const char* message);
void bind_function(int32_t level);
template<typename... Args>
inline void log_message(int32_t level, Args... args) {
	push_log(static_cast<Args&&>(args)...);
	bind_function(level);
}
template<typename... Args>
inline void log_error(Args... args) {
	log_message(LogLevel::ERR, static_cast<Args&&>(args)...);
}
template<typename... Args>
inline void log_warning(Args... args) {
	log_message(LogLevel::WARNING, static_cast<Args&&>(args)...);
}
template<typename... Args>
inline void log_info(Args... args) {
	log_message(LogLevel::INFO, static_cast<Args&&>(args)...);
}
template<typename... Args>
inline void log_fatal(Args... args) {
	log_message(LogLevel::FATAL, static_cast<Args&&>(args)...);
}
template<typename... Args>
inline void log_silent(Args... args) {
	log_message(LogLevel::SILENT, static_cast<Args&&>(args)...);
}
