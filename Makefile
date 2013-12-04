#############################################################################
# Makefile for building: hangman
# Generated by qmake (2.01a) (Qt 4.8.1) on: Wed Dec 4 20:12:46 2013
# Project:  hangman.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile hangman.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -std=c++0x -g -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = Game.cpp \
		GameLogic.cpp \
		Hangman.cpp \
		KvpParser.cpp \
		main.cpp \
		QtApplication.cpp \
		QtGameWindow.cpp \
		QtGuess.cpp \
		QtHangman.cpp \
		QtLetters.cpp \
		QtUi.cpp \
		Strings.cpp \
		TextDisplay.cpp \
		TextHangman.cpp \
		TextUi.cpp moc_QtGameWindow.cpp \
		moc_QtGuess.cpp \
		moc_QtHangman.cpp \
		moc_QtLetters.cpp
OBJECTS       = Game.o \
		GameLogic.o \
		Hangman.o \
		KvpParser.o \
		main.o \
		QtApplication.o \
		QtGameWindow.o \
		QtGuess.o \
		QtHangman.o \
		QtLetters.o \
		QtUi.o \
		Strings.o \
		TextDisplay.o \
		TextHangman.o \
		TextUi.o \
		moc_QtGameWindow.o \
		moc_QtGuess.o \
		moc_QtHangman.o \
		moc_QtLetters.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		hangman.pro
QMAKE_TARGET  = hangman
DESTDIR       = 
TARGET        = hangman

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: hangman.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile hangman.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile hangman.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/hangman1.0.0 || $(MKDIR) .tmp/hangman1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/hangman1.0.0/ && $(COPY_FILE) --parents Game.hpp GameLogic.hpp GameState.hpp GameUi.hpp Hangman.hpp KvpParser.hpp QtApplication.hpp QtGameWindow.hpp QtGuess.hpp QtHangman.hpp QtLetters.hpp QtUi.hpp Strings.hpp TextDisplay.hpp TextHangman.hpp TextUi.hpp .tmp/hangman1.0.0/ && $(COPY_FILE) --parents Game.cpp GameLogic.cpp Hangman.cpp KvpParser.cpp main.cpp QtApplication.cpp QtGameWindow.cpp QtGuess.cpp QtHangman.cpp QtLetters.cpp QtUi.cpp Strings.cpp TextDisplay.cpp TextHangman.cpp TextUi.cpp .tmp/hangman1.0.0/ && (cd `dirname .tmp/hangman1.0.0` && $(TAR) hangman1.0.0.tar hangman1.0.0 && $(COMPRESS) hangman1.0.0.tar) && $(MOVE) `dirname .tmp/hangman1.0.0`/hangman1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/hangman1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_QtGameWindow.cpp moc_QtGuess.cpp moc_QtHangman.cpp moc_QtLetters.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_QtGameWindow.cpp moc_QtGuess.cpp moc_QtHangman.cpp moc_QtLetters.cpp
moc_QtGameWindow.cpp: GameLogic.hpp \
		KvpParser.hpp \
		Strings.hpp \
		GameState.hpp \
		Hangman.hpp \
		QtHangman.hpp \
		QtGuess.hpp \
		QtGameWindow.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) QtGameWindow.hpp -o moc_QtGameWindow.cpp

moc_QtGuess.cpp: Strings.hpp \
		QtGuess.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) QtGuess.hpp -o moc_QtGuess.cpp

moc_QtHangman.cpp: Hangman.hpp \
		Strings.hpp \
		QtHangman.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) QtHangman.hpp -o moc_QtHangman.cpp

moc_QtLetters.cpp: Strings.hpp \
		QtLetters.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) QtLetters.hpp -o moc_QtLetters.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

Game.o: Game.cpp Game.hpp \
		GameUi.hpp \
		TextUi.hpp \
		TextDisplay.hpp \
		Strings.hpp \
		KvpParser.hpp \
		GameLogic.hpp \
		GameState.hpp \
		Hangman.hpp \
		QtUi.hpp \
		Exception.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Game.o Game.cpp

GameLogic.o: GameLogic.cpp GameLogic.hpp \
		KvpParser.hpp \
		Strings.hpp \
		GameState.hpp \
		Hangman.hpp \
		FileException.hpp \
		Exception.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GameLogic.o GameLogic.cpp

Hangman.o: Hangman.cpp Exception.hpp \
		Strings.hpp \
		Hangman.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Hangman.o Hangman.cpp

KvpParser.o: KvpParser.cpp KvpParser.hpp \
		Strings.hpp \
		FileException.hpp \
		Exception.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o KvpParser.o KvpParser.cpp

main.o: main.cpp Exception.hpp \
		Strings.hpp \
		Game.hpp \
		GameUi.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

QtApplication.o: QtApplication.cpp QtApplication.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o QtApplication.o QtApplication.cpp

QtGameWindow.o: QtGameWindow.cpp Strings.hpp \
		QtGameWindow.hpp \
		GameLogic.hpp \
		KvpParser.hpp \
		GameState.hpp \
		Hangman.hpp \
		QtHangman.hpp \
		QtGuess.hpp \
		QtLetters.hpp \
		FileException.hpp \
		Exception.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o QtGameWindow.o QtGameWindow.cpp

QtGuess.o: QtGuess.cpp QtGuess.hpp \
		Strings.hpp \
		Exception.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o QtGuess.o QtGuess.cpp

QtHangman.o: QtHangman.cpp QtHangman.hpp \
		Hangman.hpp \
		Strings.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o QtHangman.o QtHangman.cpp

QtLetters.o: QtLetters.cpp QtLetters.hpp \
		Strings.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o QtLetters.o QtLetters.cpp

QtUi.o: QtUi.cpp QtUi.hpp \
		GameUi.hpp \
		QtApplication.hpp \
		QtGameWindow.hpp \
		GameLogic.hpp \
		KvpParser.hpp \
		Strings.hpp \
		GameState.hpp \
		Hangman.hpp \
		QtHangman.hpp \
		QtGuess.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o QtUi.o QtUi.cpp

Strings.o: Strings.cpp Strings.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Strings.o Strings.cpp

TextDisplay.o: TextDisplay.cpp TextDisplay.hpp \
		Strings.hpp \
		Exception.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TextDisplay.o TextDisplay.cpp

TextHangman.o: TextHangman.cpp TextHangman.hpp \
		Hangman.hpp \
		TextDisplay.hpp \
		Strings.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TextHangman.o TextHangman.cpp

TextUi.o: TextUi.cpp TextUi.hpp \
		GameUi.hpp \
		TextDisplay.hpp \
		Strings.hpp \
		KvpParser.hpp \
		GameLogic.hpp \
		GameState.hpp \
		Hangman.hpp \
		TextHangman.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TextUi.o TextUi.cpp

moc_QtGameWindow.o: moc_QtGameWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_QtGameWindow.o moc_QtGameWindow.cpp

moc_QtGuess.o: moc_QtGuess.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_QtGuess.o moc_QtGuess.cpp

moc_QtHangman.o: moc_QtHangman.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_QtHangman.o moc_QtHangman.cpp

moc_QtLetters.o: moc_QtLetters.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_QtLetters.o moc_QtLetters.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

