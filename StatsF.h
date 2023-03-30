#ifndef GLCH_STATSF_H_INCLUDED
#define GLCH_STATSF_H_INCLUDED

using namespace std;

#include <math.h>
#include <algorithm> //sort
#include <vector>
#include <limits> //For handeling NaN

#include "PointT.h"

namespace glch{

    /***
    * This structure contains an (x,y) ordered pair.
    */
    struct CPointF{
           double x;    //The x coordinate of the ordered pair.
           double y;    //The y coordinate of the ordered pair.
    };

    /***
     * This structure is used for containing the linear model data
     */
    struct CLinearModel{

        double vBetaHat;        //Slope of the regression line.
        double vAlphaHat;       //Y-Intercept
        double vSxx;            //Standard deviation x
        double vSyy;            //Standard deviation y
        double vRSquared;       //R^2 value
        double vRVal;           //R value

        struct CPointF vMeanXY; //The mean of the x,y data.
        double vSumXY;          //Sum xy
        double vSumXSquared;    //Sum x^2
        double vSumYSquared;    //Sum y^2

        double vMinX;           //Min x range
        double vMaxX;           //Max x range

    };

    struct CQuadModel{

        double vBetaHat;        //Linear Term.
        double vChiHat;         //Quadratic Term.
        double vAlphaHat;       //Y-Intercept
        double vSxx;            //Standard deviation x
        double vSxy;            //Standard deviation x y
        double vSxxsq;          //Standard deviation x x^2
        double vSxsqxsq;        //Standard deviation x^2 x^2
        double vSxsqy;          //Standard deviation x^2 y
        double vRSquared;       //R^2 value
        double vRVal;           //R value

        double vMeanY;
        double vMeanX;
        double vMeanXSq;

        double vSumXY;          //Sum xy
        double vSumXSquared;    //Sum x^2
        double vSumYSquared;    //Sum y^2

        double vMinX;           //Min x range
        double vMaxX;           //Max x range

    };
    
    void calculate_least_squares_qregression(struct CQuadModel &aDst, 
                                                 std::vector<glch::PointF> &aData, 
                                                 unsigned long aDataSize, 
                                                 unsigned long aFirst, 
                                                 unsigned long aLast);
    
    void calculate_least_squares_regression(struct CLinearModel &aDst, 
                                                 std::vector<glch::PointF> &aData, 
                                                 unsigned long aDataSize, 
                                                 unsigned long aFirst, 
                                                 unsigned long aLast);
    void calculate_least_squares_regression(struct CLinearModel* aDst, 
                                                 struct CPointF* aData, 
                                                 unsigned long aDataSize, 
                                                 unsigned long aFirst, 
                                                 unsigned long aLast);
    
    void push_bin_hurst(double *aData, long unsigned int aSize, std::vector<glch::PointF> &aDst, long unsigned int aDivisions);
    double calc_hurst(double *aData, long unsigned int aSize);
    double calc_bin_hurst(double *aData, long unsigned int aSize, long unsigned int aDivisions);
    double calc_avg_bin(double * aData, long unsigned int aSize, long unsigned int aBinSize);
    double calc_bin(double *aData, long unsigned int aSize);
    double calc_bin_hurst_2d(double *aData, long unsigned int aSize, long unsigned int aDivisions);
    double min_array(double *aData, long unsigned int aSize);
    double min_array_nz(double *aData, long unsigned int aSize);
    double max_array(double *aData, long unsigned int aSize);
        struct CPointF calc_average_cpt(std::vector<glch::PointF> &aData, 
                                  unsigned long aFirst, 
                                  unsigned long aLast);
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
    double calc_average(double *argData, long unsigned int argSize); 

    template <class T>
    double mean(std::vector<T> aData){
        double lRet = 0;
        for(size_t i = 0; i < aData.size(); i++){
            lRet += aData.at(i);
        }
        return lRet/aData.size();
        
    }

    /**
     * CalcVariance(double, int) - Calculates the simple variance of a array.  
     * This is accomplished by:
     * <br>
     * Var = ∑((x_i)^2 | i=1 to N)/N - (mu)^2
     * 
     * @param argData -Array of doubles we want to find the variance of.
     * @param argSize -Integer that indicates how many elements argData contains.
     * @return Returns a double that represents the variance.
     */    
    template <class T>
    double variance(std::vector<T> aData){

        double lAverage = mean(aData);
        double lResults = 0;

        for(size_t i=0;i<aData.size();i++){
            lResults += (aData[i]-lAverage)*(aData[i]-lAverage);
        }

        lResults = lResults/(aData.size()-1);
        
        return lResults;

    }
    
    /**
     * CalcVariance(double, int) - Calculates the population variance of a array.  
     * This is accomplished by:
     * <br>
     * Var = ∑((x_i)^2 | i=1 to N)/N - (mu)^2
     * 
     * @param argData -Array of doubles we want to find the variance of.
     * @param argSize -Integer that indicates how many elements argData contains.
     * @return Returns a double that represents the variance.
     */    
    template <class T>
    double variancep(std::vector<T> aData){

        double lAverage = mean(aData);
        double lResults = 0;

        for(size_t i=0;i<aData.size();i++){
            lResults += aData[i]*aData[i];
        }

        lResults = lResults/aData.size();
        lResults -= (lAverage*lAverage);
        
        return lResults;

    }

    /**
     * Calculates population standard deviation of a double array.  This is accomplished by
     * sqrt(Variance)
     * @param argData -Array of doubles we want to find the standard deviation of.
     * @param argSize -Integer that indicates how many elements argData contains.
     * @return Returns a double that represents the standard deviation.
     */    
    template <class T>
    double stdevp(std::vector<T> aData){
        return sqrt(variancep(aData));
    }
    

    /**
     * Calculates the simple standard deviation of a double array.  This is accomplished by
     * sqrt(Variance)
     * @param argData -Array of doubles we want to find the standard deviation of.
     * @param argSize -Integer that indicates how many elements argData contains.
     * @return Returns a double that represents the standard deviation.
     */    
    template <class T>
    double stdev(std::vector<T> aData){
        return sqrt(variance(aData));
    }    
    
    template <class T>
    T max_val(std::vector<T> aData){
        return *std::max_element(aData.begin(), aData.end());
    }

    template <class T>
    T min_val(std::vector<T> aData){
        return *std::min_element(aData.begin(), aData.end());
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
    PointF calc_average_pt(vector<PointF>::iterator argBegin, vector<PointF>::iterator argEnd);

    PointF calc_average_pt(std::vector<PointF>& aData, size_t aFirst, size_t aLast);
    
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
    long double calc_variance(double *argData, long unsigned int argSize);

    /**
     * Calculates standard deviation of a double array.  This is accomplished by
     * sqrt(Variance)
     * @param argData -Array of doubles we want to find the standard deviation of.
     * @param argSize -Integer that indicates how many elements argData contains.
     * @return Returns a double that represents the standard deviation.
     */
    double calc_std_dev(double *argData, long unsigned int argSize);

    /**
     * Ranks a SORTED double array.  Where 1,2,2,3,4 would be ranked as 1,2.5,2.5,4,5
     * and 1,2,2,2,3 would be ranked as 1,3,3,3,5 OR 1/1,(2+3+4)/3,(2+3+4)/3,(2+3+4)/3,5/1
     * @param argSortedData -Sorted double array to be ranked.
     * @param argDest - Double pointer of same size argSortedData that will be the destination of the function.
     * @param argSize -Number of elements in argSortedData.
     * @return Returns a new double array with the ranked data. 
     */
    void rank_data(double *argSortedData, double *argDest, long unsigned int argSize);
    //double *RankData(double *argSortedData, int argSize);

    /**
     * Calculates out individual z scores in argData using the algorithms developed by
     * Gary Perlman.  Using calc_q.
     * @param argData -Should be a ranked probability.
     * @param argDest - Double pointer of same size argData that will be the destination of the function.
     * @param argSize -Size of argData 
     * @return  -Returns the inversenorm(p_i)
     */
    void calc_ranked_z(double *argData, double *argDest, long unsigned int argSize);

    /**
     * Calculates ranked probability by (argRank[i] -.5)/argSize.  Should only be used with
     * a double array that has been ranked.
     * @param argRank -Double array containing ranked data
     * @param argDest - Double pointer of same size argRank that will be the destination of the function.
     * @param argSize -Number of elements in argRank.
     * @return Returns a double array containing the ranked probabilities of size argSize.
     */
    void calc_ranked_prob_i(double *argRank, double *argDest, long unsigned int argSize);

    /**
     * Calculates Z score by (x_i - mu)/sigma
     * @param argData -Double array that contains the data that Z Scores will be calculated from.
     * @param argDest - Double pointer of same size argData that will be the destination of the function.
     * @param argSize -Integer representing the number of elements in argRankedProbI.
     * @return Returns a double array containing Z Scores calculated form argData 
     */
    void calc_z_score(double *argData, double *argDest, long unsigned int argSize);


    void calc_prob_from_z(double *argData, double *argDest, long unsigned int argSize);

    /**
     * Uses sort in algorithm library to sort a double array contained in argData. 
     * @param argData -Double array that contains the data that needs to be sorted.
     * @param argDest - Double pointer of same size argData that will be the destination of the function.
     * @param argSize -Integer representing the number of elements in argData.
     * @return  Returns a new double array with the sorted data with argSize elements.
     */
    void sort_data_f(double *argSource, double *argDest, long unsigned int argSize);


    /**
     * Calculates the confidence interval error of a dataset
     * @param argData -Double array that contains the data we are calculating the error from.
     * @param argSize -Integer representing the number of elements in argData.
     * @param argCI -Confidence interval we are calculating error for (requires value less than 1)
     * @return Returns a double representing the error.
     */
    double calc_error(double *argData, long unsigned int argSize, double argCI);


    /**
     * Gary Perlman's algorithm to calculate probability of normal z value
     * @param z
     * @return 
     */
    double poz(double z, double Z_MAX = 6);

    /**
     * Gary Perlman's algorithm to compute critical normal z value to produce given p
     * @param p
     * @return 
     */
    double critz(double p, double Z_MAX = 6);

    /**
     * Uses 1 - poz(fabs(argInputQ)) to calculate out z values. (Gary Perlman's algorithm)
     * @param argInputQ
     * @return 
     */
    double calc_z(double argInputQ, double Z_MAX = 6);

    /**
     * Calculate Z from Q using critz(argInputZ) (Gary Perlman's algorithm)
     * @param argInputZ
     * @return 
     */
    double calc_q(double argInputZ, double Z_MAX = 6);


    //}

}

#endif // GLCH_STATSF_H_INCLUDED
