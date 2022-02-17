#File raspberrytoolchain.cmake for ROS and system packages to cross compile.
SET(CMAKE_SYSTEM_NAME Linux)

set(HOME /home/zmpl)
set(BUILDROOT_DIR "${HOME}/OneDrive-UM/Univ/MI_Electro/Sem7/SEC/2021-22/Buildroot/buildroot-2021.11.1")
set(HOST_PATH ${BUILDROOT_DIR}/output/host)
set(TOOLCHAIN_PATH ${HOST_PATH}/bin)

#If you have installed cross compiler to somewhere else, please specify that path.
#SET(COMPILER_ROOT ${TOOLCHAIN_PATH}) 

#SET(TOOLS_PREFIX aarch64-buildroot-linux-gnu)
#SET(TOOLS_PREFIX arm-buildroot-linux-uclibcgnueabihf)
SET(TOOLS_PREFIX arm-buildroot-linux-gnueabihf)

#SET (CMAKE_C_COMPILER_WORKS 1)
#SET (CMAKE_CXX_COMPILER_WORKS 1)

# Define the cross compiler locations
SET(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/${TOOLS_PREFIX}-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/${TOOLS_PREFIX}-g++)
# Define the sysroot path for the RaspberryPi distribution in our tools folder

SET(CMAKE_FIND_ROOT_PATH ${HOST_PATH}/${TOOLS_PREFIX}/sysroot)

#set(OpenCV_DIR "/usr/local/lib/cmake/opencv4")
#aarch64-buildroot-linux-gnu/sysroot/usr/lib/cmake/opencv4/


#message("Buildroot_DIR:" ${BUILDROOT_DIR})
#message("B_DIR:" ${BUILDROOT_DIR})

# Below call is necessary to avoid non-RT problem.
#SET(CMAKE_LIBRARY_ARCHITECTURE arm-linux-gnueabihf)

#If you have installed cross compiler to somewhere else, please specify that path.
#SET(COMPILER_ROOT /usr/arm-linux-gnueabihf) 

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#SET(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

