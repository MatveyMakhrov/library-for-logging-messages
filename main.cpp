#include "logger.hpp"
#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>

std::queue<std::pair<std::string, Priority>> messageQueue;
std::mutex queueMutex;
std::condition_variable cv;
std::atomic<bool> isRunning(true);

void userInput(Logger& logger) {
    while (isRunning) {
        std::string text;
        int priorityLevel;

        std::cout << "Enter a message: ";
        std::getline(std::cin, text);
        if (text.empty()) {
            continue;
        }

        std::cout << "Enter the priority level (0 - LOW, 1 - MEDIUM, 2 - HIGH): ";
        std::cin >> priorityLevel;
        std::cin.ignore(); // To consume the newline after entering the priority

        // ≈сли пользователь не указал уровень важности, используетс€ Priority::UNKNOWN
        Priority priority = (priorityLevel == -1) ? logger.getDefaultPriority() : static_cast<Priority>(priorityLevel);

        // ѕоложим сообщение в очередь дл€ записи
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            messageQueue.push({ text, priority });
        }
        cv.notify_one(); // ”ведомление дл€ потока записи
    }
}

void logWriter(Logger& logger) {
    while (isRunning || !messageQueue.empty()) {
        std::pair<std::string, Priority> message;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, []() { return !messageQueue.empty() || !isRunning; });

            if (!messageQueue.empty()) {
                message = messageQueue.front();
                messageQueue.pop();
            }
        }

        if (!message.first.empty()) {
            logger.writeToFile(message.first, message.second);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <log_filename> [default_priority]" << std::endl;
        return 1;
    }

    std::string logFilename = argv[1];
    Priority defaultPriority = Priority::UNKNOWN; // ѕо умолчанию Priority::UNKNOWN
    if (argc >= 3) {
        int defaultPriorityLevel = std::stoi(argv[2]);
        defaultPriority = static_cast<Priority>(defaultPriorityLevel);
    }

    Logger logger(logFilename, defaultPriority);

    std::thread inputThread(userInput, std::ref(logger));
    std::thread writerThread(logWriter, std::ref(logger));

    // ќжидание завершени€ работы потоков
    inputThread.join();
    isRunning = false;
    cv.notify_one(); // ”ведомл€ем поток записи о завершении работы

    writerThread.join();

    return 0;
}
