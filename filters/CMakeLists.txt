add_subdirectory(chipper)
add_subdirectory(colorization)
add_subdirectory(crop)
add_subdirectory(decimation)
add_subdirectory(ferry)
add_subdirectory(merge)
add_subdirectory(mortonorder)
add_subdirectory(reprojection)
add_subdirectory(sort)
add_subdirectory(splitter)
add_subdirectory(stats)
add_subdirectory(transformation)

set(PDAL_TARGET_OBJECTS ${PDAL_TARGET_OBJECTS} PARENT_SCOPE)
