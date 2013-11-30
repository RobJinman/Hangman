NAME = hangman
OUTDIR = .
CC = g++
CFLAGS = -std=c++0x -g -Wall
INCL =
LIBS =
SRC = .
OBJS = $(SRC)/TextDisplay.o \
	$(SRC)/TextHangman.o \
	$(SRC)/TextUi.o \
	$(SRC)/Game.o \
	$(SRC)/GameLogic.o \
	$(SRC)/Hangman.o \
	$(SRC)/KvpParser.o \
	$(SRC)/main.o \
	$(SRC)/Strings.o

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUTDIR)/$(NAME) $(LIBS)

$(OBJS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCL) $< -o $@

clean:
	rm -f $(SRC)/*.o
	rm -f $(OUTDIR)/$(NAME)
