cmake_minimum_required(VERSION 2.8)
 
PROJECT(QtTest)
 
FIND_PACKAGE(Qt5Widgets REQUIRED)

ADD_DEFINITIONS(${QT_DEFINITIONS}) 
 
# support for out-of-source build
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR} #this is where ui_SimpleViewUI.h is generated
  ${CMAKE_CURRENT_SOURCE_DIR}
  (${Qt5Widgets_INCLUDE_DIRS})
)
 
# Set your files and resources here
SET(SimpleViewSrcs main.cpp qtprogramwin.cpp)
SET(SimpleViewUI qtprogramwin.ui)
SET(SimpleViewHeaders qtprogramwin.h)
 
QT5_WRAP_UI(UISrcs ${SimpleViewUI})
QT5_WRAP_CPP(MOCSrcs ${SimpleViewHeaders} )
 
SOURCE_GROUP("Resources" FILES
  ${SimpleViewUI}
)
 
SOURCE_GROUP("Generated" FILES
  ${UISrcs}
  ${MOCSrcs}
)
ADD_EXECUTABLE( QtTest ${SimpleViewSrcs} ${UISrcs} ${MOCSrcs} ${SimpleViewHeaders} )
TARGET_LINK_LIBRARIES( QtTest ${Qt5Widgets_LIBRARIES})