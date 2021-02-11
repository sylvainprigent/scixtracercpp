### CMakeLists.txt --- 
##
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################
enable_testing()

project(scixtracerTest)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_MAIN_SOURCES
  TestSxData.cpp
  TestSxObject.cpp
  TestSxRequest.cpp
  TestSxRequestLocal.cpp
)

## ###################################################################
## Configure file
## ###################################################################
set(ref_rawdata_file ${PROJECT_SOURCE_DIR}/test_metadata_local/data/population1_001.md.json)
set(ref_rawdata_file1 ${PROJECT_SOURCE_DIR}/test_metadata_local/data/population1_001.md.json)
set(ref_rawdata_file2 ${PROJECT_SOURCE_DIR}/test_metadata_local/data/population1_002.md.json)
set(ref_rawdata_file3 ${PROJECT_SOURCE_DIR}/test_metadata_local/data/population1_003.md.json)
set(tst_rawdata_file ${PROJECT_SOURCE_DIR}/test_metadata_local/data/population1_001_tst.md.json)
set(ref_processeddata_file ${PROJECT_SOURCE_DIR}/test_metadata_local/process1/population1_001_o.md.json)
set(tst_processeddata_file ${PROJECT_SOURCE_DIR}/test_metadata_local/process1/population1_001_o_tst.md.json)
set(ref_processeddata2_file ${PROJECT_SOURCE_DIR}/test_metadata_local/process1/population1_002_o.md.json)
set(ref_processeddata3_file ${PROJECT_SOURCE_DIR}/test_metadata_local/process1/population1_003_o.md.json)
set(ref_dataset_file ${PROJECT_SOURCE_DIR}/test_metadata_local/data/rawdataset.md.json)
set(tst_dataset_file ${PROJECT_SOURCE_DIR}/test_metadata_local/data/rawdataset_tst.md.json)
set(ref_experiment_file ${PROJECT_SOURCE_DIR}/test_metadata_local/experiment.md.json)
set(tst_experiment_file ${PROJECT_SOURCE_DIR}/test_metadata_local/experiment_tst.md.json)
set(tst_experiment_dir ${PROJECT_SOURCE_DIR}/test_metadata_local/)

set(ref_rawdataset_file ${PROJECT_SOURCE_DIR}/test_metadata_local/data/rawdataset.md.json)
set(ref_processeddataset1_file ${PROJECT_SOURCE_DIR}/test_metadata_local/process1/processeddataset.md.json)
set(ref_processeddataset2_file ${PROJECT_SOURCE_DIR}/test_metadata_local/process2/processeddataset.md.json)

set(ref_process1_run_file ${PROJECT_SOURCE_DIR}/test_metadata_local/process1/run.md.json)
set(ref_rawdata_img_uri ${PROJECT_SOURCE_DIR}/test_metadata_local/data/population1_001.tif)
set(ref_processeddata_img_uri ${PROJECT_SOURCE_DIR}/test_metadata_local/process1/population1_001_o.tif)

set(test_images_data_dir ${PROJECT_SOURCE_DIR}/test_images/data/)

if(EXISTS ${PROJECT_SOURCE_DIR}/SxTestConfig.h.in)
  configure_file(SxTestConfig.h.in ${CMAKE_BINARY_DIR}/SxTestConfig.h)
endif()

## #################################################################
## Build rules
## #################################################################

SET(TESTS "")

foreach (test ${${PROJECT_NAME}_MAIN_SOURCES})
  get_filename_component(TName ${test} NAME_WE)

  add_executable(${TName} ${test} CreateMetadata.h CreateMetadata.cpp SxCompare.h SxCompare.cpp)
  target_link_libraries(${TName} scixtracer ${SL_LIBRARIES})

  add_test(${TName} ${EXECUTABLE_OUTPUT_PATH}/${TName})

  set(TEST ${TESTS} ${EXECUTABLE_OUTPUT_PATH}/${TName})
endforeach()

add_custom_target(testscixtracer COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${TESTS})

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################
SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Source Files" REGULAR_EXPRESSION .*\\.cpp\$)
