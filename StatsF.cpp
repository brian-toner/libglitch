#include "StatsF.h"

namespace glch{

    
    /**
     * Sums the values in an array.
     * @param aData - Array to find the sum of.
     * @param aDataSize - The number of elements in aData
     * @return The sum of all the elements of the vector.
     */
    double sum_vector(double* aData,
                      unsigned long aDataSize){

        double lRet = 0;

        for(unsigned long i = 0; i < aDataSize; i++){
            lRet += aData[i];
        }

        return lRet;
    }

    /**
     * Calculates the average of an ordered set of pairs.
     * mu_x = (1/(f-l)) ∑((x_i) | i=f to l)
     * mu_y = (1/(f-l)) ∑((y_i) | i=f to l)
     * where x_i = aData.x, y_i = aData.y, f = aFirst, and l = aLast
     *
     * @param aData -Array of points.
     * @param aFirst -First element to calculate the mean from
     * @param aLast - Last element to calculate the mean to
     * @return Returns a PointF that represents the mean of the x and y ordered pairs.
     *         between the first and last elements.
     */
    struct CPointF calc_average_cpt(struct CPointF* aData, 
                                  unsigned long aFirst, 
                                  unsigned long aLast){

        struct CPointF locAverage = {0,0};

        long unsigned int lSize = aLast-aFirst+1;

        for(unsigned long i = aFirst; i < aLast+1; i++){
            locAverage.x += aData[i].x/(double)lSize;
            locAverage.y += aData[i].y/(double)lSize;
        }

        return locAverage;
    }

    struct CPointF calc_average_cpt(std::vector<glch::PointF> &aData, 
                                  unsigned long aFirst, 
                                  unsigned long aLast){

        struct CPointF locAverage = {0,0};

        long unsigned int lSize = aLast-aFirst+1;

        for(unsigned long i = aFirst; i < aLast+1; i++){
            locAverage.x += aData[i].x/(double)lSize;
            locAverage.y += aData[i].y/(double)lSize;
        }

        return locAverage;
    }

void calculate_least_squares_qregression(struct CQuadModel &aDst, 
                                                 std::vector<glch::PointF> &aData, 
                                                 unsigned long aDataSize, 
                                                 unsigned long aFirst, 
                                                 unsigned long aLast){

    //Initialize the return argument
    aDst.vRSquared = 0;
    aDst.vRVal = 0;

    unsigned long lSize = aLast-aFirst+1;
    
    aDst.vMeanX = 0;
    aDst.vMeanXSq = 0;
    aDst.vMeanY = 0;
    
    for(unsigned long i = aFirst; i < aLast+1; i++){
        aDst.vMeanX   += aData.at(i).x;
        aDst.vMeanXSq += aData.at(i).x*aData.at(i).x;
        aDst.vMeanY   += aData.at(i).y;
    }
    
    aDst.vMeanX = aDst.vMeanX/lSize;
    aDst.vMeanXSq = aDst.vMeanXSq/lSize;
    aDst.vMeanY = aDst.vMeanY/lSize;
    
    //Performing the linear model calculations
    aDst.vSxx = 0;
    aDst.vSxy = 0;
    aDst.vSxxsq = 0;
    aDst.vSxsqxsq = 0;
    aDst.vSxsqy = 0;

    for(unsigned long i = aFirst; i < aLast+1; i++){
        aDst.vSxx += (aData[i].x-aDst.vMeanX)*(aData[i].x-aDst.vMeanX);
        aDst.vSxy += (aData[i].x-aDst.vMeanX)*(aData[i].y-aDst.vMeanY);
        aDst.vSxxsq += (aData[i].x-aDst.vMeanX)*(aData[i].x*aData[i].x-aDst.vMeanXSq);
        aDst.vSxsqxsq += (aData[i].x*aData[i].x-aDst.vMeanXSq)*(aData[i].x*aData[i].x-aDst.vMeanXSq);
        aDst.vSxsqy += (aData[i].x*aData[i].x-aDst.vMeanXSq)*(aData[i].y-aDst.vMeanY);

    }

    aDst.vBetaHat = (aDst.vSxy*aDst.vSxsqxsq - aDst.vSxsqy*aDst.vSxxsq )
                    /(aDst.vSxx*aDst.vSxsqxsq - (aDst.vSxxsq)*(aDst.vSxxsq) );
    aDst.vChiHat = (aDst.vSxsqy*aDst.vSxx - aDst.vSxy*aDst.vSxxsq)
                   /(aDst.vSxx*aDst.vSxsqxsq - (aDst.vSxxsq)*(aDst.vSxxsq) );
    aDst.vAlphaHat = aDst.vMeanY - (aDst.vBetaHat*aDst.vMeanX) - (aDst.vChiHat*aDst.vMeanXSq);


    aDst.vMinX = aData[aFirst].x;
    aDst.vMaxX = aData[aLast].x;

}
    
void calculate_least_squares_regression(struct CLinearModel &aDst, 
                                                 std::vector<glch::PointF> &aData, 
                                                 unsigned long aDataSize, 
                                                 unsigned long aFirst, 
                                                 unsigned long aLast){

    //Initialize the return argument
    aDst.vSumXY = 0;
    aDst.vSumXSquared = 0;
    aDst.vSumYSquared = 0;
    aDst.vBetaHat = 0;
    aDst.vAlphaHat = 0;
    aDst.vSxx = 0;
    aDst.vSyy = 0;
    aDst.vRSquared = 0;
    aDst.vRVal = 0;

    
    //Performing the linear model calculations

    unsigned long lSize = aLast-aFirst+1;
    aDst.vMeanXY = calc_average_cpt(aData,aFirst, aLast);

    for(unsigned long i = aFirst; i < aLast+1; i++){
        aDst.vSumXY = aDst.vSumXY + ( aData[i].x * aData[i].y );
        aDst.vSumXSquared = aDst.vSumXSquared + ( aData[i].x * aData[i].x );
        aDst.vSumYSquared = aDst.vSumYSquared + ( aData[i].y * aData[i].y );

    }

    aDst.vBetaHat = (aDst.vSumXY - (lSize*aDst.vMeanXY.x*aDst.vMeanXY.y))
                    /(aDst.vSumXSquared - (lSize*aDst.vMeanXY.x*aDst.vMeanXY.x));
    aDst.vAlphaHat = aDst.vMeanXY.y - (aDst.vBetaHat*aDst.vMeanXY.x);
    aDst.vSxx = aDst.vSumXSquared - (lSize*aDst.vMeanXY.x*aDst.vMeanXY.x);
    aDst.vSyy = aDst.vSumYSquared - (lSize*aDst.vMeanXY.y*aDst.vMeanXY.y);
    aDst.vRVal = aDst.vBetaHat*sqrt(aDst.vSxx/aDst.vSyy);
    aDst.vRSquared = aDst.vRVal*aDst.vRVal;


    aDst.vMinX = aData[aFirst].x;
    aDst.vMaxX = aData[aLast].x;

}

void calculate_least_squares_regression(struct CLinearModel* aDst, 
                                                 struct CPointF* aData, 
                                                 unsigned long aDataSize, 
                                                 unsigned long aFirst, 
                                                 unsigned long aLast){

    //Initialize the return argument
    aDst->vSumXY = 0;
    aDst->vSumXSquared = 0;
    aDst->vSumYSquared = 0;
    aDst->vBetaHat = 0;
    aDst->vAlphaHat = 0;
    aDst->vSxx = 0;
    aDst->vSyy = 0;
    aDst->vRSquared = 0;
    aDst->vRVal = 0;

    
    //Performing the linear model calculations

    unsigned long lSize = aLast-aFirst+1;
    aDst->vMeanXY = calc_average_cpt(aData,aFirst, aLast);

    for(unsigned long i = aFirst; i < aLast+1; i++){
        aDst->vSumXY = aDst->vSumXY + ( aData[i].x * aData[i].y );
        aDst->vSumXSquared = aDst->vSumXSquared + ( aData[i].x * aData[i].x );
        aDst->vSumYSquared = aDst->vSumYSquared + ( aData[i].y * aData[i].y );

    }

    aDst->vBetaHat = (aDst->vSumXY - (lSize*aDst->vMeanXY.x*aDst->vMeanXY.y))
                    /(aDst->vSumXSquared - (lSize*aDst->vMeanXY.x*aDst->vMeanXY.x));
    aDst->vAlphaHat = aDst->vMeanXY.y - (aDst->vBetaHat*aDst->vMeanXY.x);
    aDst->vSxx = aDst->vSumXSquared - (lSize*aDst->vMeanXY.x*aDst->vMeanXY.x);
    aDst->vSyy = aDst->vSumYSquared - (lSize*aDst->vMeanXY.y*aDst->vMeanXY.y);
    aDst->vRVal = aDst->vBetaHat*sqrt(aDst->vSxx/aDst->vSyy);
    aDst->vRSquared = aDst->vRVal*aDst->vRVal;


    aDst->vMinX = aData[aFirst].x;
    aDst->vMaxX = aData[aLast].x;

}

double max_array(double *aData, long unsigned int aSize){
    double lRet = aData[0];
    for(int i = 1; i < aSize; i++){
        if(lRet < aData[i]){
            lRet = aData[i];
        }
    }
    return lRet;
}

double min_array(double *aData, long unsigned int aSize){
    double lRet = aData[0];
    for(int i = 1; i < aSize; i++){
        if(lRet > aData[i]){
            lRet = aData[i];
        }
    }
    return lRet;
}

double min_array_nz(double *aData, long unsigned int aSize){
    double lRet = 1.79769e+308;
    for(int i = 1; i < aSize; i++){
        if( lRet > aData[i] && aData[i] > 0 ){
            lRet = aData[i];
        }
    }
    return lRet;
}

double calc_bin(double *aData, long unsigned int aSize){
    
    double lMean = calc_average(aData, aSize);
    double lAdjMean[aSize];
    double lCumulativeDeviate[aSize];
    double lRange;
    double lStandardDeviation = 0;
    double lRet;
    
    for(long unsigned int i = 0; i < aSize; i++){
        lAdjMean[i] = aData[i]-lMean;
        lCumulativeDeviate[i] = sum_vector(lAdjMean,i+1);
        lStandardDeviation += lAdjMean[i]*lAdjMean[i];
        
    }
    
    lStandardDeviation = sqrt(lStandardDeviation/(aSize-1) );
    lRange = max_array(lCumulativeDeviate, aSize)-min_array(lCumulativeDeviate, aSize);
    
    if(lStandardDeviation){
        lRet = lRange/lStandardDeviation;
    } else {
        lRet = 0;
    }
    
    return lRet;
      
}


double calc_avg_bin(double * aData, long unsigned int aSize, long unsigned int aBinSize){
    
    double lAvgRescaledRange = 0;
    double lCt = (int)aSize/(int)aBinSize;
    double lTemp;
    long unsigned int lSize = (long unsigned int)lCt*aBinSize;
    
    for(long unsigned int i = 0; i < lCt; i++){
        
        lTemp = calc_bin(aData+(i*aBinSize), aBinSize);
        //std::cout << i << " : " << lCt << " : " << lTemp << " : " << (i*aBinSize) << " : " << aBinSize << " : " << aSize << std::endl;
        if(lTemp){
            lAvgRescaledRange += lTemp;
        }
    }
    if(lCt == 0){
      //std::cout << "ASR: " << lAvgRescaledRange << " : " << lCt << std::endl;
      return 0;
    }
    return lAvgRescaledRange/lCt;
    
}

void push_bin_hurst(double *aData, long unsigned int aSize, std::vector<glch::PointF> &aDst, long unsigned int aDivisions){

        CPointF lRegData[aDivisions];
        int lCurrentSize = aSize;


        for(long unsigned int i = 0; i < aDivisions; i++){
            lRegData[i].x = log(lCurrentSize);
            double lAvgBin = calc_avg_bin(aData, aSize, lCurrentSize);
            if(lAvgBin){
                lRegData[i].y = log(lAvgBin);
                aDst.push_back(glch::PointF(lRegData[i].x,lRegData[i].y));
            }

            lCurrentSize /= 2;

        }

    }
    
    
double calc_avg_bin_2d(double * aData, long unsigned int aSize, long unsigned int aBinSize){
    
    double lAvgRescaledRange = 0;
    double lCt = 2*(aSize*aSize)/aBinSize;
    double lTData[aBinSize];
    
    for(long unsigned int i = 0; i < aSize; i++){
        for(long unsigned int j = 0; j < aSize-aBinSize+1; j+=aBinSize){
            lAvgRescaledRange += calc_bin(aData+(i*aSize)+j, aBinSize);
            
            for(int k = 0; k < aBinSize; k++){
                lTData[k] = *(aData+(j*aSize)+i+(k*aSize) );
            }
            lAvgRescaledRange += calc_bin(lTData, aBinSize);
        }
    }

    
    return lAvgRescaledRange/lCt;
    
}


double calc_bin_hurst_2d(double *aData, long unsigned int aSize, long unsigned int aDivisions){

    CLinearModel lLinearModel;
    CPointF lRegData[aDivisions];
    int lCurrentSize = aSize;
    

    for(long unsigned int i = 0; i < aDivisions; i++){
        
        lRegData[i].x = log(lCurrentSize*lCurrentSize);
        lRegData[i].y = log(calc_avg_bin_2d(aData, aSize, lCurrentSize));   
        
        //std::cout << i << " | " << lRegData[i].x << " : " << lRegData[i].y << std::endl;
        
        lCurrentSize /= 2;
        
    }

    calculate_least_squares_regression(&lLinearModel, lRegData, aDivisions, 0, aDivisions-1);
    

    return lLinearModel.vBetaHat;
}

double calc_bin_hurst(double *aData, long unsigned int aSize, long unsigned int aDivisions){

    CLinearModel lLinearModel;
    CPointF lRegData[aDivisions];
    int lCurrentSize = aSize;
    

    for(long unsigned int i = 0; i < aDivisions; i++){
        lRegData[i].x = log(lCurrentSize);
        double lAvgBin = calc_avg_bin(aData, aSize, lCurrentSize);
        if(lAvgBin){
            lRegData[i].y = log(lAvgBin);   
        }
        
        lCurrentSize /= 2;
        
    }

    calculate_least_squares_regression(&lLinearModel, lRegData, aDivisions, 0, aDivisions-1);
    

    return lLinearModel.vBetaHat;
}



double calc_hurst(double *aData, long unsigned int aSize){
    double lMean = calc_average(aData, aSize);
    double lAdjMean[aSize];
    double lCumulativeDeviate[aSize];
    double lRange[aSize];
    double lStandardDeviations[aSize];
    double lRescaledRange[aSize];
    CLinearModel lLinearModel;
    CPointF lRegData[aSize];
    
    //std::cout << lMean << std::endl;
    
    for(long unsigned int i = 0; i < aSize; i++){
        lAdjMean[i] = aData[i]-lMean;
        lCumulativeDeviate[i] = sum_vector(lAdjMean,i+1);
        lRange[i] = max_array(lCumulativeDeviate, i)-min_array(lCumulativeDeviate, i);
        
        for(long unsigned int j = 0; j < i; j++){
            lStandardDeviations[i] += (lAdjMean[j]*lAdjMean[j]);
        }
        
        lStandardDeviations[i] = sqrt(1.0/i * lStandardDeviations[i]);
        if(lStandardDeviations[i]){
            lRescaledRange[i] = lRange[i]/lStandardDeviations[i];
        }

        if(i && lRescaledRange[i] > 0){
            lRegData[i].x = log(i);
            lRegData[i].y = log(lRescaledRange[i]);
        }
        
        //std::cout << i << " | Mean: " << lAdjMean[i] << " | SD: " << lStandardDeviations[i] << " | RR: " << lRescaledRange[i] << " | Rg: " << lRange[i]<< " | CD: " << lCumulativeDeviate[i] << std::endl;
        
        //std::cout << lRegData[i].x << " : " << lRegData[i].y << std::endl;
    }
    
    calculate_least_squares_regression(&lLinearModel, lRegData, aSize, 0, aSize-1);
    
    return lLinearModel.vBetaHat;
    
    
}
    



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
        std::cout << "calc avg:" << it->x << " : " << it->y << endl; 
        locAverage.x += (*it).x/(double)locSize;
        locAverage.y += (*it).y/(double)locSize;
    }
    
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
PointF calc_average_pt(std::vector<PointF>& aData, size_t aFirst, size_t aLast){
    PointF locAverage = PointF(0,0);
    
    vector<PointF>::iterator argBegin = aData.begin()+aFirst;
    vector<PointF>::iterator argEnd = aData.begin()+aLast;
    
    long unsigned int locSize = argEnd-argBegin;
    
    for(vector<PointF>::iterator it = argBegin; it != argEnd; it++){
        //std::cout << "calc avg:" << it->x << " : " << it->y << endl; 
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