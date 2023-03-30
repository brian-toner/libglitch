/* 
 * File:   LinearModel.cpp
 * Author: brian
 * 
 * Created on July 4, 2015, 10:07 PM
 */

#include "LinearModel.h"

namespace glch{


    LinearModel::LinearModel(double aBetaHat, 
                        double aAlaphaHat,
                        double aSxx,
                        double aSyy,
                        double aRSquared,
                        std::string aEquation){
        vBetaHat = aBetaHat;
        vAlphaHat = aAlaphaHat;
        vSxx = aSxx;
        vSyy = aSyy;
        vRSquared = aRSquared;
        vRVal = sqrt(aRSquared);
        vEquation = aEquation;
    
    }

    LinearModel::LinearModel(const LinearModel &orig): vBetaHat(orig.vBetaHat),
                                                        vAlphaHat(orig.vAlphaHat),
                                                        vSxx(orig.vSxx),
                                                        vSyy(orig.vSyy),
                                                        vRSquared(orig.vRSquared),
                                                        vRVal(orig.vRVal),
                                                        vEquation(orig.vEquation),
                                                        vMinX(orig.vMinX),
                                                        vMaxX(orig.vMaxX),
                                                        vData(orig.vData){

    }

    /**
     * Calculates the line of best fit through a set of ordered pairs (argDataX, argDataY) using the least squares method.
     * <br>
     * Sxx = ∑(x^2|i=1 to n) - n (x-bar)^2
     * <br>    
     * Syy = ∑(y^2|i=1 to n) - n (y-bar)^2
     * <br>
     * B-hat = ∑(xy|i=1 to n) - (n x-bar y-bar)/Sxx
     * <br>
     * A-hat = y-bar - B-hat*x-bar
     * <br>
     * R^2 = (B-hat) √(Sxx/Syy)
     * 
     * @param argBegin - Begin iterator of points
     * @param argEnd - End iterator of points
     * @return Returns a structure containing the least squares data.
     */
    void LinearModel::calculate_least_squares_regression(std::vector<PointF>& aData, size_t aFirst, size_t aLast){

        vector<PointF>::iterator argBegin = aData.begin()+aFirst;
        vector<PointF>::iterator argEnd = aData.begin()+aLast;
        
        double locDataSumXY;
        double locDataSumXSquared;
        double locDataSumYSquared;
        //std::cout << "LM Test 65\n";
        PointF locAverage = calc_average_pt(aData,aFirst, aLast);
        //std::cout << "LM Test 67\n";
        long unsigned int argSize = argEnd-argBegin;
        long double locBetaHat;
        long double locAlphaHat;
        double locSxx;
        double locSyy;
        double locRSquared;

        string locEquation;

        locDataSumXY = 0;
        locDataSumXSquared = 0;
        locDataSumYSquared = 0;
        locBetaHat = 0;
        locAlphaHat = 0;
        locSxx = 0;
        locSyy = 0;


        for(vector<PointF>::iterator it = argBegin; it != argEnd; it++){
            locDataSumXY = locDataSumXY + ( (*it).x * (*it).y );
        }

        for(vector<PointF>::iterator it = argBegin; it != argEnd; it++){
            locDataSumXSquared = locDataSumXSquared + ( (*it).x * (*it).x );
        }

        for(vector<PointF>::iterator it = argBegin; it != argEnd; it++){
            locDataSumYSquared = locDataSumYSquared + ( (*it).y * (*it).y );
        }      

        locBetaHat = (locDataSumXY - (argSize*locAverage.x*locAverage.y))/(locDataSumXSquared - (argSize*locAverage.x*locAverage.x));
        locAlphaHat = locAverage.y - (locBetaHat*locAverage.x);
        locSxx = locDataSumXSquared - (argSize*locAverage.x*locAverage.x);
        locSyy = locDataSumYSquared - (argSize*locAverage.y*locAverage.y);
        locRSquared = locBetaHat*sqrt(locSxx/locSyy);
        //locRSquared *= locRSquared;
        
        //cout << "y = " << locAlphaHat << " + " << locBetaHat << "x " << " with R^2=" << locRSquared << endl;
        locEquation = "y = " + to_string(locAlphaHat) + " + " + to_string(locBetaHat) + "x " + " with R^2=" + to_string(locRSquared);

        vAlphaHat = locAlphaHat;
        vBetaHat = locBetaHat;
        vRSquared = locRSquared*locRSquared;
        vRVal = locRSquared;
        vSxx = locSxx;
        vSyy = locSyy;
        vEquation = locEquation;

        vMinX = (*argBegin).x;
        vMaxX = (*(argEnd-1) ).x;

    } 
    
    /**
     * Calculates the line of best fit through a set of ordered pairs (argDataX, argDataY) using the least squares method.
     * <br>
     * Sxx = ∑(x^2|i=1 to n) - n (x-bar)^2
     * <br>    
     * Syy = ∑(y^2|i=1 to n) - n (y-bar)^2
     * <br>
     * B-hat = ∑(xy|i=1 to n) - (n x-bar y-bar)/Sxx
     * <br>
     * A-hat = y-bar - B-hat*x-bar
     * <br>
     * R^2 = (B-hat) √(Sxx/Syy)
     * 
     * @param argBegin - Begin iterator of points
     * @param argEnd - End iterator of points
     * @return Returns a structure containing the least squares data.
     */
    void LinearModel::calculate_least_squares_regression_dep(vector<PointF>::iterator argBegin, vector<PointF>::iterator argEnd){

        double locDataSumXY;
        double locDataSumXSquared;
        double locDataSumYSquared;
        std::cout << "LM Test 65\n";
        PointF locAverage = calc_average_pt(argBegin, argEnd);
        std::cout << "LM Test 67\n";
        long unsigned int argSize = argEnd-argBegin;
        long double locBetaHat;
        long double locAlphaHat;
        double locSxx;
        double locSyy;
        double locRSquared;

        string locEquation;

        locDataSumXY = 0;
        locDataSumXSquared = 0;
        locDataSumYSquared = 0;
        locBetaHat = 0;
        locAlphaHat = 0;
        locSxx = 0;
        locSyy = 0;


        for(vector<PointF>::iterator it = argBegin; it != argEnd; it++){
            locDataSumXY = locDataSumXY + ( (*it).x * (*it).y );
        }

        for(vector<PointF>::iterator it = argBegin; it != argEnd; it++){
            locDataSumXSquared = locDataSumXSquared + ( (*it).x * (*it).x );
        }

        for(vector<PointF>::iterator it = argBegin; it != argEnd; it++){
            locDataSumYSquared = locDataSumYSquared + ( (*it).y * (*it).y );
        }      

        locBetaHat = (locDataSumXY - (argSize*locAverage.x*locAverage.y))/(locDataSumXSquared - (argSize*locAverage.x*locAverage.x));
        locAlphaHat = locAverage.y - (locBetaHat*locAverage.x);
        locSxx = locDataSumXSquared - (argSize*locAverage.x*locAverage.x);
        locSyy = locDataSumYSquared - (argSize*locAverage.y*locAverage.y);
        locRSquared = locBetaHat*sqrt(locSxx/locSyy);
        //locRSquared *= locRSquared;
        
        //cout << "y = " << locAlphaHat << " + " << locBetaHat << "x " << " with R^2=" << locRSquared << endl;
        locEquation = "y = " + to_string(locAlphaHat) + " + " + to_string(locBetaHat) + "x " + " with R^2=" + to_string(locRSquared);

        vAlphaHat = locAlphaHat;
        vBetaHat = locBetaHat;
        vRSquared = locRSquared*locRSquared;
        vRVal = locRSquared;
        vSxx = locSxx;
        vSyy = locSyy;
        vEquation = locEquation;

        vMinX = (*argBegin).x;
        vMaxX = (*(argEnd-1) ).x;

    } 

    /**
     * Computes the least squares regression for a vector of points.
     * The line of regression is only calculated for the points whose x values
     * fall within the range set by the min and max values.  Endpoints inclusive.
     * @param vChartData Data for regression line
     * @param aMinX Min value to calculate the regression line over.
     * @param aMaxX Max value to calculate the regression line over.
     * @return The linear model of the vector of points.
     */         
    void LinearModel::calculate_least_squares_regression(double argMinXValue, double argMaxXValue){

        MatPoints::iterator locBegin = vData.begin();
        MatPoints::iterator locEnd = vData.end();

        for(MatPoints::iterator it = locBegin; it != locEnd; it++){
            if((*it).x >= argMinXValue){
                locBegin = it;
                break;
            }
        }

        //for(MatPoints::reverse_iterator it = vData.rbegin(); it != vData.rend(); it++){
        //    if( (*it).x <= argMaxXValue){
        //        size_t lIndex = it-vData.rend();
        //        locEnd = vData.begin()+lIndex;
        //    }
        //}
        
        for(MatPoints::iterator it = locBegin; it != locEnd; it++){
            if( (*it).x > argMaxXValue ){
                locEnd = it;
                break;
            }
        }

        //calculate_least_squares_regression(locBegin, locEnd);
        calculate_least_squares_regression(vData,locBegin-vData.begin(), locEnd-vData.begin());
    }

    void LinearModel::recompute(double aMinX, double aMaxX){
        calculate_least_squares_regression(aMinX, aMaxX);
    }

    void LinearModel::set_data(vector<PointF> &aData){
        vData = aData;
        //calculate_least_squares_regression(vData.begin(), vData.end());
        calculate_least_squares_regression(vData,0,vData.size()-1);
    }

    void LinearModel::set_data(vector<PointF> &aData, double aMinX, double aMaxX){
        vData = aData;

        calculate_least_squares_regression(aMinX, aMaxX);
    }
    
    void LinearModel::set_data(std::vector<double>& aXData, std::vector<double>& aYData){
        //std::cout << "LM Test 174\n";
        vData.resize(aXData.size());
        
        for(size_t i = 0; i < aXData.size(); i++){
            //std::cout << i << " : " << aXData.at(i) << " : " << aYData.at(i) << endl;
            //std::cout << i << "LM Test 178\n";
            vData.at(i).x = aXData.at(i);
            vData.at(i).y = aYData.at(i);
        }        
        //std::cout << "LM Test 182\n";
        calculate_least_squares_regression(vData,0,aXData.size()-1);
        //std::cout << "LM Test 184\n";
    }
    
    void LinearModel::set_data(std::vector<double>& aXData, std::vector<double>& aYData, double aMinX, double aMaxX){
        
        set_data(aXData, aYData);
        calculate_least_squares_regression(aMinX, aMaxX);
    }
    
}