CC=g++
CFLAGS=-Wall -Wextra -O2
OUTNAME=portmap
BINDIR=bin
SRC=src
OBJDIR=obj
TARGET=$(BINDIR)/$(OUTNAME)

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(SRCS:$(SRC)/%.cpp=$(OBJDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRC)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
