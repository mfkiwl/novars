CMAKE_MINIMUM_REQUIRED (VERSION 2.8.11)

PROJECT (NOVARS CXX)

SET (NOVARS        "NovaRS"      CACHE STRING "Name of the executeable")

SET (DESTDIR)

SET ( NOVARS_SOURCES 
                ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/typedefs.h
                ${CMAKE_CURRENT_SOURCE_DIR}/StringUtils.h
                ${CMAKE_CURRENT_SOURCE_DIR}/date.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/ncrc32.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/OemHeader.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/OemLog.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/OemRangecmp.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/OemRange.cpp
 )

set ( DOCS
		${CMAKE_CURRENT_SOURCE_DIR}/HOWTO/Connecting_NovAtel_receiver_via_USB.txt.gz
		${CMAKE_CURRENT_SOURCE_DIR}/README
		${CMAKE_CURRENT_SOURCE_DIR}/TODO
		${CMAKE_CURRENT_SOURCE_DIR}/COPYING
		${CMAKE_CURRENT_SOURCE_DIR}/debian/changelog
)


CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)


ADD_EXECUTABLE( ${NOVARS}  ${NOVARS_SOURCES})

target_link_libraries(${NOVARS} ${LIBS})


## Add uninstall item
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
      
ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
## end uninstall target adding


# Install daemon
INSTALL (TARGETS ${NOVARS} RUNTIME DESTINATION /usr/sbin)
## Install configfile
INSTALL(FILES NovaRS.config DESTINATION /etc/NovaRS)
## Install docs
##INSTALL (FILES DOCS DESTINATION /usr/share/doc)
