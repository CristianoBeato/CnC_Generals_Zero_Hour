##############################################
##	Beato Command & Conquer Generals(tm)    ##
##############################################

cmake_minimum_required( VERSION 3.16 )
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

#########################
##    Project Name     ##
#########################
project( " Command & Conquer Generals(tm) " )

## STD 17
set( CMAKE_CXX_STANDARD 17 )

############################
##    Project Options     ##
############################


############################
##  Build Configuration   ##
############################
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
	
	add_compile_options(-pipe)
	add_compile_options(-fPIC)
	#add_compile_options(-Wall)
	#add_compile_options( -Wunknown-pragmas )

	set(CMAKE_C_FLAGS_DEBUG "-g -ggdb -D_DEBUG -O0")
	set(CMAKE_C_FLAGS_DEBUGALL "-g -ggdb -D_DEBUG")
	set(CMAKE_C_FLAGS_PROFILE "-g -ggdb -D_DEBUG -O2 -fno-omit-frame-pointer -Wunknown-pragmas")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -fno-math-errno -fno-trapping-math -fomit-frame-pointer")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g -ggdb -O2 -fno-math-errno -fno-trapping-math -fno-omit-frame-pointer")
	set(CMAKE_C_FLAGS_MINSIZEREL "-Os -fno-math-errno -fno-trapping-math -fomit-frame-pointer")

	set(CMAKE_CXX_FLAGS_DEBUGALL ${CMAKE_C_FLAGS_DEBUGALL})
	set(CMAKE_CXX_FLAGS_PROFILE ${CMAKE_C_FLAGS_PROFILE})
else()
	message(FATAL_ERROR "Unsupported compiler")
endif()

###########################
##   	 Libraries     	 ##
###########################
find_package( OpenAL REQUIRED )
find_package( SDL3 REQUIRED )
include_directories( ${SDL3_INCLUDE_DIR} )
#find_package( OGG REQUIRED )
#find_package( VORBIS REQUIRED )
#include_directories( ${OGG_INCLUDE_DIR} )

###########################
##	    Engine Sources	 ##
###########################

# base directories 
include_directories( ${CMAKE_SOURCE_DIR}/Libraries/Include 
					 ${CMAKE_SOURCE_DIR}/Libraries/Source/WWVegas
					 ${CMAKE_SOURCE_DIR}/GameEngine/Include 
					 ${CMAKE_SOURCE_DIR}/GameEngineDevice/Include )

add_subdirectory( GameEngineDevice )

set( BEATO_CEC_SOURCES 
    ${CMAKE_SOURCE_DIR}/Main/WinMain.cpp
    ${CMAKE_SOURCE_DIR}/Main/WinMain.h
    ${CMAKE_SOURCE_DIR}/Main/SDLMain.cpp
    ${CMAKE_SOURCE_DIR}/Main/SDLMain.h
    )

set( ENGINE_SOURCES_ALL 
	${BEATO_CEC_SOURCES}
	)

set( ENGINE_LIBS_ALL )



add_executable( bCeC_Generals WIN32 ${ENGINE_SOURCES_ALL} )
set_target_properties( bCeC_Generals PROPERTIES COMPILE_DEFINITIONS "_MBCS;_DEBUG")
add_dependencies( bCeC_Generals GameEngineDevice )
target_link_libraries( bCeC_Generals ${ENGINE_LIBS_ALL} )

#target_precompile_headers( bCeC_Generals
#	PUBLIC
#		${CMAKE_SOURCE_DIR}/idlib/precompiled.h
#	PRIVATE
#		"$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/sys/sys_local.h>"
#		"$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/sys/sys_public.h>"
#		"$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/framework/Common.h>"
#		"$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/renderer/renderer_common.h>"
#		"$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/sound/sound.h>"
#		)