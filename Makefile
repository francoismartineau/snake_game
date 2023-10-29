CXX = g++
CXXFLAGS = -Wall -Iinclude
CXXFLAGS += -MMD
CXXFLAGS += -g
# CXXFLAGS += -O3

SRCDIR = src
OBJDIR = obj
SRCS = define.cpp \
	apple.cpp game.cpp gameDraw.cpp graph.cpp main.cpp snake.cpp util.cpp wall.cpp
SRCS := $(addprefix $(SRCDIR)/, $(SRCS))
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
OUTDIR = bin
OUT = .\$(OUTDIR)\snake.exe

all: $(OUT)

$(OUT): $(OBJS)
	@if not exist "$(OUTDIR)" mkdir $(OUTDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@if not exist "$(OBJDIR)" mkdir $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rmdir /s /q $(OBJDIR) 2>NUL

fclean: clean
	-rmdir /s /q $(OUTDIR) 2>NUL

re: fclean all

.PHONY: all clean fclean re
-include $(OBJS:.o=.d)