include(flex.pri)

TEMPLATE = app
TARGET = ../bin/veaml
QT += widgets
INCLUDEPATH += . \
  ../include \
  "/usr/include/ImageMagick" \
  "/usr/include/qt5" \
  "/usr/include/qt5/QtGui" \
  "/usr/include/qt5/QtCore" \
  "/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64" \
  "../thirdparty/libopenshot/include" \
  "../thirdparty/libopenshot/include/thirdparty" \
  "../thirdparty/libopenshot/include/include" \
  "../thirdparty/libopenshot/include/include/Qt" \
  "../thirdparty/libopenshot-audio/include"

LIBS += -L../thirdparty/libopenshot/lib -L../thirdparty/libopenshot-audio/lib -lopenshot -lopenshot-audio -lfl

# Flex/Lex
FLEXSOURCES += ../src/veaml.lex

# Input
HEADERS += ../include/timeline.h
SOURCES += ../src/timeline.cc
