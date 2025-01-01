cmake_minimum_required(VERSION 3.5)

project(CircularByte LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    circularbyte.cpp
    main.cpp
)

set(HEADERS
    circularbyte.h
)

add_executable(CircularByte ${SOURCES} ${HEADERS})

install(TARGETS CircularByte
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
