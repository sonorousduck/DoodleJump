cmake_minimum_required(VERSION 3.10)
project(DoodleJump)

#
# Specify source files
#

set(SOURCE_FILES
	main.cpp
	GameModel.cpp
	)
set(HEADER_FILES
	GameModel.hpp
	)


set(ENTITY_HEADERS
	entities/Entity.hpp
	entities/LocalPlayer.hpp
	)
set(ENTITY_SOURCES
	entities/Entity.cpp
	entities/LocalPlayer.cpp
	)


set(COMPONENTS_HEADERS
	components/Position.hpp
	components/Sprite.hpp
	components/Component.hpp
	components/Size.hpp
	components/Movement.hpp
	components/Input.hpp
	components/AudioSource.hpp
	components/Audio.hpp
	)


set(COMPONENTS_SOURCES
	)


set(SYSTEMS_HEADERS
	systems/System.hpp
	systems/Renderer.hpp
	systems/KeyboardInput.hpp
	systems/AudioSystem.hpp
	)
set(SYSTEMS_SOURCES
	systems/System.cpp
	systems/Renderer.cpp
	systems/KeyboardInput.cpp
	systems/AudioSystem.cpp
	)

set(MISC_HEADERS
	misc/ConcurrentQueue.hpp
	misc/Configuration.hpp
	misc/ConfigurationPath.hpp
	misc/Content.hpp
	misc/ContentKey.hpp
	misc/math.hpp
	misc/misc.hpp
)

set(MISC_SOURCES
	misc/Configuration.cpp
	misc/Content.cpp
	misc/math.cpp
	misc/misc.cpp
)

#
# Organize the files into logical groups
#

source_group("Main\\Header Files" FILES ${HEADER_FILES})
source_group("Main\\Source Files" FILES ${SOURCE_FILES})

source_group("Components\\Header Files" FILES ${COMPONENTS_HEADERS})
source_group("Components\\Source Files" FILES ${COMPONENTS_SOURCES})

source_group("Entities\\Header Files" FILES ${ENTITY_HEADERS})
source_group("Entities\\Source Files" FILES ${ENTITY_SOURCES})

source_group("Systems\\Header Files" FILES ${SYSTEMS_HEADERS})
source_group("Systems\\Source Files" FILES ${SYSTEMS_SOURCES})

source_group("Misc\\Header Files" FILES ${MISC_HEADERS})
source_group("Misc\\Source Files" FILES ${MISC_SOURCES})


#
# For clang-format
#

set(ALL_CODE_FILES
	${SOURCE_FILES}
	${HEADER_FILES}
	${COMPONENTS_HEADERS}
	${COMPONENTS_SOURCES}
	${ENTITY_HEADERS}
	${ENTITY_SOURCES}
	${SYSTEMS_HEADERS}
	${SYSTEMS_SOURCES}
	${MISC_HEADERS}
	${MISC_SOURCES}
	)

#
# This is the main target
#
add_executable(DoodleJump ${ALL_CODE_FILES})

#
# Doing the following so that the source code can do includes like...
# #include "components/Component.hpp"
# instead of...
# #include "../components/Component.hpp"
#
target_include_directories(DoodleJump PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#
# Want the C++ 17 standard for the project
#
set_property(TARGET DoodleJump PROPERTY CXX_STANDARD 20)

#
# Enable a lot of warnings, forcing better cod eto be written
#
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(DoodleJump PRIVATE /W4 /permissive-)
else()
	target_compile_options(DoodleJump PRIVATE -O3 -Wall -Wextra -pedantic) # -Wconversion -Wsign-conversion
endif()



#
# Move the assets into the build folder so they load at runtime (inside MSVC)
#
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/images/crow.png ${CMAKE_CURRENT_BINARY_DIR}/assets/images/crow.png COPYONLY)


#
# Move the assets into the build folder so they load at runtime
#
set(ASSETS_DIR assets)
set(ASSETS_FONT_DIR ${ASSETS_DIR}/fonts)
set(ASSETS_IMAGE_DIR ${ASSETS_DIR}/images)
set(ASSETS_AUDIO_DIR ${ASSETS_DIR}/audio)
set(ASSETS_MUSIC_DIR ${ASSETS_DIR}/music)

#
# Copy the default configuration & scores files into the build folder so they are
# available at runtime
# 
set(DEFAULT_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/client.settings.json)
set(BUILD_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/client.settings.json)
if (NOT EXISTS ${BUILD_CONFIG_FILE} OR ${DEFAULT_CONFIG_FILE} IS_NEWER_THAN ${BUILD_CONFIG_FILE})
   configure_file(${DEFAULT_CONFIG_FILE} ${BUILD_CONFIG_FILE} COPYONLY)
endif()

set(DEFAULT_SCORES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/client.scores.json)
set(BUILD_SCORES_FILE ${CMAKE_CURRENT_BINARY_DIR}/client.scores.json)
if (NOT EXISTS ${BUILD_SCORES_FILE} OR ${DEFAULT_SCORES_FILE} IS_NEWER_THAN ${BUILD_SCORES_FILE})
   configure_file(${DEFAULT_SCORES_FILE} ${BUILD_SCORES_FILE} COPYONLY)
endif()


#
# ------------------------ Add SFML ----------------------------------
#

# This causes the SFML .dll files to be copied into the Multiplayer-Step0-ECS executable folder.
# Only need this for development time, for a production release statically link
# everything together: set BUILD_SHARED_LIBS to FALSE
# Reference: https://en.sfml-dev.org/forums/index.php?topic=24070.0
# Reference: https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(ThirdParty/SFML)
include_directories(ThirdParty/SFML/include)

add_dependencies(DoodleJump sfml-graphics sfml-audio sfml-system sfml-window sfml-network)
target_link_libraries(DoodleJump sfml-graphics sfml-audio sfml-system sfml-window sfml-network)

#
# ------------------------ Add CTTI ------------------------
#

#
# Reference: https://github.com/Manu343726/ctti
add_subdirectory(ThirdParty/ctti)
include_directories(ThirdParty/ctti/include)

#
# ------------------------- Add RapidJson --------------------

add_subdirectory(ThirdParty/rapidjson)
include_directories(ThirdParty/rapidjson/include)
#


#
# ------------------------ Clang Format ------------------------
#
#
# Prepare a pre-build step to run clang-format over all the [ch]pp source files.
# Start by finding the location of the clang-format executable.
#
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    message("Clang-Format found at: " ${CLANG_FORMAT})

    #
    # Need to take the simple source file locations used for the project and get their full
    # file system locations for use in putting together the clang-format command line
    #
    unset(CODE_FILES_PATHS)
    foreach(CODE_FILE ${ALL_CODE_FILES})
        get_source_file_property(WHERE ${CODE_FILE} LOCATION)
        set(CODE_FILES_PATHS ${CODE_FILES_PATHS} ${WHERE})
    endforeach()

    #
    # This creates the clang-format target/command
    #
    add_custom_target(
        ClangFormat
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${CODE_FILES_PATHS}
    )
else()
    message("Unable to find clang-format")
endif()
