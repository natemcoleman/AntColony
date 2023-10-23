cmake_minimum_required(VERSION 3.23)

project(AntSimulation LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Create the AntWorld Library
add_library(AntWorld STATIC)

target_sources(AntWorld
    PRIVATE
    main.cpp
    Ant.cpp
    Food.cpp
    Colony.cpp
    AntWorld.cpp
    AntLogic.cpp
    FoodLogic.cpp
    ColonyLogic.cpp
    AntWorldLogic.cpp
    PUBLIC FILE_SET HEADERS
    BASE_DIRS ${PROJECT_SOURCE_DIR}
    FILES
    Ant.h
    Food.h
    Colony.h
    AntWorld.h
    AntLogic.hpp
    FoodLogic.hpp
    ColonyLogic.hpp
    AntWorldLogic.hpp
)

target_link_libraries(AntWorld
    PUBLIC
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
)

install(TARGETS AntWorld
    EXPORT AntWorldTargets
    FILE_SET HEADERS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)

install(EXPORT AntWorldTargets
    FILE AntWorldTargets.cmake
    NAMESPACE AntWorld::
    DESTINATION lib/cmake/AntWorld)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "AntWorldConfigVersion.cmake"
    VERSION ${AntWorld_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(
    FILES
        "AntWorldConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/AntWorldConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)

#create the Qt GUI Executable
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(AntSimulation ${PROJECT_SOURCES})
target_sources(AntSimulation PRIVATE
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  icons/icons.qrc
)

target_link_libraries(AntSimulation PRIVATE
  Qt6::Widgets
  AntWorld
)

#Create AntSimulation UnitTests Library
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(AntColony_UnitTests)
target_sources(AntColony_UnitTests
    PRIVATE AntColony_UnitTests.cpp
  )
target_link_libraries(AntColony_UnitTests PRIVATE
          ${GTEST_LIBRARIES}
     ${GTEST_MAIN_LIBRARIES}
    AntWorld
)
