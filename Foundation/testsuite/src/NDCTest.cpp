//
// NDCTest.cpp
//
// $Id: //poco/1.4/Foundation/testsuite/src/NDCTest.cpp#1 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "NDCTest.h"
#include "Poco/CppUnit/TestCaller.h"
#include "Poco/CppUnit/TestSuite.h"
#include "Poco/NestedDiagnosticContext.h"
#include <iostream>


using Poco::NDC;


NDCTest::NDCTest(const std::string& rName): CppUnit::TestCase(rName)
{
}


NDCTest::~NDCTest()
{
}


void NDCTest::testNDC()
{
	NDC ndc;
	assert (ndc.depth() == 0);
	ndc.push("item1");
	assert (ndc.toString() == "item1");
	assert (ndc.depth() == 1);
	ndc.push("item2");
	assert (ndc.toString() == "item1:item2");
	assert (ndc.depth() == 2);
	ndc.pop();
	assert (ndc.depth() == 1);
	assert (ndc.toString() == "item1");
	ndc.pop();
	assert (ndc.depth() == 0);
}


void NDCTest::testNDCScope()
{
	Poco::NDCScope item1("item1", __LINE__, __FILE__);
	assert (NDC::current().depth() == 1);
	{
		Poco::NDCScope item2("item2", __LINE__, __FILE__);
		assert (NDC::current().depth() == 2);
		{
			Poco::NDCScope item3("item3", __LINE__, __FILE__);
			assert (NDC::current().depth() == 3);
			NDC::current().dump(std::cout);
		}
		assert (NDC::current().depth() == 2);
	}
	assert (NDC::current().depth() == 1);
}


void NDCTest::setUp()
{
}


void NDCTest::tearDown()
{
}


CppUnit::Test* NDCTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("NDCTest");

	CppUnit_addTest(pSuite, NDCTest, testNDC);
	CppUnit_addTest(pSuite, NDCTest, testNDCScope);

	return pSuite;
}
