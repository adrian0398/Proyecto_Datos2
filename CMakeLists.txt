cmake_minimum_required(VERSION 3.3)
project(Proyecto1_Datos2)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp Linkedlist.cpp Linkedlist.h Movie.cpp Movie.h jsoncpp.cpp Html.cpp Html.h MovieComponent.cpp MovieComponent.h VideoPlayer.cpp VideoPlayer.h Pagina.cpp Pagina.h Imagelist.cpp Imagelist.h)
add_executable(Proyecto1_Datos2 ${SOURCE_FILES})

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
include_directories(./include)


find_package(Boost REQUIRED regex date_time system filesystem thread graph)
include_directories(${BOOST_INCLUDE_DIRS})
target_link_libraries(Proyecto1_Datos2 ${Boost_LIBRARIES})


include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(Proyecto1_Datos2 ${CURL_LIBRARIES})



find_package(PkgConfig REQUIRED)


pkg_check_modules(GTK3 REQUIRED gtk+-3.0 gmodule-2.0 )


include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
include_directories(./include)


add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(Proyecto1_Datos2 ${GTK3_LIBRARIES})

pkg_search_module(GST REQUIRED gstreamer-1.0  libgstvideo-1.0)

target_include_directories(Proyecto1_Datos2  PRIVATE ${GST_INCLUDE_DIRS})
target_link_libraries(Proyecto1_Datos2  ${GST_LIBRARIES})

target_link_libraries(Proyecto1_Datos2  gstvideo-1.0)
