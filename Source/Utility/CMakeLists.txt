project(SimpleMemo)

set(CMAKE_CXX_STANDARD 17)

set(MODULE_NAME Utility)

find_package(Boost REQUIRED COMPONENTS serialization)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(UTILITY_SRC Comparer.h SerializationUtility.h
        TraverseHelper.h XMLUtility.h
        EventMonitor.cpp EventMonitor.h
        XMLUtility.h)


#add_library(${MODULE_NAME} STATIC ${UTILITY_SRC})
#
#TARGET_LINK_LIBRARIES(${MODULE_NAME} pthread Boost::serialization ws2_32)
