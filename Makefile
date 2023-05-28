CXX=g++

SOURCES += src/main.cpp

SOURCES += src/RadarSystem.cpp
HEADERS += src/RadarSystem.hpp

HEADERS += src/Position.hpp
HEADERS += src/RealPosition.hpp

HEADERS += src/radar_objects/RadarObject.hpp
SOURCES += src/radar_objects/RadarObject.cpp
HEADERS += src/radar_objects/RadarObjectId.hpp
HEADERS += src/radar_objects/RadarObjectKind.hpp
HEADERS += src/radar_objects/Route.hpp
SOURCES += src/radar_objects/Route.cpp
HEADERS += src/radar_objects/CollisionComputer.hpp
SOURCES += src/radar_objects/CollisionComputer.cpp
HEADERS += src/radar_objects/RouteCheckpoint.hpp
HEADERS += src/radar_objects/ImmobileRadarObject.hpp
HEADERS += src/radar_objects/Skyscraper.hpp
HEADERS += src/radar_objects/Mountain.hpp
HEADERS += src/radar_objects/Windmill.hpp
HEADERS += src/radar_objects/MobileRadarObject.hpp
SOURCES += src/radar_objects/MobileRadarObject.cpp
HEADERS += src/radar_objects/Plane.hpp
HEADERS += src/radar_objects/Helicopter.hpp
HEADERS += src/radar_objects/Glider.hpp
HEADERS += src/radar_objects/HotAirBalloon.hpp

HEADERS += src/terrain/Terrain.hpp

HEADERS += src/warnings/Warning.hpp
SOURCES += src/warnings/ProximityWarning.cpp
HEADERS += src/warnings/ProximityWarning.hpp

SOURCES += src/ui/GUI.cpp
HEADERS += src/ui/GUI.hpp
SOURCES += src/ui/Label.cpp
HEADERS += src/ui/Label.hpp
SOURCES += src/ui/Button.cpp
HEADERS += src/ui/Button.hpp
SOURCES += src/ui/TextField.cpp
HEADERS += src/ui/TextField.hpp
SOURCES += src/ui/RealField.cpp
HEADERS += src/ui/RealField.hpp
SOURCES += src/ui/RadarView.cpp
HEADERS += src/ui/RadarView.hpp
SOURCES += src/ui/RouteEditor.cpp
HEADERS += src/ui/RouteEditor.hpp

HEADERS += src/ui/Signal.hpp

CFLAGS += -Ithirdparty/
CFLAGS += `pkg-config --cflags raylib`
CFLAGS += -g

LIBS += `pkg-config --libs raylib`

OBJECTS = $(subst src/,.obj/,$(subst .cpp,.o,$(SOURCES)))

sim: ${OBJECTS} ${HEADERS}
	${CXX} -o $@ ${LIBS} ${OBJECTS}

dev: compile_flags.txt

compile_flags.txt:
	echo ${CFLAGS} | tr ' ' '\n' > $@

.obj/%.o: src/%.cpp
	[ -d `dirname $@` ] || mkdir -p `dirname $@`
	$(CXX) -c $< ${CFLAGS} -o $@
