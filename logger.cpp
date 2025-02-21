#include "logger.hpp"

Logger::Logger(const std::string& filename, Priority defaultPriority)
	: filename(filename), defaultPriority(defaultPriority) {
}

void Logger::setPriorityLevel(Priority newPriority) {
	defaultPriority = newPriority;
}

std::string Logger::getCurrentTime() {
	std::time_t now = std::time(nullptr);
	char buf[80];
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	return std::string(buf);
}

std::string Logger::priorityToString(Priority priority) {
	switch (priority) {
	case Priority::LOW: return "[LOW]";
	case Priority::MEDIUM: return "[MEDIUM]";
	case Priority::HIGH: return "[HIGH]";
	default: return "[UNKNOWN]";
	}
}

void Logger::createFile() {
	std::ofstream file(filename, std::ios::app);
	file.close();
}

void Logger::writeToFile(const std::string& text, Priority priority) {
	if (priority < defaultPriority) return;

	std::lock_guard<std::mutex> lock(logMutex);
	std::ofstream file(filename, std::ios::app);
	if (file) {
		file << text << " " << priorityToString(priority) << " " << getCurrentTime() << std::endl;
	}
	else {
		std::cerr << "Ошибка записи в файл " << filename << std::endl;
	}
}




//int main() {
//	Logger newfile("example.txt", Priority::UNKNOWN);
//
//	std::string text;
//	int priorityLevel;
//
//	std::cout << "Enter a message: ";
//	std::getline(std::cin, text);
//	std::cout << "Enter the priority level (0 - LOW, 1 - MEDIUM, 2 - HIGH, -1 - no priority level): ";
//	std::cin >> priorityLevel;
//
//	Priority priority = static_cast<Priority>(priorityLevel);
//
//	newfile.createFile();
//	newfile.writeToFile(text, priority);
//}