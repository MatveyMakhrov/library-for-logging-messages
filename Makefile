# �������� �����
SRC = logger.cpp main.cpp
OBJ = $(SRC:.cpp=.o)

# ����������� ����
TARGET = logger_app

# ��������� �����, ������� ����� �������
TEMP_FILES = *.o *.tmp *.log *.bak

build:
	g++ -std=c++17 logger.cpp main.cpp -o logger_app -pthread

run:
	./$(TARGET) $(ARGS)

clean: 
	rm -f $(OBJ) $(TARGET) $(TEMP_FILES)