NAME = hangman
OUTDIR = .
CC = g++
CFLAGS = -std=c++0x -O3 -Wall
INCL =
LIBS =
SRC = .
OBJS = $(SRC)/AsciiDisplay.o \
	$(SRC)/AsciiHangman.o \
	$(SRC)/AsciiUi.o \
	$(SRC)/Game.o \
	$(SRC)/GameLogic.o \
	$(SRC)/Hangman.o \
	$(SRC)/main.o

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUTDIR)/$(NAME) $(LIBS)

$(OBJS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCL) $< -o $@

clean:
	rm -f $(SRC)/*.o
	rm -f $(OUTDIR)/$(NAME)
