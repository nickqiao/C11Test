cmake_minimum_required(VERSION 3.6)
project(C11Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SmartPointer.cpp Thread.cpp ConditionVariable.cpp Future.cpp Note.cpp ManageResource.cpp Animal.cpp)
add_executable(C11Test ${SOURCE_FILES})
add_executable(SmartPointer SmartPointer.cpp)
add_executable(ConditionVariable ConditionVariable.cpp)
add_executable(Future Future.cpp)
add_executable(Note Note.cpp)
add_executable(ManageResource ManageResource.cpp)