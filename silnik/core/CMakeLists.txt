set(nudny-silnik-core-headers
	${CMAKE_CURRENT_LIST_DIR}/include/Interfaces.h 
	${CMAKE_CURRENT_LIST_DIR}/include/KeyMap.h 
	${CMAKE_CURRENT_LIST_DIR}/include/Log.h 
	${CMAKE_CURRENT_LIST_DIR}/include/State.h 
	${CMAKE_CURRENT_LIST_DIR}/include/StateFactory.h 
	${CMAKE_CURRENT_LIST_DIR}/include/JSONLoader.h 
	${CMAKE_CURRENT_LIST_DIR}/include/Log.h 
	${CMAKE_CURRENT_LIST_DIR}/include/Keyboard.h 
	${CMAKE_CURRENT_LIST_DIR}/include/Resources.h
)

set(nudny-silnik-core-src
	${CMAKE_CURRENT_LIST_DIR}/src/App.cpp 
	${CMAKE_CURRENT_LIST_DIR}/src/JSONLoader.cpp 
	${CMAKE_CURRENT_LIST_DIR}/src/Log.cpp 
	${CMAKE_CURRENT_LIST_DIR}/src/Keyboard.cpp 
	${CMAKE_CURRENT_LIST_DIR}/src/Resources.cpp
	${nudny-silnik-core-headers}
)
	
add_library(nudny-silnik-core)

target_link_libraries(nudny-silnik-core box2d sfml-system sfml-window sfml-audio sfml-graphics sfml-network Xxf86vm stdc++fs )

target_sources(nudny-silnik-core PUBLIC ${nudny-silnik-core-src} )

target_include_directories(nudny-silnik-core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/lib/include )

enable_testing()
add_subdirectory(tests)
