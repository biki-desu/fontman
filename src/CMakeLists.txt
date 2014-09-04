########################################################################
## Name:        src/CMakeLists.txt
## Purpose:     Build system
## Author:      biki-desu
## Modified by: biki-desu
## Created:     2014/09/01
## Copyright:   (c) biki-desu
## Licence:     GPLv2
########################################################################

include_directories(${PROJECT_SOURCE_DIR} ${wxWidgets_INCLUDE_DIRS} )

set(fm_SOURCES
	app.cpp
	frame.cpp
)

if(WIN32)
	set(fm_SOURCES ${fm_SOURCES} fontman.rc)
endif(WIN32)

add_executable(${PROJECT_NAME} WIN32 ${fm_SOURCES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
