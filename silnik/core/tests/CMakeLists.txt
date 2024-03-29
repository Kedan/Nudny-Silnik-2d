# UNIT TEST CMAKE CONF
find_package(Catch2 3 REQUIRED)
add_executable( core-unit-test Interfaces_Test.cpp)
target_link_libraries(core-unit-test
	PUBLIC	
		nudny-silnik-core 
	PRIVATE 
		Catch2::Catch2WithMain
)
add_test(
	NAME
		test_interface
	COMMAND
		$<TARGET_FILE:core-unit-test>
)
