CXX = g++
CXXFLAGS = -Wall -Iinclude

SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
OUT = bin/snake.exe

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /q $(OBJDIR)/* $(OUT)

.PHONY: all clean