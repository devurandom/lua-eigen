project(lua-eigen)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

include(FindPkgConfig)

set(USE_LUAJIT False CACHE BOOL "Use LuaJIT 2.0 instead of Lua 5.2")
if (USE_LUAJIT)
	pkg_check_modules(LUAJIT luajit-2.0 REQUIRED)
	set(LUA_INCLUDE_DIRS ${LUAJIT_INCLUDE_DIRS})
	set(LUA_LIBRARIES ${LUAJIT_LIBRARIES})
else ()
	pkg_check_modules(LUA lua>=5.2)
	if (NOT LUA_FOUND)
		pkg_check_modules(LUA lua5.2 REQUIRED)
	endif ()
endif ()

find_package(Eigen3 3.1 REQUIRED)

include_directories(
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/lib/lextlib
	${CMAKE_SOURCE_DIR}/lib/lunar
	${LUA_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(CXX11_ALLOW_0X False)
include(UseCXX11)

include(UseDebug)
include(UseOptimise)

add_library(luaeigen SHARED
	src/angleaxisf.cpp
	src/quaternionf.cpp

	src/matrix2f.cpp
	src/matrix3f.cpp
	src/matrix4f.cpp

	src/vector2f.cpp
	src/vector3f.cpp
	src/vector4f.cpp

	lib/lextlib/lextlib.c
)

add_library(eigen MODULE
	src/eigen.cpp
)

target_link_libraries(eigen
	luaeigen
)

set_target_properties(eigen
	PROPERTIES PREFIX ""
)
