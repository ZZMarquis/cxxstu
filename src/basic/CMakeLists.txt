include_directories(${CMAKE_SOURCE_DIR}/src/basic)

set(COMMON_SRC common.hpp)

add_executable(prameter parameter.cpp ${COMMON_SRC})

add_executable(return return.cpp ${COMMON_SRC})

add_executable(move move.cpp ${COMMON_SRC})

add_executable(memory memory.cpp ${COMMON_SRC})

add_executable(map map.cpp ${COMMON_SRC})