cmake_minimum_required(VERSION 3.2)
project(graphandtree VERSION 1.0)

file(GLOB_RECURSE GRAPHANDTREE_HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE GRAPHANDTREE_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${GRAPHANDTREE_HEADERS} ${GRAPHANDTREE_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

option(INSTALL_LIB "Installation can be made optional" ON)

if(INSTALL_LIB)
    set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${GRAPHANDTREE_HEADERS})
    
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        if(MSVC)
            install(TARGETS ${PROJECT_NAME} 
                    ARCHIVE DESTINATION lib
                    LIBRARY DESTINATION bin
                    PUBLIC_HEADER DESTINATION include)
        endif()
        if(MINGW)
            install(TARGETS ${PROJECT_NAME} 
                    ARCHIVE DESTINATION lib
                    LIBRARY DESTINATION bin
                    PUBLIC_HEADER DESTINATION include)
        endif()
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        install(TARGETS ${PROJECT_NAME} 
                LIBRARY DESTINATION lib
                PUBLIC_HEADER DESTINATION include)
    endif()
    
endif()
