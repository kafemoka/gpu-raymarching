function(include_recursive_dirs HEADERS_PATH)
    file(GLOB_RECURSE FOUND_HEADERS ${HEADERS_PATH})

    set(INCLUDE_DIRS "")
    foreach(_headerFile ${FOUND_HEADERS})
        get_filename_component(_dir ${_headerFile} PATH)
        list(APPEND INCLUDE_DIRS ${_dir})
    endforeach()
    list(REMOVE_DUPLICATES INCLUDE_DIRS)

    include_directories(${INCLUDE_DIRS})

    set(HEADERS
        ${HEADERS}
        ${FOUND_HEADERS}
        CACHE INTERNAL "headers" FORCE)
    list(REMOVE_DUPLICATES HEADERS)
endfunction(include_recursive_dirs)

macro(group_recursive_sources CURDIR CURGROUP)
    file(GLOB children ${CURDIR}/*)

    foreach(child ${children})
        if(IS_DIRECTORY ${child})
            file(GLOB FOUND_HEADERS ${child}/*.h)
            file(GLOB FOUND_SOURCES ${child}/*.cpp)
            string(REGEX MATCH "([^/]+)$" group ${child})

            if("${CURGROUP}" STREQUAL "")
                source_group(${group} FILES ${FOUND_HEADERS} ${FOUND_SOURCES})
            else()
                source_group(${CURGROUP}\\${group} FILES ${FOUND_HEADERS} ${FOUND_SOURCES})
                set(group ${CURGROUP}\\\\${group})
            endif()

            group_recursive_sources(${child} ${group})
        endif()
    endforeach()

    # add files from top level group
    file(GLOB FOUND_HEADERS ${CURGROUP}/*.h)
    file(GLOB FOUND_SOURCES ${CURGROUP}/*.cpp)
    source_group(${CURGROUP} FILES ${FOUND_HEADERS} ${FOUND_SOURCES})
endmacro()
