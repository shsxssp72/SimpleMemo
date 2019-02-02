cmake_minimum_required(VERSION 3.12)
project(SimpleMemo)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS serialization)
find_package(snappy)
find_package(cryptopp)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(UTILITY_SRC ../Source/Utility/Comparer.h
        ../Source/Utility/SerializationUtility.h
        ../Source/Utility/TraverseHelper.h
        ../Source/Utility/XMLUtility.h
        ../Source/Utility/XMLUtility.h
        ../Source/Utility/CompressUtility.h
        )
set(ENTITY ../Source/Entity/MemoData.cpp
        ../Source/Entity/MemoData.h
        ../Source/Entity/MemoStorage.cpp
        ../Source/Entity/MemoStorage.h
        ../Source/Entity/MemoBookmark.cpp
        ../Source/Entity/MemoBookmark.h
        )


add_executable(SimpleMemoTest main.cpp SerializationTest.cpp ${UTILITY_SRC} ${ENTITY})

target_link_libraries(SimpleMemoTest gtest pthread Boost::serialization snappy cryptopp bcrypt)