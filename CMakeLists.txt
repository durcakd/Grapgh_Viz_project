cmake_minimum_required(VERSION 2.8)
set( PROJECT_NAME GraphViz )
project( ${PROJECT_NAME})



# Install destinations
set( CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/_install CACHE PATH "Installation Destination" FORCE)
SET( INSTALL_DES ./ CACHE PATH "Where to install to." )

# Release is default
if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE ) #MinSizeRel
endif()
message("CMAKE_BUILD_TYPE  ::" ${CMAKE_BUILD_TYPE})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)



### Qt4
find_package(Qt4 REQUIRED)


# autogenerate all moc files
set( CMAKE_AUTOMOC TRUE )
add_definitions(${QT_DEFINITIONS})
set(QT_USE_QMAIN true)
SET(QT_USE_QTOPENGL TRUE)
include(${QT_USE_FILE})

# ============================================
### Source files

file(GLOB SRC_EDITOR	"src/*.cpp")
file(GLOB INCL_EDITOR	"include/*.h")

set(SRC		${SRC_EDITOR})
set(INCL	${INCL_EDITOR})

message("SRC  ::" ${SRC})
message("INCL ::" ${INCL})

include_directories( ${CMAKE_CURRENT_BINARY_DIR}
                     ${CMAKE_CURRENT_SOURCE_DIR}
                     ${CMAKE_CURRENT_SOURCE_DIR}/include
                    )




message("add_executable of ::" ${PROJECT_NAME})


set( SRCS 	${INCL}
            ${SRC})
add_executable(${PROJECT_NAME} ${SRCS} )

target_link_libraries( ${PROJECT_NAME}
    ${QT_LIBRARIES}
    ${QT_QTMAIN_LIBRARY}
)

#aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST})



# =============================================
### install

INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${INSTALL_DES} COMPONENT Runtime )
