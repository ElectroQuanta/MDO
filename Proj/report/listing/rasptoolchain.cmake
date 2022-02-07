SET(CMAKE_SYSTEM_NAME Linux)

set(HOME /home/zmpl)
set(BUILDROOT_DIR "${HOME}/OneDrive-UM/Univ/MI_Electro/Sem7/SEC/2021-22/Buildroot/buildroot-2021.08.1")
set(HOST_PATH ${BUILDROOT_DIR}/output/host)
set(TOOLCHAIN_PATH ${HOST_PATH}/bin)

SET(TOOLS_PREFIX aarch64-buildroot-linux-gnu)

# Define the cross compiler locations
SET(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/${TOOLS_PREFIX}-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/${TOOLS_PREFIX}-g++)

# Define the sysroot path for the RaspberryPi distribution in our tools folder 
SET(CMAKE_FIND_ROOT_PATH ${HOST_PATH}/${TOOLS_PREFIX}/sysroot)

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
