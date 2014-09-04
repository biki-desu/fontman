########################################################################
## Name:        CMakeLists.txt
## Purpose:     Build system
## Author:      biki-desu
## Modified by: biki-desu
## Created:     2014/09/01
## Copyright:   (c) biki-desu
## Licence:     GPLv2
########################################################################

cmake_minimum_required(VERSION 2.6) 
project(fontman)

message("-------------------------")

# set version
set(fm_VERSION_MAJOR 0)
set(fm_VERSION_MINOR 0)
set(fm_VERSION_RELEASE 1)
execute_process(COMMAND ${PROJECT_SOURCE_DIR}/version.sh WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	OUTPUT_VARIABLE fm_VERSION_GITREV OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(fm_VERSION "${fm_VERSION_MAJOR}.${fm_VERSION_MINOR}.${fm_VERSION_RELEASE}${fm_VERSION_GITREV}")
add_definitions("-DFM_VERSION=\"${fm_VERSION}\"")
message("-- ${PROJECT_NAME} version: ${fm_VERSION}.")

# wxWidgets
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base adv gl REQUIRED)
if(wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})
else()
	message("wxWidgets not found!")
endif()

# debug
option(ENABLE_DEBUG "Enable debug options~" ON)
if(ENABLE_DEBUG)
	add_definitions("-DFM_DEBUG -g -Og -Wall -Wextra -pedantic -std=c++0x")
	message("-- Enable debug: yes.")
else()
	add_definitions("-Wwarning -pedantic -std=c++0x")
	message("-- Enable debug: no.")
endif()

# set a easily changable program name
add_definitions("-DFM_NAME=\"${PROJECT_NAME}\"")

message("-------------------------")

# add src
add_subdirectory(src)