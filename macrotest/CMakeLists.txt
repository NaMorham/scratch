cmake_minimum_required (VERSION 2.6)

# Maps to a solution file (Tutorial.sln). The solution will 
# have all targets (exe, lib, dll) as projects (.vcproj)
project (MacroTest)

if( MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++11" )
else ( MSVC )
    set( CMAKE_CXX_STANDARD 14 )
    set( CMAKE_CXX_STANDARD_REQUIRED ON )
    set( CMAKE_CXX_EXTENSIONS OFF ) # -std=c++11 instead of -std=gnu++11
endif( MSVC )

set ( OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build )

set( Cmake_Runtime_Output_Directory_Debug   "${OUTPUT_DIRECTORY}/bin/Debug")
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}/bin/Release")
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIRECTORY}/lib/Debug")
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}/lib/Release")
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${OUTPUT_DIRECTORY}/archive/Debug")
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}/archive/Release")


# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

# Command to output information to the console
# Useful for displaying errors, warnings, and debugging
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

# Sub-directories where more CMakeLists.txt exist
#add_subdirectory(app)
#add_subdirectory (math)

set( SRCS 
    macro_test/console_display.cpp
    macro_test/macro_test.cpp
    macro_test/mcs_logger.cpp
    macro_test/test_method_base.cpp
)

set ( HDRS 
    macro_test/console_display.h
    macro_test/mcs_logger.h
    macro_test/test_method_base.h
)

source_group("source" FILES ${SRCS} )

source_group("headers" FILES ${HDRS} )

add_executable( macrotest ${SRCS} ${HDRS} )



# Turn on CMake testing capabilities
enable_testing()

# Add test cases
#add_test(AppTest1 ${PROJECT_BINARY_DIR}/bin/app 100)
#add_test(AppTest2 ${PROJECT_BINARY_DIR}/bin/app 200)
#add_test(AppTest3 ${PROJECT_BINARY_DIR}/bin/app 300)
