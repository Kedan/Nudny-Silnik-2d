set(nudny-silnik-visual-headers
	${CMAKE_CURRENT_LIST_DIR}/include/Animation.h 
	${CMAKE_CURRENT_LIST_DIR}/include/Shape.h
	${CMAKE_CURRENT_LIST_DIR}/include/Circle.h
	${CMAKE_CURRENT_LIST_DIR}/include/Rect.h 
	${CMAKE_CURRENT_LIST_DIR}/include/Poly.h 
	${CMAKE_CURRENT_LIST_DIR}/include/Sprite.h 
	${CMAKE_CURRENT_LIST_DIR}/include/Body.h
	${CMAKE_CURRENT_LIST_DIR}/include/Entity.h
	${CMAKE_CURRENT_LIST_DIR}/include/Text.h
	${CMAKE_CURRENT_LIST_DIR}/include/Tileset.h
)

set(nudny-silnik-visual-src
	${CMAKE_CURRENT_LIST_DIR}/src/Animation.cpp 
	${CMAKE_CURRENT_LIST_DIR}/src/Shape.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Circle.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Rect.cpp 
	${CMAKE_CURRENT_LIST_DIR}/src/Poly.cpp 
	${CMAKE_CURRENT_LIST_DIR}/src/Sprite.cpp 
	${CMAKE_CURRENT_LIST_DIR}/src/Body.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Entity.cpp 
	${CMAKE_CURRENT_LIST_DIR}/src/Text.cpp 
	${CMAKE_CURRENT_LIST_DIR}/src/Tileset.cpp 
)

add_library(nudny-silnik-visual)

target_link_libraries(nudny-silnik-visual)

target_sources(nudny-silnik-visual PUBLIC ${nudny-silnik-visual-src} )

target_include_directories(nudny-silnik-visual 
	PUBLIC	
		${CMAKE_CURRENT_LIST_DIR}/../core/include 
		${CMAKE_CURRENT_LIST_DIR}/../core/lib/include 
		${CMAKE_CURRENT_LIST_DIR}/include 
		${CMAKE_CURRENT_LIST_DIR}/lib/include 
)
