/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Validate.cpp
 * Author: brian
 *
 * Created on Jul 16, 2018, 11:50:18 AM
 */

#include "Validate.h"


CPPUNIT_TEST_SUITE_REGISTRATION(Validate);

Validate::Validate() {
}

Validate::~Validate() {
}

void Validate::setUp() {
}

void Validate::tearDown() {
}

void Validate::testMethod() {
    CPPUNIT_ASSERT(true);
}

void Validate::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}

