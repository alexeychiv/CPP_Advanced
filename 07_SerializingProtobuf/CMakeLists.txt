cmake_minimum_required(VERSION 3.20)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

project (${ProjectId})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")


#------------------
#PROTOBUF
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set (ProtoSources
	test.proto
	Students.proto
)

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${ProtoSources})
#------------------

add_executable(${ProjectId} #WIN32
	main.cpp
	
	StudentsGroup.h
	StudentsGroup.cpp
	
	${PROTO_SRCS}
	${PROTO_HDRS}
)

target_link_libraries(${ProjectId}
    ${PROTOBUF_LIBRARY}
)