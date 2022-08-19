cmake_minimum_required(VERSION 3.10)
project(Shootout)

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
	)
set(COMPONENTS_SOURCES
	)


set(SYSTEMS_HEADERS
	systems/System.hpp
	systems/Renderer.hpp
	systems/KeyboardInput.hpp
	)
set(SYSTEMS_SOURCES
	systems/System.cpp
	systems/Renderer.cpp
	systems/KeyboardInput.cpp
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
	)

#
# This is the main target
#
add_executable(Shootout ${ALL_CODE_FILES})

#
# Doing the following so that the source code can do includes like...
# #include "components/Component.hpp"
# instead of...
# #include "../components/Component.hpp"
#
target_include_directories(Shootout PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#
# Want the C++ 17 standard for the project
#
set_property(TARGET Shootout PROPERTY CXX_STANDARD 17)

#
# Enable a lot of warnings, forcing better cod eto be written
#
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(Shootout PRIVATE /W4 /permissive-)
else()
	target_compile_options(Shootout PRIVATE -O3 -Wall -Wextra -pedantic) # -Wconversion -Wsign-conversion
endif()



#
# Move the assets into the build folder so they load at runtime (inside MSVC)
#
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/crow.png ${CMAKE_CURRENT_BINARY_DIR}/assets/crow.png COPYONLY)



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

add_subdirectory(SFML)
include_directories(SFML/include)

add_dependencies(Shootout sfml-graphics sfml-audio sfml-system sfml-window sfml-network)
target_link_libraries(Shootout sfml-graphics sfml-audio sfml-system sfml-window sfml-network)

#
# ------------------------ Add CTTI ------------------------
#

#
# Reference: https://github.com/Manu343726/ctti
add_subdirectory(ctti)
include_directories(ctti/include)


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
