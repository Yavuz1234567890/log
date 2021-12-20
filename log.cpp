#include "log.h"

#include <vector>
#include <memory>

static struct {
	std::vector<std::function<void(int32_t, const char*)>> log_functions;
	int ilfi;
	std::string log_message_buffer;
} s_log_data;

void push_log(std::string msg) {
	s_log_data.log_message_buffer += msg;
}

void push_log(const char* msg) {
	s_log_data.log_message_buffer += std::string(msg);
}

void push_log(int value) {
	s_log_data.log_message_buffer += std::to_string(value);
}

void push_log(double value) {
	s_log_data.log_message_buffer += std::to_string(value);
}

void push_log(float value) {
	s_log_data.log_message_buffer += std::to_string(value);
}

void push_log(bool value) {
	s_log_data.log_message_buffer += value ? "true" : "false";
}

void push_log(char value) {
	char* buffer = (char*)std::malloc(2);
	buffer[0] = value;
	buffer[1] = 0;
	s_log_data.log_message_buffer += std::string(buffer);
}

void push_log_function(std::function<int32_t, const char*> function) {
	s_log_data.log_functions.push_back(function);
}

void invoke_log_functions(int32_t level, const char* message) {
	for (s_log_data.ilfi = 0; s_log_data.ilfi < s_log_data.log_functions.size(); s_log_data.ilfi++) {
		s_log_data.log_functions[s_log_data.ilfi](level, message);
	}
}

void bind_function(int32_t level) {
	invoke_log_functions(level, s_log_data.log_message_buffer.c_str());
	s_log_data.log_message_buffer.clear();
}
