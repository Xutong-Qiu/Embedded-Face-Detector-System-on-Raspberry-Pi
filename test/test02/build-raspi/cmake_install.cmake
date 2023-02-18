# Install script for directory: /homes/x/q/xqiu1234/home/enee408m/team1/test/test02

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/homes/x/q/xqiu1234/home/enee408m/pkuser/dice_user/tmp/driver.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/homes/x/q/xqiu1234/home/enee408m/pkuser/dice_user/tmp/driver.exe")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/homes/x/q/xqiu1234/home/enee408m/pkuser/dice_user/tmp/driver.exe"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/homes/x/q/xqiu1234/home/enee408m/pkuser/dice_user/tmp/driver.exe")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/homes/x/q/xqiu1234/home/enee408m/pkuser/dice_user/tmp" TYPE EXECUTABLE FILES "/homes/x/q/xqiu1234/home/enee408m/team1/test/test02/build-raspi/driver.exe")
  if(EXISTS "$ENV{DESTDIR}/homes/x/q/xqiu1234/home/enee408m/pkuser/dice_user/tmp/driver.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/homes/x/q/xqiu1234/home/enee408m/pkuser/dice_user/tmp/driver.exe")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/homes/x/q/xqiu1234/home/enee408m/pkuser/dice_user/tmp/driver.exe"
         OLD_RPATH "/dept/enee/software/dspcad/common/welter/weltergen_rpi:/homes/x/q/xqiu1234/home/enee408m/pkuser/dice_user/tmp:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/dept/enee/software/dspcad/enee408m/raspi-tools/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-strip" "$ENV{DESTDIR}/homes/x/q/xqiu1234/home/enee408m/pkuser/dice_user/tmp/driver.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/homes/x/q/xqiu1234/home/enee408m/team1/test/test02/build-raspi/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
