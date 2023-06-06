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

SOURCES += src/terrain/Terrain.cpp
HEADERS += src/terrain/Terrain.hpp
HEADERS += src/terrain/TerrainTile.hpp
HEADERS += src/terrain/TerrainTileKind.hpp
HEADERS += src/terrain/MeadowTerrainTile.hpp
HEADERS += src/terrain/MountainsTerrainTile.hpp
HEADERS += src/terrain/UrbanTerrainTile.hpp
HEADERS += src/terrain/WaterTerrainTile.hpp

HEADERS += src/warnings/Warning.hpp
SOURCES += src/warnings/ProximityWarning.cpp
HEADERS += src/warnings/ProximityWarning.hpp
SOURCES += src/warnings/CollisionWarning.cpp
HEADERS += src/warnings/CollisionWarning.hpp

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
SOURCES += src/ui/TerrainView.cpp
HEADERS += src/ui/TerrainView.hpp
SOURCES += src/ui/RadarView.cpp
HEADERS += src/ui/RadarView.hpp
SOURCES += src/ui/RouteEditor.cpp
HEADERS += src/ui/RouteEditor.hpp
SOURCES += src/ui/WarningList.cpp
HEADERS += src/ui/WarningList.hpp
SOURCES += src/ui/WarningView.cpp
HEADERS += src/ui/WarningView.hpp
SOURCES += src/ui/FileSelector.cpp
HEADERS += src/ui/FileSelector.hpp

HEADERS += src/ui/Signal.hpp

CFLAGS += -Ithirdparty/
CFLAGS += `pkg-config --cflags raylib`
CFLAGS += -g
CFLAGS += -O2

WCFLAGS += -Wall
WCFLAGS += -Werror

LIBS += `pkg-config --libs raylib`

OBJECTS = $(subst src/,.obj/,$(subst .cpp,.o,$(SOURCES)))
OBJECTS += .obj/raygui.o

sim: ${OBJECTS} ${HEADERS}
	${CXX} -o $@ ${LIBS} ${OBJECTS}

dev: compile_flags.txt

web: web/index.html

compile_flags.txt:
	echo ${CFLAGS} ${WCFLAGS} | tr ' ' '\n' > $@

.obj/raygui.o: thirdparty/raygui.cpp
	$(CXX) -c $< ${CFLAGS} -Wno-enum-compare -o $@

.obj/%.o: src/%.cpp
	[ -d `dirname $@` ] || mkdir -p `dirname $@`
	$(CXX) -c $< ${CFLAGS} ${WCFLAGS} -o $@

EMFLAGS += -Os
EMFLAGS += ${CFLAGS}
EMFLAGS += -s WASM=1
EMFLAGS += -s USE_GLFW=3
EMFLAGS += -s ASYNCIFY
EMFLAGS += -s TOTAL_MEMORY=1024MB
EMFLAGS += --preload-file resources
EMFLAGS += --shell-file src/shell_minimal.html

web/index.html: ${SOURCES} ${HEADERS} thirdparty/libraylib.a
	[ -d web ] || mkdir web
	emcc -o $@ ${SOURCES} thirdparty/raygui.cpp thirdparty/libraylib.a  ${EMFLAGS}

thirdparty/libraylib.a:
	[ -f $@ ] || echo "[Error] You must provide thirdparty/libraylib.a for web build!!!" || exit 1 


TESTS += tests/position.cpp
TESTS += tests/terrain.cpp
TESTS += tests/mobile.cpp
TESTS += tests/collision.cpp

TEST_E = $(subst .cpp,.cpp.test,$(TESTS))

test: ${OBJECTS} ${TEST_E} 
	@echo Tests finished!

%.cpp.test: %.cpp
	@${CXX} -c ${CFLAGS} $< -o $@.o
	@${CXX} $@.o ${subst .obj/main.o,,${OBJECTS}} ${LIBS} -o $@.ex
	@./$@.ex || (echo "FAILURE: $@"; exit 42; ) 
	@echo "SUCCESS: $@"


