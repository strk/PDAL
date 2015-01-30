set(srcs PassthroughFilter.cpp)
set(incs PassthroughFilter.hpp)

PDAL_ADD_DRIVER(filter passthrough "${srcs}" "${incs}" objects)
set(PDAL_TARGET_OBJECTS ${PDAL_TARGET_OBJECTS} ${objects} PARENT_SCOPE)
