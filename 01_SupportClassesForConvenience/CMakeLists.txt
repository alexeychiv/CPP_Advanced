cmake_minimum_required(VERSION 3.20)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

project (${ProjectId})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-O2 -g -Wall -Wextra")

add_subdirectory(PhoneBook)

add_executable(${ProjectId} #WIN32
	main.cpp
)

target_link_libraries(${ProjectId} PhoneBook)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/PhoneBook.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})