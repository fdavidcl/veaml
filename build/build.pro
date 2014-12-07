include(flex.pri)

TEMPLATE = app
TARGET = ../bin/veaml
QT += widgets
CONFIG += c++11
QMAKE_CXXFLAGS += -fopenmp

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

LIBS += -L/usr/local/lib/libopenshot \
  -L/usr/local/lib/libopenshot-audio \
  -lopenshot -lopenshot-audio -lfl -lrt -std=c++11

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
