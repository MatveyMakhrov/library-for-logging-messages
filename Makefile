build:
	g++ -std=c++17 logger.cpp main.cpp -o logger_app -pthread

clean: 
	rm -f logger_app