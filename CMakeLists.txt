cmake_minimum_required(VERSION 3.17)
project(FastStlViewer)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON) # Enable Qt MOC compiler
set(CMAKE_AUTORCC ON) # Enable Qt resources compiler
set(CMAKE_AUTOUIC ON) # Enable Qt UI compiler

#set(CMAKE_PREFIX_PATH "C:/Qt/6.4.2/mingw_64/lib/cmake")

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\")")
endif ()

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Widgets Gui)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Widgets Qt6::Gui)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -O0")

set(SOURCES main.cpp
        View/view.cpp
        Model/Model.cpp
        Controller/controller.cpp
        Model/model_loader.cpp
        View/camera.cpp
        Model/geometry.cpp
        utils.cpp
        Model/ModelParsers/ascii_parser.cpp
        Model/ModelParsers/binary_parser.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})