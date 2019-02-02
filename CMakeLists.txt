cmake_minimum_required(VERSION 3.12)
project(SimpleMemo)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Source)
add_subdirectory(Test)

find_package(Boost REQUIRED COMPONENTS serialization)
find_package(cryptopp)
find_package(gtest)
find_package(snappy)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

#add_executable(SimpleMemo main.cpp ${MAIN_EXECUTABLE_SOURCE})
add_executable(SimpleMemo main.cpp
        Source/Entity/MemoData.cpp
        Source/Entity/MemoData.h
        Source/Entity/MemoStorage.cpp
        Source/Entity/MemoStorage.h
        Source/Utility/Comparer.h
        Source/Utility/XMLUtility.h
        Source/Utility/EventMonitor.cpp
        Source/Utility/EventMonitor.h
        Source/Utility/TraverseHelper.h
        Source/Utility/SerializationUtility.h
        Source/Utility/ParameterDecorator.h
        Source/Utility/Commons.h
        Source/Utility/Crypto.h
        Source/Utility/AbstractSingleton.h
        Source/Utility/UUIDUtility.h
        Source/Interface/Memo/AccessMemoInterface.h
        Source/Interface/Memo/AccessMemoInterfaceImpl.cpp
        Source/Interface/Memo/AccessMemoInterfaceImpl.h
        Source/Interface/Memo/MemoInterfaceParameters.h
        Source/Entity/MemoBookmark.cpp
        Source/Entity/MemoBookmark.h
        Source/Interface/Bookmark/BookmarkInterfaceParameters.h
        Source/Interface/Bookmark/AccessBookmarkInterface.h
        Source/Interface/Bookmark/AccessBookmarkInterfaceImpl.cpp
        Source/Interface/Bookmark/AccessBookmarkInterfaceImpl.h
        Source/UI/mainwindow.cpp
        Source/UI/mainwindow.h
        Source/UI/ui_mainwindow.h Source/Config/Constants.h Source/Core/MemoCore.cpp Source/Core/MemoCore.h Source/Interface/AbstractInterfaceProvider.h Source/Interface/Memo/MemoInterfaceProvider.h Source/Interface/Memo/MemoInterfaceProvider.cpp Source/Interface/Bookmark/BookmarkInterfaceProvider.cpp Source/Interface/Bookmark/BookmarkInterfaceProvider.h Source/Interface/Bookmark/HistoryInterfaceProvider.cpp Source/Interface/Bookmark/HistoryInterfaceProvider.h Source/Utility/CompressUtility.h Source/Entity/TransferEntity.h Source/Core/MainController.cpp Source/Core/MainController.h Source/Config/ChronoSerialization.h Source/Utility/StateMachine.cpp Source/Utility/StateMachine.h)



set(MAIN_LIBS pthread Boost::serialization cryptopp bcrypt snappy)
set(QT_LIBS Qt5::Core Qt5::Widgets Qt5::Gui)
target_link_libraries(SimpleMemo ${MAIN_LIBS} ${QT_LIBS})
