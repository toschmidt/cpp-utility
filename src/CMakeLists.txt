# Header-Only Library (without source files):
add_library(cpp-utility INTERFACE)
target_include_directories(cpp-utility INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(cpp-utility INTERFACE)

# Static Library (with source files):
# file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
# add(<project-name> INTERFACE ${CPP_FILES})
# target_link_directories(<project-name> INTERFACE ${CMAKE_CURRENT_LIST_DIR}
# target_link_libraries(<project-name> PRIVATE <dependencies>)

# For more information on library definitions in cmake see https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/

if (ENABLE_INSTALL)
    include(GNUInstallDirs)

    # Install the project's header files (destination is relative to CMAKE_INSTALL_PREFIX)
    install(
            DIRECTORY ${PROJECT_SOURCE_DIR}/src/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            FILES_MATCHING PATTERN "*.hpp"
    )
endif ()
