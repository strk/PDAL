#
# PgPointCloud plugin CMake configuration
#

include(${PDAL_CMAKE_DIR}/postgres.cmake)

#
# PgPointCloud Reader
#
set(srcs io/PgReader.cpp)
set(incs
    io/PgCommon.hpp
    io/PgReader.hpp
)

PDAL_ADD_PLUGIN(reader_libname reader pgpointcloud
    FILES "${srcs}" "${incs}"
    LINK_WITH ${POSTGRESQL_LIBRARIES})

#
# PgPointCloud Writer
#
set(srcs io/PgWriter.cpp)
set(incs
    io/PgCommon.hpp
    io/PgWriter.hpp
)

PDAL_ADD_PLUGIN(writer_libname writer pgpointcloud
    FILES "${srcs}" "${incs}"
    LINK_WITH ${POSTGRESQL_LIBRARIES})

#
# PgPointCloud tests
#
if (BUILD_PGPOINTCLOUD_TESTS)
	set(PGPOINTCLOUD_TEST_DB_HOST localhost CACHE STRING
            "Postgres test database host")
	set(PGPOINTCLOUD_TEST_DB_PORT 5432 CACHE STRING
            "Postgres test database port")
	set(PGPOINTCLOUD_TEST_DB_NAME pdal_test CACHE STRING
            "Postgres test database name, must exist and must be able to create databases")
	set(PGPOINTCLOUD_TEST_DB_TEMPNAME pdal_test_tmp CACHE STRING
            "Postgres test database temp database name")

	configure_file(
        test/Pgtest-Support.hpp.in
        ${CMAKE_CURRENT_BINARY_DIR}/Pgtest-Support.hpp
    )

    set(srcs
        test/PgpointcloudWriterTest.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/Pgtest-Support.hpp
    )

    include_directories(${CMAKE_CURRENT_BINARY_DIR})

	PDAL_ADD_TEST(pgpointcloudtest
        FILES "${srcs}"
        LINK_WITH ${reader_libname} ${writer_libname})
endif()
