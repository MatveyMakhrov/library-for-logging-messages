#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <mutex>

enum class Priority {
	UNKNOWN = -1,
	LOW = 0,
	MEDIUM = 1,
	HIGH = 2
};

class Logger {
private:
	std::string filename;
	Priority defaultPriority;
	std::mutex logMutex;

	std::string getCurrentTime();
	std::string priorityToString(Priority priority);

public:
	Logger(const std::string& filename, Priority defaultPriority = Priority::UNKNOWN);
	//~Logger();

	void setPriorityLevel(Priority newpriority);
	void createFile();
	void writeToFile(const std::string& text, Priority priority);
	const Priority getDefaultPriority() {
		return defaultPriority;
	}
};