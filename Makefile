#############################################################################
# Makefile for building: QIRC
# Generated by qmake (2.01a) (Qt 4.6.3) on: Mon Jan 3 15:41:20 2011
# Project:  QIRC.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile QIRC.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtNetwork -lQtCore -lpthread 
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

SOURCES       = main.cpp \
		message.cpp \
		channel.cpp \
		messageparser.cpp \
		user.cpp \
		ircserver.cpp \
		spambot.cpp moc_ircserver.cpp \
		moc_channel.cpp \
		moc_spambot.cpp
OBJECTS       = main.o \
		message.o \
		channel.o \
		messageparser.o \
		user.o \
		ircserver.o \
		spambot.o \
		moc_ircserver.o \
		moc_channel.o \
		moc_spambot.o
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
		QIRC.pro
QMAKE_TARGET  = QIRC
DESTDIR       = 
TARGET        = QIRC

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

Makefile: QIRC.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
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
		/usr/lib/libQtNetwork.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile QIRC.pro
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
/usr/lib/libQtNetwork.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile QIRC.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/QIRC1.0.0 || $(MKDIR) .tmp/QIRC1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/QIRC1.0.0/ && $(COPY_FILE) --parents ircserver.h message.h channel.h messageparser.h user.h ircconstants.h spambot.h .tmp/QIRC1.0.0/ && $(COPY_FILE) --parents main.cpp message.cpp channel.cpp messageparser.cpp user.cpp ircserver.cpp spambot.cpp .tmp/QIRC1.0.0/ && (cd `dirname .tmp/QIRC1.0.0` && $(TAR) QIRC1.0.0.tar QIRC1.0.0 && $(COMPRESS) QIRC1.0.0.tar) && $(MOVE) `dirname .tmp/QIRC1.0.0`/QIRC1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/QIRC1.0.0


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

compiler_moc_header_make_all: moc_ircserver.cpp moc_channel.cpp moc_spambot.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_ircserver.cpp moc_channel.cpp moc_spambot.cpp
moc_ircserver.cpp: message.h \
		ircserver.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ircserver.h -o moc_ircserver.cpp

moc_channel.cpp: message.h \
		channel.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) channel.h -o moc_channel.cpp

moc_spambot.cpp: message.h \
		spambot.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) spambot.h -o moc_spambot.cpp

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

main.o: main.cpp spambot.h \
		message.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

message.o: message.cpp message.h \
		ircconstants.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o message.o message.cpp

channel.o: channel.cpp channel.h \
		message.h \
		ircserver.h \
		ircconstants.h \
		user.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o channel.o channel.cpp

messageparser.o: messageparser.cpp messageparser.h \
		message.h \
		ircconstants.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o messageparser.o messageparser.cpp

user.o: user.cpp user.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o user.o user.cpp

ircserver.o: ircserver.cpp ircserver.h \
		message.h \
		ircconstants.h \
		channel.h \
		messageparser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ircserver.o ircserver.cpp

spambot.o: spambot.cpp spambot.h \
		message.h \
		ircserver.h \
		user.h \
		channel.h \
		ircconstants.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o spambot.o spambot.cpp

moc_ircserver.o: moc_ircserver.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ircserver.o moc_ircserver.cpp

moc_channel.o: moc_channel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_channel.o moc_channel.cpp

moc_spambot.o: moc_spambot.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_spambot.o moc_spambot.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

