include(flex.pri)

TEMPLATE = app
TARGET = ../bin/veaml
QT += widgets
INCLUDEPATH += . \
  ../include \
  "/usr/local/include/libopenshot" \
  "/usr/local/include/libopenshot/thirdparty" \
  "/usr/local/include/libopenshot/include" \
  "/usr/include/ImageMagick" \
  "/usr/include/qt5" \
  "/usr/include/qt5/QtGui" \
  "/usr/include/qt5/QtCore" \
  "/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64" \
  "/usr/local/include/libopenshot/include/Qt"

LIBS += -L/usr/local/lib -lopenshot -L /lib64 -lopenshot-audio -lfl

# Flex/Lex
FLEXSOURCES += ../src/veaml.lex

# Input
HEADERS += ../include/timeline.h
SOURCES += ../src/timeline.cc
