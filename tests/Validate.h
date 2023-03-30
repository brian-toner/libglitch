/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Validate.h
 * Author: brian
 *
 * Created on Jul 16, 2018, 11:50:18 AM
 */

#ifndef VALIDATE_H
#define VALIDATE_H

#include <cppunit/extensions/HelperMacros.h>

class Validate : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(Validate);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    Validate();
    virtual ~Validate();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif /* VALIDATE_H */

