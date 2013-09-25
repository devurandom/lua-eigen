project(lua-eigen)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	${CMAKE_CURRENT_SOURCE_DIR}/cmake
)


find_package(Eigen3 3.1 REQUIRED)

include(FindPkgConfig)

set(USE_LUAJIT False CACHE BOOL "Build against LuaJIT 2.0 instead of Lua 5.2")
if (USE_LUAJIT)
	pkg_check_modules(LUAJIT luajit>=2.0)
	if (NOT LUAJIT_FOUND)
		pkg_check_modules(LUAJIT luajit-2.0>=2.0)
		if (NOT LUAJIT_FOUND)
			if (LUAJIT_INCLUDE_DIRS AND LUAJIT_LIBRARIES)
				find_package_message(LUAJIT "Using local LuaJIT ..." "[${LUAJIT_INCLUDE_DIRS}][${LUAJIT_LIBRARIES}]")
			else ()
				message(FATAL_ERROR "Please provide a local LuaJIT")
			endif ()
		endif ()
	endif ()
	set(LUA_INCLUDE_DIRS ${LUAJIT_INCLUDE_DIRS})
	set(LUA_LIBRARIES ${LUAJIT_LIBRARIES})
	add_definitions(-DHAVE_LUAJIT)
else ()
	pkg_check_modules(LUA lua>=5.2)
	if (NOT LUA_FOUND)
		pkg_check_modules(LUA lua5.2 REQUIRED)
	endif ()
endif ()

if (LEXTLIB_INCLUDE_DIRS AND LEXTLIB_LIBRARIES)
	find_package_message(LEXTLIB "Using local lextlib ..." "[${LEXTLIB_INCLUDE_DIRS}][${LEXTLIB_LIBRARIES}]")
else ()
	message(FATAL_ERROR "Please provide a local lextlib")
endif ()

if (LUNAR_INCLUDE_DIRS)
	find_package_message(LUNAR "Using local Lunar ..." "[${LUNAR_INCLUDE_DIRS}]")
else ()
	message(FATAL_ERROR "Please provide a local Lunar")
endif ()


include_directories(
	${CMAKE_SOURCE_DIR}/src
	${LUA_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
	${LEXTLIB_INCLUDE_DIRS}
	${LUNAR_INCLUDE_DIRS}
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-error=unused-local-typedefs")

set(CXX11_ALLOW_0X False)
include(UseCXX11)

include(UseDebug)
include(UseOptimise)

add_library(eigen MODULE
	src/eigen.cpp
	src/util.cpp

	src/angleaxisf.cpp
	src/quaternionf.cpp

	src/matrix.cpp
)

target_link_libraries(eigen
	${LEXTLIB_LIBRARIES}
)
set_target_properties(eigen
	PROPERTIES PREFIX ""
)
