cmake_minimum_required(VERSION 2.8)

project(HappyWms)

set(MYSQL_DIR_INC "/usr/local/mysql/include")
set(MYSQL_DIR_LIB "/usr/local/mysql/lib")

set(JSON_DIR_INC "/home/xuhui/TarsFramework/thirdparty")

set(util_SOURCE_DIR "/usr/local/tars/cpp")

set(TARS_PATH "/usr/local/tars/cpp")

set(TARS2CPP "/usr/local/tars/cpp/tools/tars2cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O2 -Wall -Wno-deprecated")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -Wall -Wno-deprecated")

include_directories(./)
include_directories(${MYSQL_DIR_INC})
include_directories(${JSON_DIR_INC})
include_directories(${util_SOURCE_DIR}/include)
include_directories(${servant_SOURCE_DIR})
include_directories(${util_SOURCE_DIR}/include)


link_libraries(${TARS_PATH}/lib/libtarsservant.a ${TARS_PATH}/lib/libtarsutil.a)
link_libraries(${MYSQL_DIR_LIB}/libmysqlclient.a)
link_libraries(pthread z dl rt)

macro(complice_module MODULE)

    include_directories(${PROJECT_SOURCE_DIR}/include)


    aux_source_directory(. DIR_SRCS)

    add_executable(${MODULE} ${DIR_SRCS})
    add_dependencies(${MODULE} FRAMEWORK-PROTOCOL)

endmacro()

#调用tars2cpp, 生成tars对应的文件
macro(complice_tars OUT_DEPENDS_LIST HEADER)
    set(DEPENDS_LIST)

    FILE(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.tars")

    set(CLEAN_LIST)

    #设置tars生成后, cpp文件因为h文件的include路径
    set(INCLUDE)
    if (NOT ${HEADER} STREQUAL "")
        set(INCLUDE "--header=${HEADER}")
    endif ()

    foreach (FILE ${SRC_LIST})

        get_filename_component(NAME_WE ${FILE} NAME_WE)

        # 生成tars文件
        set(TARS_IN ${FILE})
        set(TARS_H ${NAME_WE}.h)

        add_custom_command(
                OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${TARS_H}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#                DEPENDS tars2cpp
                COMMAND ${TARS2CPP} --with-tars ${INCLUDE} ${TARS_IN}
                COMMENT "${TARS2CPP} --with-tars ${INCLUDE} ${TARS_IN}")

        list(APPEND DEPENDS_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${TARS_H})

        #设置需要清除的文件
        get_filename_component(PATH ${FILE} PATH)
        list(APPEND CLEAN_LIST ${PATH}/${NAME_WE}.h)
        if (EXISTS ${PATH}/${NAME_WE}.cpp)
            list(APPEND CLEAN_LIST ${PATH}/${NAME_WE}.cpp)
        endif (EXISTS ${PATH}/${NAME_WE}.cpp)

    endforeach (FILE)

    set(OUT_DEPENDS_LIST ${DEPENDS_LIST})

    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CLEAN_LIST}")

endmacro()

add_subdirectory(protocol)
add_subdirectory(HttpServer)
add_subdirectory(HallServer)
add_subdirectory(FruitTigerServer)


set(DEPENDS_LIST)
list(APPEND DEPENDS_LIST HttpServer)
list(APPEND DEPENDS_LIST HallServer)
list(APPEND DEPENDS_LIST FruitTigerServer)

foreach (MODULE ${DEPENDS_LIST})

    #set(MODULE-TGZ "${CMAKE_BINARY_DIR}/${MODULE}-tmp.tgz")
    set(MODULE-TGZ "${CMAKE_BINARY_DIR}/${MODULE}.tgz")

    #打包脚本
    SET(RUN_DEPLOY_COMMAND_FILE "${PROJECT_BINARY_DIR}/run-deploy-${MODULE}.cmake")
    FILE(WRITE ${RUN_DEPLOY_COMMAND_FILE} "#deploy ${MODULE}-tar\n")
    FILE(APPEND ${RUN_DEPLOY_COMMAND_FILE} "EXECUTE_PROCESS(\n")
    FILE(APPEND ${RUN_DEPLOY_COMMAND_FILE} "WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/deploy/\n")
    FILE(APPEND ${RUN_DEPLOY_COMMAND_FILE} "COMMAND tar czfv ${MODULE-TGZ} ${MODULE}\n")
    #FILE(APPEND ${RUN_DEPLOY_COMMAND_FILE} "COMMAND mv ${MODULE-TGZ} ${CMAKE_BINARY_DIR}/${MODULE}.tgz\n")
    FILE(APPEND ${RUN_DEPLOY_COMMAND_FILE} ")\n")

    add_custom_command(OUTPUT ${MODULE-TGZ}
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
            COMMAND ${CMAKE_COMMAND} -P ${RUN_DEPLOY_COMMAND_FILE}
            COMMENT "call ${RUN_DEPLOY_COMMAND_FILE}")

    add_custom_target(${MODULE}-tar DEPENDS ${MODULE-TGZ} ${MODULE})
endforeach ()
