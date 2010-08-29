#############################################################################
# Makefile for building: QtMCTS
# Generated by qmake (2.01a) (Qt 4.6.2) on: ned avg 8 12:00:51 2010
# Project:  QtMCTS.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -unix -o Makefile QtMCTS.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Isrc -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
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

SOURCES       = src/Bishop.cpp \
		src/Game.cpp \
		src/GoToBorderGame.cpp \
		src/GoToCornerDirectGame.cpp \
		src/GoToCornerGame.cpp \
		src/KBNKLooserPlayer.cpp \
		src/KBNKWinnerPlayer.cpp \
		src/King.cpp \
		src/Knight.cpp \
		src/main.cpp \
		src/MCTSNode.cpp \
		src/MCTSPlayer.cpp \
		src/Piece.cpp \
		src/Player.cpp \
		src/Position.cpp \
		src/RandomPlayer.cpp \
		src/TableBase.cpp \
		src/TableBlackPlayer.cpp \
		src/TableWhitePlayer.cpp moc_Bishop.cpp \
		moc_Game.cpp \
		moc_GoToBorderGame.cpp \
		moc_GoToCornerDirectGame.cpp \
		moc_GoToCornerGame.cpp \
		moc_KBNKLooserPlayer.cpp \
		moc_KBNKWinnerPlayer.cpp \
		moc_King.cpp \
		moc_Knight.cpp \
		moc_MCTSNode.cpp \
		moc_MCTSPlayer.cpp \
		moc_Piece.cpp \
		moc_Player.cpp \
		moc_Position.cpp \
		moc_RandomPlayer.cpp \
		moc_TableBase.cpp \
		moc_TableBlackPlayer.cpp \
		moc_TableWhitePlayer.cpp
OBJECTS       = Bishop.o \
		Game.o \
		GoToBorderGame.o \
		GoToCornerDirectGame.o \
		GoToCornerGame.o \
		KBNKLooserPlayer.o \
		KBNKWinnerPlayer.o \
		King.o \
		Knight.o \
		main.o \
		MCTSNode.o \
		MCTSPlayer.o \
		Piece.o \
		Player.o \
		Position.o \
		RandomPlayer.o \
		TableBase.o \
		TableBlackPlayer.o \
		TableWhitePlayer.o \
		moc_Bishop.o \
		moc_Game.o \
		moc_GoToBorderGame.o \
		moc_GoToCornerDirectGame.o \
		moc_GoToCornerGame.o \
		moc_KBNKLooserPlayer.o \
		moc_KBNKWinnerPlayer.o \
		moc_King.o \
		moc_Knight.o \
		moc_MCTSNode.o \
		moc_MCTSPlayer.o \
		moc_Piece.o \
		moc_Player.o \
		moc_Position.o \
		moc_RandomPlayer.o \
		moc_TableBase.o \
		moc_TableBlackPlayer.o \
		moc_TableWhitePlayer.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		QtMCTS.pro
QMAKE_TARGET  = QtMCTS
DESTDIR       = 
TARGET        = QtMCTS

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

Makefile: QtMCTS.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix -o Makefile QtMCTS.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix -o Makefile QtMCTS.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/QtMCTS1.0.0 || $(MKDIR) .tmp/QtMCTS1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/QtMCTS1.0.0/ && $(COPY_FILE) --parents src/Bishop.h src/environment.h src/Game.h src/GoToBorderGame.h src/GoToCornerDirectGame.h src/GoToCornerGame.h src/KBNKLooserPlayer.h src/KBNKWinnerPlayer.h src/King.h src/Knight.h src/MCTSNode.h src/MCTSPlayer.h src/Piece.h src/Player.h src/Position.h src/RandomPlayer.h src/TableBase.h src/TableBlackPlayer.h src/TableWhitePlayer.h .tmp/QtMCTS1.0.0/ && $(COPY_FILE) --parents src/Bishop.cpp src/Game.cpp src/GoToBorderGame.cpp src/GoToCornerDirectGame.cpp src/GoToCornerGame.cpp src/KBNKLooserPlayer.cpp src/KBNKWinnerPlayer.cpp src/King.cpp src/Knight.cpp src/main.cpp src/MCTSNode.cpp src/MCTSPlayer.cpp src/Piece.cpp src/Player.cpp src/Position.cpp src/RandomPlayer.cpp src/TableBase.cpp src/TableBlackPlayer.cpp src/TableWhitePlayer.cpp .tmp/QtMCTS1.0.0/ && (cd `dirname .tmp/QtMCTS1.0.0` && $(TAR) QtMCTS1.0.0.tar QtMCTS1.0.0 && $(COMPRESS) QtMCTS1.0.0.tar) && $(MOVE) `dirname .tmp/QtMCTS1.0.0`/QtMCTS1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/QtMCTS1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_Bishop.cpp moc_Game.cpp moc_GoToBorderGame.cpp moc_GoToCornerDirectGame.cpp moc_GoToCornerGame.cpp moc_KBNKLooserPlayer.cpp moc_KBNKWinnerPlayer.cpp moc_King.cpp moc_Knight.cpp moc_MCTSNode.cpp moc_MCTSPlayer.cpp moc_Piece.cpp moc_Player.cpp moc_Position.cpp moc_RandomPlayer.cpp moc_TableBase.cpp moc_TableBlackPlayer.cpp moc_TableWhitePlayer.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_Bishop.cpp moc_Game.cpp moc_GoToBorderGame.cpp moc_GoToCornerDirectGame.cpp moc_GoToCornerGame.cpp moc_KBNKLooserPlayer.cpp moc_KBNKWinnerPlayer.cpp moc_King.cpp moc_Knight.cpp moc_MCTSNode.cpp moc_MCTSPlayer.cpp moc_Piece.cpp moc_Player.cpp moc_Position.cpp moc_RandomPlayer.cpp moc_TableBase.cpp moc_TableBlackPlayer.cpp moc_TableWhitePlayer.cpp
moc_Bishop.cpp: src/Piece.h \
		src/Player.h \
		src/Position.h \
		src/Bishop.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/Bishop.h -o moc_Bishop.cpp

moc_Game.cpp: src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/Game.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/Game.h -o moc_Game.cpp

moc_GoToBorderGame.cpp: src/Game.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/GoToBorderGame.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/GoToBorderGame.h -o moc_GoToBorderGame.cpp

moc_GoToCornerDirectGame.cpp: src/Game.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/GoToCornerDirectGame.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/GoToCornerDirectGame.h -o moc_GoToCornerDirectGame.cpp

moc_GoToCornerGame.cpp: src/Game.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/GoToCornerGame.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/GoToCornerGame.h -o moc_GoToCornerGame.cpp

moc_KBNKLooserPlayer.cpp: src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/KBNKLooserPlayer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/KBNKLooserPlayer.h -o moc_KBNKLooserPlayer.cpp

moc_KBNKWinnerPlayer.cpp: src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/KBNKWinnerPlayer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/KBNKWinnerPlayer.h -o moc_KBNKWinnerPlayer.cpp

moc_King.cpp: src/Piece.h \
		src/Player.h \
		src/Position.h \
		src/King.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/King.h -o moc_King.cpp

moc_Knight.cpp: src/Piece.h \
		src/Player.h \
		src/Position.h \
		src/Knight.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/Knight.h -o moc_Knight.cpp

moc_MCTSNode.cpp: src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/MCTSPlayer.h \
		src/MCTSNode.h \
		src/MCTSNode.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/MCTSNode.h -o moc_MCTSNode.cpp

moc_MCTSPlayer.cpp: src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/MCTSNode.h \
		src/MCTSPlayer.h \
		src/MCTSPlayer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/MCTSPlayer.h -o moc_MCTSPlayer.cpp

moc_Piece.cpp: src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/Piece.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/Piece.h -o moc_Piece.cpp

moc_Player.cpp: src/Position.h \
		src/Piece.h \
		src/Player.h \
		src/Player.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/Player.h -o moc_Player.cpp

moc_Position.cpp: src/Position.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/Position.h -o moc_Position.cpp

moc_RandomPlayer.cpp: src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/RandomPlayer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/RandomPlayer.h -o moc_RandomPlayer.cpp

moc_TableBase.cpp: src/Piece.h \
		src/Player.h \
		src/Position.h \
		src/TableBase.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/TableBase.h -o moc_TableBase.cpp

moc_TableBlackPlayer.cpp: src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/TableBase.h \
		src/TableBlackPlayer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/TableBlackPlayer.h -o moc_TableBlackPlayer.cpp

moc_TableWhitePlayer.cpp: src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/TableBase.h \
		src/TableWhitePlayer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/TableWhitePlayer.h -o moc_TableWhitePlayer.cpp

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

Bishop.o: src/Bishop.cpp src/environment.h \
		src/Bishop.h \
		src/Piece.h \
		src/Player.h \
		src/Position.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Bishop.o src/Bishop.cpp

Game.o: src/Game.cpp src/environment.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/Game.h \
		src/MCTSNode.h \
		src/MCTSPlayer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Game.o src/Game.cpp

GoToBorderGame.o: src/GoToBorderGame.cpp src/GoToBorderGame.h \
		src/Game.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GoToBorderGame.o src/GoToBorderGame.cpp

GoToCornerDirectGame.o: src/GoToCornerDirectGame.cpp src/GoToCornerDirectGame.h \
		src/Game.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GoToCornerDirectGame.o src/GoToCornerDirectGame.cpp

GoToCornerGame.o: src/GoToCornerGame.cpp src/GoToCornerGame.h \
		src/Game.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GoToCornerGame.o src/GoToCornerGame.cpp

KBNKLooserPlayer.o: src/KBNKLooserPlayer.cpp src/KBNKLooserPlayer.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/King.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o KBNKLooserPlayer.o src/KBNKLooserPlayer.cpp

KBNKWinnerPlayer.o: src/KBNKWinnerPlayer.cpp src/KBNKWinnerPlayer.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o KBNKWinnerPlayer.o src/KBNKWinnerPlayer.cpp

King.o: src/King.cpp src/environment.h \
		src/King.h \
		src/Piece.h \
		src/Player.h \
		src/Position.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o King.o src/King.cpp

Knight.o: src/Knight.cpp src/environment.h \
		src/Knight.h \
		src/Piece.h \
		src/Player.h \
		src/Position.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Knight.o src/Knight.cpp

main.o: src/main.cpp src/environment.h \
		src/Position.h \
		src/Piece.h \
		src/Player.h \
		src/RandomPlayer.h \
		src/KBNKLooserPlayer.h \
		src/KBNKWinnerPlayer.h \
		src/TableBlackPlayer.h \
		src/TableBase.h \
		src/TableWhitePlayer.h \
		src/MCTSPlayer.h \
		src/MCTSNode.h \
		src/Bishop.h \
		src/Knight.h \
		src/King.h \
		src/Game.h \
		src/GoToBorderGame.h \
		src/GoToCornerGame.h \
		src/GoToCornerDirectGame.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/main.cpp

MCTSNode.o: src/MCTSNode.cpp src/MCTSNode.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/MCTSPlayer.h \
		src/environment.h \
		src/GoToBorderGame.h \
		src/Game.h \
		src/GoToCornerGame.h \
		src/GoToCornerDirectGame.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MCTSNode.o src/MCTSNode.cpp

MCTSPlayer.o: src/MCTSPlayer.cpp src/MCTSPlayer.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/MCTSNode.h \
		src/environment.h \
		src/Game.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MCTSPlayer.o src/MCTSPlayer.cpp

Piece.o: src/Piece.cpp src/Piece.h \
		src/Player.h \
		src/Position.h \
		src/King.h \
		src/Knight.h \
		src/Bishop.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Piece.o src/Piece.cpp

Player.o: src/Player.cpp src/environment.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/RandomPlayer.h \
		src/KBNKLooserPlayer.h \
		src/KBNKWinnerPlayer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Player.o src/Player.cpp

Position.o: src/Position.cpp src/Position.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Position.o src/Position.cpp

RandomPlayer.o: src/RandomPlayer.cpp src/RandomPlayer.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o RandomPlayer.o src/RandomPlayer.cpp

TableBase.o: src/TableBase.cpp src/TableBase.h \
		src/Piece.h \
		src/Player.h \
		src/Position.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TableBase.o src/TableBase.cpp

TableBlackPlayer.o: src/TableBlackPlayer.cpp src/TableBlackPlayer.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/TableBase.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TableBlackPlayer.o src/TableBlackPlayer.cpp

TableWhitePlayer.o: src/TableWhitePlayer.cpp src/TableWhitePlayer.h \
		src/Player.h \
		src/Position.h \
		src/Piece.h \
		src/TableBase.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TableWhitePlayer.o src/TableWhitePlayer.cpp

moc_Bishop.o: moc_Bishop.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Bishop.o moc_Bishop.cpp

moc_Game.o: moc_Game.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Game.o moc_Game.cpp

moc_GoToBorderGame.o: moc_GoToBorderGame.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_GoToBorderGame.o moc_GoToBorderGame.cpp

moc_GoToCornerDirectGame.o: moc_GoToCornerDirectGame.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_GoToCornerDirectGame.o moc_GoToCornerDirectGame.cpp

moc_GoToCornerGame.o: moc_GoToCornerGame.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_GoToCornerGame.o moc_GoToCornerGame.cpp

moc_KBNKLooserPlayer.o: moc_KBNKLooserPlayer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_KBNKLooserPlayer.o moc_KBNKLooserPlayer.cpp

moc_KBNKWinnerPlayer.o: moc_KBNKWinnerPlayer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_KBNKWinnerPlayer.o moc_KBNKWinnerPlayer.cpp

moc_King.o: moc_King.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_King.o moc_King.cpp

moc_Knight.o: moc_Knight.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Knight.o moc_Knight.cpp

moc_MCTSNode.o: moc_MCTSNode.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MCTSNode.o moc_MCTSNode.cpp

moc_MCTSPlayer.o: moc_MCTSPlayer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MCTSPlayer.o moc_MCTSPlayer.cpp

moc_Piece.o: moc_Piece.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Piece.o moc_Piece.cpp

moc_Player.o: moc_Player.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Player.o moc_Player.cpp

moc_Position.o: moc_Position.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Position.o moc_Position.cpp

moc_RandomPlayer.o: moc_RandomPlayer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_RandomPlayer.o moc_RandomPlayer.cpp

moc_TableBase.o: moc_TableBase.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_TableBase.o moc_TableBase.cpp

moc_TableBlackPlayer.o: moc_TableBlackPlayer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_TableBlackPlayer.o moc_TableBlackPlayer.cpp

moc_TableWhitePlayer.o: moc_TableWhitePlayer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_TableWhitePlayer.o moc_TableWhitePlayer.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
