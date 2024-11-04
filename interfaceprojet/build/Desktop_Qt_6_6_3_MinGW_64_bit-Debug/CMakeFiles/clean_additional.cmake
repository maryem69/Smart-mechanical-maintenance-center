# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\interfaceprojet_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\interfaceprojet_autogen.dir\\ParseCache.txt"
  "interfaceprojet_autogen"
  )
endif()
