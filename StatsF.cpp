#include "StatsF.h"

namespace glch{

/**
 * Calculates the average by taking Sum of argData[i], from 0 to argSize and dividing
 * that sum by argSize. 
 * <br>
 * mu = (1/n) ∑((x_i) | i=1 to n)
 *
 * @param argData -Array of doubles we want to find the mean of.
 * @param argSize -Integer that indicates how many elements argData contains.
 * @return Returns a double that represents the mean.
 */
double calc_average(double *argData, long unsigned int argSize){
    long unsigned int i;
    double locAverage;
    locAverage = 0;

    for(i=0; i < argSize; i++){
        locAverage = locAverage + argData[i];
    }

    locAverage = locAverage/argSize;
    return locAverage;
}



/**
 * Calculates the average of an ordered set of pairs.
 * <br>
 * mu = (1/n) ∑((x_i) | i=1 to n)
 *
 * @param argBegin -Begin of vector of points.
 * @param argEnd -End of vector of points.
 * @return Returns a PointF that represents the mean.
 */
PointF calc_average_pt(vector<PointF>::iterator argBegin, vector<PointF>::iterator argEnd){
    PointF locAverage = PointF(0,0);
    
    long unsigned int locSize = argEnd-argBegin;
    
    for(vector<PointF>::iterator it = argBegin; it != argEnd; it++){
        locAverage.x += (*it).x/(double)locSize;
        locAverage.y += (*it).y/(double)locSize;
    }
    
    return locAverage;
}


/**
 * CalcVariance(double, int) - Calculates the variance of a double array.  
 * This is accomplished by: Sum (x_i-mu)^2, from 0 to argSize, and dividing that sum by argSize.
 * <br>
 * Var = ∑((x_i-mu)^2 | i=1 to n)
 * 
 * @param argData -Array of doubles we want to find the variance of.
 * @param argSize -Integer that indicates how many elements argData contains.
 * @return Returns a double that represents the variance.
 */
long double calc_variance(double *argData, long unsigned int argSize){
    long unsigned int i;
    std::vector<double> locCalcVar(argSize,0);
    double locAverage = calc_average(argData, argSize);
    long double locResults;
    locResults = 0;

    for(i=0;i<argSize;i++){
        locCalcVar[i] = (argData[i] - locAverage)*(argData[i] - locAverage);
        locResults = locResults + locCalcVar[i];
    }

    locResults = locResults/(argSize-1);

    return locResults;

}

/**
 * Calculates standard deviation of a double array.  This is accomplished by
 * sqrt(Variance)
 * @param argData -Array of doubles we want to find the standard deviation of.
 * @param argSize -Integer that indicates how many elements argData contains.
 * @return Returns a double that represents the standard deviation.
 */
double calc_std_dev(double *argData, long unsigned int argSize){
    double locVariance;
    locVariance = sqrt(calc_variance(argData, argSize));

    return locVariance;
}

/**
 * Uses sort in algorithm library to sort a double array contained in argData. Probably note useful...
 * @param argData -Double array that contains the data that needs to be sorted.
 * @param argDest - Double pointer of same size argData that will be the destination of the function.
 * @param argSize -Integer representing the number of elements in argData.
 * @return  Returns a new double array with the sorted data with argSize elements.
 */
void sort_data_f(double *argSource, double *argDest, long unsigned int argSize){
    long unsigned int i;
    
    //Copies the source to the destination.
    for(i=0; i<argSize; i++){
        argDest[i] = argSource[i];
    }

    //Sorts the destination container.
    sort(argDest, argDest+argSize);

}


/**
 * Ranks a SORTED double array.  Where 1,2,2,3,4 would be ranked as 1,2.5,2.5,4,5
 * and 1,2,2,2,3 would be ranked as 1,3,3,3,5 OR 1/1,(2+3+4)/3,(2+3+4)/3,(2+3+4)/3,5/1
 * @param argSortedData -Sorted double array to be ranked.
 * @param argDest - Double pointer of same size argSortedData that will be the destination of the function.
 * @param argSize -Number of elements in argSortedData.
 * @return Returns a new double array with the ranked data. 
 */
void rank_data(double *argData, double *argDest, long unsigned int argSize){
    double locCurrentData;
    double *locTempData = argDest;
    long unsigned int i,j,k;
    long unsigned int locCount;
    double locAverageRank;


    for(i=0; i<argSize; i++){
        locCurrentData = argData[i];
        locCount = 0;

        //Starts at i, and breaks for after finding first non-matching number, no need to go through
        //The entire array, would be just a waste of cycles
        for(j=i; j<argSize; j++){

            //Counts the number of times locCurrentData appears, should appear at least once, counts self.
            if(locCurrentData == argData[j]){
                locCount ++;
                //cout << j << endl;
            } else {
                break;
            }
        }

        //Reinitializes locAverageRank after each run.
        locAverageRank = 0;

        //Because this is sorted we are adding up the successive matching numbers
        for(k=0;k<locCount;k++){
            locAverageRank = locAverageRank+i+k+1;
        }
        locAverageRank = locAverageRank/locCount;

        for(k=0;k<locCount;k++){
            locTempData[i+k] = locAverageRank;
        }

        //Jumps ahead to next i value
        i = i+k-1;
    }

}

/**
 * Calculates ranked probability by (argRank[i] -.5)/argSize.  Should only be used with
 * a double array that has been ranked.
 * @param argRank -Double array containing ranked data
 * @param argDest - Double pointer of same size argRank that will be the destination of the function.
 * @param argSize -Number of elements in argRank.
 * @return Returns a double array containing the ranked probabilities of size argSize.
 */
void calc_ranked_prob_i(double *argData, double *argDest, long unsigned int argSize){
    long unsigned int i;

    double *locTempData = argDest;

    for(i = 0; i < argSize; i++){
        locTempData[i] = (argData[i] -.5)/argSize;
    }

}

/**
 * Calculates out individual z scores in argData using the algorithms developed by
 * Gary Perlman.  Using calc_q.
 * @param argData -Should be a ranked probability.
 * @param argDest - Double pointer of same size argData that will be the destination of the function.
 * @param argSize -Size of argData 
 * @return  -Returns the inversenorm(p_i)
 */
void calc_ranked_z(double *argData, double *argDest, long unsigned int argSize){
    long unsigned int i;

    double *locTempData = argDest;

    for(i = 0; i < argSize; i++){
        locTempData[i] = calc_q(argData[i]);
    }

}

void calc_prob_from_z(double *argData, double *argDest, long unsigned int argSize){
     long unsigned int i;

    double *locTempData = argDest;

    for(i = 0; i < argSize; i++){
        locTempData[i] = calc_z(argData[i]);
    }
    
}

/**
 * Calculates Z score by (x_i - mu)/sigma
 * @param argData -Double array that contains the data that Z Scores will be calculated from.
 * @param argDest - Double pointer of same size argData that will be the destination of the function.
 * @param argSize -Integer representing the number of elements in argRankedProbI.
 * @return Returns a double array containing Z Scores calculated form argData 
 */
void calc_z_score(double *argData, double *argDest, long unsigned int argSize){
    double locStdDev = calc_std_dev(argData, argSize);
    double locMean = calc_average(argData, argSize);
    long unsigned int i;

    double *locTempData = argDest;

    for(i = 0; i < argSize; i++){
        locTempData[i] = (argData[i] - locMean)/locStdDev;
    }

}

/**
 * Calculates the confidence interval error of a dataset
 * @param argData -Double array that contains the data we are calculating the error from.
 * @param argSize -Integer representing the number of elements in argData.
 * @param argCI -Confidence interval we are calculating error for (requires value less than 1)
 * @return Returns a double representing the error.
 */
double calc_error(double *argData, long unsigned int argSize, double argCI){
    double locStdDev = calc_std_dev(argData, argSize);
    double locAlpha = 1-argCI;
    double locAlphaByTwo = locAlpha/2;
    double locZAlphaByTwo;    
    double locError;
    locZAlphaByTwo = calc_q(1-locAlphaByTwo);
    
    locError = (locStdDev/sqrt(argSize))*locZAlphaByTwo;
    
    return locError;
}




/********************************************************************
Statistical functions
*///////////////////////////////////////////////////////////////////
 
 /**  The following c++ functions for calculating normal and
 * chi-square probabilities and critical values were originally
 *  written by Gary Perlman of Wang Institute, Tyngsboro, MA
 * 01879.  Both the original C code and this c++ edition
 * are in the public domain.  This particular code was found online in javascript
 * and adapted for c++.  Original has been located and is included in the project
 * as z.c  */

    /*  POZ  --  probability of normal z value

        Note:
                This routine has six digit accuracy, so it is only useful for absolute
                z values <= 6.  For z values > to 6.0, poz() returns 0.0.
    */

    /**
     * Gary Perlman's algorithm to calculate probability of normal z value.
     * POZ  --  probability of normal z value
     * This routine has six digit accuracy, so it is only useful for absolute
                z values <= 6.  For z values > to 6.0, poz() returns 0.0.
     * @param z
     * @return 
     */
    double poz(double z, double Z_MAX) {
        double y, x, w;

        if (z == 0.0) {
            x = 0.0;
        } else {
            y = 0.5 * fabs(z);
            if (y > (Z_MAX * 0.5)) {
                x = 1.0;
            } else if (y < 1.0) {
                w = y * y;
                x = ((((((((0.000124818987 * w
                         - 0.001075204047) * w + 0.005198775019) * w
                         - 0.019198292004) * w + 0.059054035642) * w
                         - 0.151968751364) * w + 0.319152932694) * w
                         - 0.531923007300) * w + 0.797884560593) * y * 2.0;
            } else {
                y -= 2.0;
                x = (((((((((((((-0.000045255659 * y
                               + 0.000152529290) * y - 0.000019538132) * y
                               - 0.000676904986) * y + 0.001390604284) * y
                               - 0.000794620820) * y - 0.002034254874) * y
                               + 0.006549791214) * y - 0.010557625006) * y
                               + 0.011630447319) * y - 0.009279453341) * y
                               + 0.005353579108) * y - 0.002141268741) * y
                               + 0.000535310849) * y + 0.999936657524;
            }
        }
        return z > 0.0 ? ((x + 1.0) * 0.5) : ((1.0 - x) * 0.5);
    }

    /**  CRITZ  --  Compute critical normal z value to
                   produce given p.  We just do a bisection
                   search for a value within CHI_EPSILON,
                   relying on the monotonicity of pochisq().  */
    double critz(double p, double Z_MAX) {
        double Z_EPSILON = 0.000001;     /* Accuracy of z approximation */
        double minz = -Z_MAX;
        double maxz = Z_MAX;
        double zval = 0.0;
        double pval;

        if (p < 0.0 || p > 1.0) {
            return -1;
        }

        while ((maxz - minz) > Z_EPSILON) {
            pval = poz(zval,Z_MAX);
            if (pval > p) {
                maxz = zval;
            } else {
                minz = zval;
            }
            zval = (maxz + minz) * 0.5;
        }
        return(zval);
    }

    double calc_z(double argInputQ, double Z_MAX)
    {
        if (fabs(argInputQ) > Z_MAX) {
            return std::numeric_limits<double>::quiet_NaN(); //Return nan if invalid.
        } else {
            double qz = poz(argInputQ,Z_MAX);
            return qz;
        }
    }

    //  CALC_Q  --  Calculate Z from Q

    
    double calc_q(double argInputZ, double Z_MAX) {
        if (argInputZ < 0 || argInputZ > 1) {
            return std::numeric_limits<double>::quiet_NaN(); //Return nan if invalid.
        } else {
            return (critz(argInputZ,Z_MAX));
        }
    }

}