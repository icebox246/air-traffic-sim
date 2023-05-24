CXX=g++

SOURCES += src/main.cpp

SOURCES += src/ui/GUI.cpp
HEADERS += src/ui/GUI.hpp

SOURCES += src/ui/Signal.cpp
HEADERS += src/ui/Signal.hpp

CFLAGS += -Ithirdparty/
CFLAGS += `pkg-config --cflags raylib`

LIBS += `pkg-config --libs raylib`

sim: ${SOURCES} ${HEADERS}
	${CXX} -o $@ ${CFLAGS} ${LIBS} ${SOURCES}

dev: compile_flags.txt

compile_flags.txt:
	echo ${CFLAGS} | tr ' ' '\n' > $@
