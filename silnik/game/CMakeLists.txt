#nudny silnik game module

set(nudny-silnik-game-headers
	${CMAKE_CURRENT_LIST_DIR}/include/Actor.h 
	${CMAKE_CURRENT_LIST_DIR}/include/ActorInterface.h
	${CMAKE_CURRENT_LIST_DIR}/include/Enemy.h
	${CMAKE_CURRENT_LIST_DIR}/include/EnemyState.h
	${CMAKE_CURRENT_LIST_DIR}/include/EntityFactory.h
	${CMAKE_CURRENT_LIST_DIR}/include/Inventory.h
	${CMAKE_CURRENT_LIST_DIR}/include/Item.h 
	${CMAKE_CURRENT_LIST_DIR}/include/MapLayer.h
	${CMAKE_CURRENT_LIST_DIR}/include/Map.h
	${CMAKE_CURRENT_LIST_DIR}/include/Player.h
	${CMAKE_CURRENT_LIST_DIR}/include/PlayerState.h
)

set(nudny-silnik-game-src
	${CMAKE_CURRENT_LIST_DIR}/src/Actor.cpp 
	${CMAKE_CURRENT_LIST_DIR}/src/Map.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/MapLayer.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Player.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/PlayerState.cpp
)

add_library(nudny-silnik-game)

target_link_libraries(nudny-silnik-game)

target_sources(nudny-silnik-game PUBLIC ${nudny-silnik-game-src} )

target_include_directories(nudny-silnik-game 
	PUBLIC	
		${CMAKE_CURRENT_LIST_DIR}/../core/include 
		${CMAKE_CURRENT_LIST_DIR}/../core/lib/include 
		${CMAKE_CURRENT_LIST_DIR}/../visual/include 
		${CMAKE_CURRENT_LIST_DIR}/../visual/lib/include 
		${CMAKE_CURRENT_LIST_DIR}/include 
		${CMAKE_CURRENT_LIST_DIR}/lib/include 
)
