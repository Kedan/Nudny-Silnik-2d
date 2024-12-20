add_library(nudny-silnik
	core/src/Config.cpp
	core/src/Input.cpp
	core/src/GameState.cpp
	core/src/Camera.cpp
	core/src/AppConfig.cpp
	core/src/App.cpp
	graph/src/Adapter.cpp
	graph/src/Text.cpp
	graph/src/Circle.cpp
	graph/src/Rectangle.cpp
	graph/src/Polygon.cpp
	game/src/Hud.cpp
	game/src/Physic.cpp
	game/src/Body.cpp
)

target_include_directories(nudny-silnik PUBLIC
	ext
	core/include
	graph/include
	game/include
)
