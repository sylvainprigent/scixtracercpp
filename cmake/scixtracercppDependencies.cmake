############################################################
#
# $Id$
#
# Copyright (c) scixtracercpp 2020
#
# AUTHOR:
# Sylvain Prigent
# 

## #################################################################
## Qt
## #################################################################
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(Threads REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)

set (SL_LIBRARIES ${SL_LIBRARIES} Qt6::Core)


## #################################################################
## Doxygen
## #################################################################

find_package(Doxygen QUIET)
if(${DOXYGEN_FOUND})
  set(scixtracer_USE_DOXYGEN 1)
endif(${DOXYGEN_FOUND})

if(${SL_USE_OPENMP})
  find_package(OpenMP REQUIRED)
endif(${SL_USE_OPENMP})  
 
