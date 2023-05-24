CXX=g++

SOURCES += src/main.cpp

SOURCES += src/RadarSystem.cpp
HEADERS += src/RadarSystem.hpp

HEADERS += src/radar_objects/RadarObject.hpp
HEADERS += src/radar_objects/RadarObjectId.hpp
HEADERS += src/radar_objects/Route.hpp

HEADERS += src/terrain/Terrain.hpp

HEADERS += src/warnings/Warning.hpp

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
