cmake_minimum_required(VERSION 3.0)
project(encoding_cpp)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
find_package(Protobuf REQUIRED)

set(INC_DIR
    p_imports)

set(SRC_LIST 
    example.cc 
    p_imports/person_info.pb.cc)


add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR} ${PROTOBUF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARIES})