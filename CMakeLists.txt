cmake_minimum_required(VERSION 3.5)

project(QMemos VERSION 0.1 LANGUAGES CXX)
project(qmc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools WebEngineWidgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools WebEngineWidgets Network)

set(QT_DEFAULT_MAJOR_VERSION 6)
add_subdirectory(QHotkey)
include_directories(QHotkey/QHotkey)

set(TS_FILES QMemos_en_US.ts)

set(PROJECT_SOURCES
        main.cpp
        quickmemo.cpp
        quickmemo.h
        quickmemo.ui
        IniConfig.h
        IniConfig.cpp
        wrapper.cpp
        wrapper.h
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QMemos
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        res/res.qrc
    )
    qt_add_executable(qmc
        MANUAL_FINALIZATION
        wrapper.cpp
        wrapper.h
        qmc.cpp
        IniConfig.h
        IniConfig.cpp
    )
    qt_add_executable(QMemos2
        MANUAL_FINALIZATION
        main2.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QMemos APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(QMemos SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QMemos
            ${PROJECT_SOURCES}
            mainwindow.h mainwindow.cpp mainwindow.ui
            res/res.qrc
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(QMemos PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::WebEngineWidgets
)
target_link_libraries(qmc PRIVATE
    Qt${QT_VERSION_MAJOR}::Network
)
target_link_libraries(QMemos PRIVATE QHotkey::QHotkey)
target_link_libraries(QMemos2 PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QMemos)
endif()
set_target_properties(QMemos PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QMemos
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QMemos)
endif()



