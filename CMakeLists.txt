project(GPRD)

cmake_minimum_required(VERSION 2.8)

set(OPENCV_PATH C:/Users/patrick/Downloads/opencv3/opencv/build CACHE PATH "Der Pfad zum opencv build Verzeichnis")
set(FFTW_PATH C:/Users/patrick/Downloads/fftw-3.3.4-dll32 CACHE PATH "Der Pfad zum fftw Verzeichnis")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(_DEBUG_POSTFIX "d")
else()
    set(_DEBUG_POSTFIX "")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
   set(_ARCH x64)
else()
    set(_ARCH x86)
endif()

include_directories(${OPENCV_PATH}/include ${FFTW_PATH})
link_directories(${OPENCV_PATH}/${_ARCH}/vc12/lib ${FFTW_PATH})

include_directories(GraphicPulseRateDetector)

set(GPRD_SRCS
#     GraphicPulseRateDetector/Functions.cpp
    GraphicPulseRateDetector/GetPulse.cpp
    GraphicPulseRateDetector/GraphicPulseRateDetector.cpp
    GraphicPulseRateDetector/Source.cpp
)

add_executable(gprd ${GPRD_SRCS})
target_link_libraries(gprd opencv_world300${_DEBUG_POSTFIX})