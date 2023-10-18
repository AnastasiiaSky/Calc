cmake_minimum_required(VERSION 3.5)

project(SMART_CALC VERSION 0.1 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport REQUIRED)




set(PROJECT_SOURCES
        main.cc

        mainwindow.cc
        mainwindow.h
        mainwindow.ui

        graphwindow.cc
        graphwindow.h
        graphwindow.ui

        creditwindow.cc
        creditwindow.h
        creditwindow.ui


        ../controller/controller.h
        ../controller/controller.cc

        ../model/smart_calc.cc
        ../model/smart_calc.h
        ../model/string_validation.cc
        ../model/string_validation.h
        ../model/credit_calc.cc
        ../model/credit_calc.h

        library/qcustomplot.cc
        library/qcustomplot.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SMART_CALC
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SMART_CALC APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SMART_CALC SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SMART_CALC
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SMART_CALC PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(SMART_CALC PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

#file(COPY ${app_icon_macos} DESTINATION ${ICON_DESTINATION})


set_target_properties(SMART_CALC PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SMART_CALC)
endif()
