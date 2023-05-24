CXX=g++

SOURCES += src/main.cpp

SOURCES += src/ui/GUI.cpp
HEADERS += src/ui/GUI.hpp

CFLAGS += -Ithirdparty/
CFLAGS += `pkg-config --cflags raylib`

LIBS += `pkg-config --libs raylib`

sim: ${SOURCES} ${HEADERS}
	${CXX} -o $@ ${CFLAGS} ${LIBS} ${SOURCES}

dev: compile_flags.txt

compile_flags.txt:
	echo ${CFLAGS} | tr ' ' '\n' > $@
