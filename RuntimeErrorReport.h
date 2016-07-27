/* 
 * File:   BadConversion.h
 * Author: brian
 *
 * Created on July 5, 2015, 10:49 AM
 */

#ifndef BADCONVERSION_H
#define	BADCONVERSION_H

#include <stdexcept>
#include <iostream>
#include <exception>

namespace glch{

    class RuntimeErrorReport : public std::runtime_error {
    public:
        /**
         * Used to report various runtime errors.
         * @param aErrorString Error string for outputting error.
         */
        RuntimeErrorReport(std::string const& aErrorString) : std::runtime_error(aErrorString){};
    };

}

#endif	/* BADCONVERSION_H */

