# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\NewGame_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\NewGame_autogen.dir\\ParseCache.txt"
  "NewGame_autogen"
  )
endif()
