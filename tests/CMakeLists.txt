cmake_minimum_required(VERSION 3.0.0)

# tests using Google Test.
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# get all tests
file(GLOB TESTS *.cpp)

# loop over each test
foreach(test_source ${TESTS})
    # strip .cpp extension:
    get_filename_component(test_name ${test_source} NAME)
    string( REPLACE ".cpp" "" test_file_name ${test_name})


    add_executable(${test_file_name} ${test_source})
    target_link_libraries(${test_file_name} PUBLIC ${PROJECT_NAME} -pthread ${GTEST_LIBRARIES})

endforeach(test_source ${TESTS})