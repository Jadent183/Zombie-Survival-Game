CC = g++
CFLAGS = -Wall -g -std=c++11
SRCS = main.cpp 
HDRS = Array2D.hpp macros.h Player.hpp functions.hpp
OBJS = $(SRCS:.cpp=.o)
EXEC = exe

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

debug: $(OBJS)
	$(CC) -fsanitize=address $(CFLAGS) $(OBJS) -o $(EXEC)