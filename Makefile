CXX = g++
CXXFLAGS = -O3 -Wall -Iinclude
CXXFLAGS += -MMD
CXXFLAGS += -g

SRCDIR = src
OBJDIR = obj
SRCS = define.cpp \
	apple.cpp Game.cpp GameDraw.cpp graph.cpp main.cpp snake.cpp util.cpp wall.cpp
SRCS := $(addprefix $(SRCDIR)/, $(SRCS))
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
OUT = bin\snake.exe

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@if not exist "$(OBJDIR)" mkdir $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rmdir /s /q $(OBJDIR) 2>NUL

fclean: clean
	-rm $(OUT) 2>NUL

re: fclean all

.PHONY: all clean fclean re
-include $(OBJS:.o=.d)