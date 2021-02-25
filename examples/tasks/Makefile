SRCS=$(wildcard *.cpp)

TARGETS=$(patsubst %.cpp,%,$(SRCS))

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

.cpp:
	g++ -O0 -g -Wall -Werror `pkg-config --cflags sword` $< -o $@ `pkg-config --libs sword`
.c:
	gcc -O0 -g -Wall -Werror `pkg-config --cflags sword` $< -o $@ `pkg-config --libs sword` -lstdc++


