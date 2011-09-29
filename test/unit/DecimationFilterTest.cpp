/******************************************************************************
* Copyright (c) 2011, Michael P. Gerlek (mpg@flaxen.com)
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following
* conditions are met:
*
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in
*       the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of Hobu, Inc. or Flaxen Geo Consulting nor the
*       names of its contributors may be used to endorse or promote
*       products derived from this software without specific prior
*       written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
****************************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/cstdint.hpp>

#include <pdal/StageIterator.hpp>
#include <pdal/Schema.hpp>
#include <pdal/PointBuffer.hpp>
#include <pdal/SchemaLayout.hpp>
#include <pdal/drivers/faux/Reader.hpp>
#include <pdal/drivers/faux/Writer.hpp>
#include <pdal/filters/DecimationFilter.hpp>

using namespace pdal;

BOOST_AUTO_TEST_SUITE(DecimationFilterTest)

BOOST_AUTO_TEST_CASE(DecimationFilterTest_test1)
{
    Bounds<double> srcBounds(0.0, 0.0, 0.0, 100.0, 100.0, 100.0);

    pdal::drivers::faux::Reader reader(srcBounds, 1000, pdal::drivers::faux::Reader::Random);

    pdal::filters::DecimationFilter filter(reader, 10);
    BOOST_CHECK(filter.getDescription() == "Decimation Filter");
    filter.initialize();

    const Schema& schema = filter.getSchema();
    SchemaLayout schemaLayout(schema);

    PointBuffer data(schema, 3);

    StageSequentialIterator* iter = filter.createSequentialIterator();
    boost::uint32_t numRead = iter->read(data);

    BOOST_CHECK(numRead == 3);

    int offsetT = schema.getDimensionIndex(DimensionId::Time_u64);

    boost::uint64_t t0 = data.getField<boost::uint64_t>(0, offsetT);
    boost::uint64_t t1 = data.getField<boost::uint64_t>(1, offsetT);
    boost::uint64_t t2 = data.getField<boost::uint64_t>(2, offsetT);

    BOOST_CHECK(t0 == 0);
    BOOST_CHECK(t1 == 10);
    BOOST_CHECK(t2 == 20);

    delete iter;

    return;
}

BOOST_AUTO_TEST_CASE(DecimationFilterTest_test_options)
{
    Bounds<double> srcBounds(0.0, 0.0, 0.0, 100.0, 100.0, 100.0);

    pdal::drivers::faux::Reader reader(srcBounds, 1000, pdal::drivers::faux::Reader::Random);

    pdal::Option opt("step", "10");
    pdal::Options opts(opt);
    pdal::filters::DecimationFilter filter(reader, opts);
    BOOST_CHECK(filter.getDescription() == "Decimation Filter");
    filter.initialize();

    const Schema& schema = filter.getSchema();
    SchemaLayout schemaLayout(schema);

    PointBuffer data(schema, 3);

    StageSequentialIterator* iter = filter.createSequentialIterator();
    boost::uint32_t numRead = iter->read(data);

    BOOST_CHECK(numRead == 3);

    int offsetT = schema.getDimensionIndex(DimensionId::Time_u64);

    boost::uint64_t t0 = data.getField<boost::uint64_t>(0, offsetT);
    boost::uint64_t t1 = data.getField<boost::uint64_t>(1, offsetT);
    boost::uint64_t t2 = data.getField<boost::uint64_t>(2, offsetT);

    BOOST_CHECK(t0 == 0);
    BOOST_CHECK(t1 == 10);
    BOOST_CHECK(t2 == 20);

    delete iter;

    return;
}


BOOST_AUTO_TEST_SUITE_END()
