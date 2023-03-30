# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/mapgui_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/mapgui_autogen.dir/ParseCache.txt"
  "mapgui_autogen"
  )
endif()
