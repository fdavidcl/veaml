include(flex.pri)

TEMPLATE = app
TARGET = ../bin/veaml
QT += widgets
CONFIG += c++11
QMAKE_CXXFLAGS_DEBUG += -fopenmp
QMAKE_CXXFLAGS_RELEASE += -fopenmp

INCLUDEPATH += . \
  ../include \
  "/usr/local/include/libopenshot" \
  "/usr/local/include/libopenshot/thirdparty" \
  "/usr/local/include/libopenshot/include" \
  "/usr/local/include/libopenshot/include/Qt" \
  "/usr/local/include/libopenshot-audio" \
  "/usr/include/ImageMagick" \
  "/usr/include/qt5" \
  "/usr/include/qt5/QtGui" \
  "/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64" \
  "/usr/include/qt5/QtCore"

LIBS += \
  -L$(HOME)/ffmpeg_build/lib \
  -L/usr/local/lib/ \
  -lopenshot -lopenshot-audio -lfl -lrt -std=c++11 -Wl,-Bsymbolic \
  -lvorbis -lmp3lame -lfaac -lfdk-aac -lvpx -lx264 -llzma -lvorbisenc \
  -lswscale -lswresample -ltheora -ltheoraenc -ltheoradec `Magick++-config --ldflags`

# Flex/Lex
FLEXSOURCES += ../src/veaml.lex

# Input
HEADERS += \
  ../include/*.h

SOURCES += \
  ../src/timeline.cc \
  ../src/instant.cc \
  ../src/video.cc \
  ../src/image.cc \
  ../src/audio.cc
