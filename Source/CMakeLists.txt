project(SimpleMemo)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(Utility)


set(ENTITY Entity/MemoData.cpp Entity/MemoData.h)


set(MAIN_EXECUTABLE_SOURCE ${ENTITY})
