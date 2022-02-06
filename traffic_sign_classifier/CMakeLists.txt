CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(trafic_sign_classifier)
ENABLE_LANGUAGE(CXX)
SET (CMAKE_CXX_STANDARD 11) 

FIND_PACKAGE(OpenCV 3.4	REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

add_executable(train_test_clf train_test_clf.cpp debug.hpp debug.cpp dataset.cpp dataset.hpp metrics.cpp metrics.hpp features.hpp features.cpp)
add_executable(test_image test_image.cpp debug.hpp debug.cpp dataset.cpp dataset.hpp features.hpp features.cpp)

 
