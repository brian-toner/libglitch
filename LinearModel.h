/* 
 * File:   LinearModel.h
 * Author: brian
 *
 * Created on July 4, 2015, 10:07 PM
 */

#ifndef LINEARMODEL_H
#define	LINEARMODEL_H

#include <string>
#include <cstdlib>
#include <iostream>
#include "StatsF.h"
#include "PointT.h"
#include "stringconversion.h"

namespace glch{

    class LinearModel {
    public:
        double vBetaHat;        //Slope of the regression line.
        double vAlphaHat;       //Y-Intercept
        double vSxx;            //Standard deviation x
        double vSyy;            //Standard deviation y
        double vRSquared;       //R^2 value
        std::string vEquation;  //String value representing the linear equation.

        double vMinX;
        double vMaxX;
        vector<PointF> vData;
        
        LinearModel(double aBetaHat = 0, 
                            double aAlaphaHat = 0,
                            double aSxx = 0,
                            double aSyy = 0,
                            double aRSquared = 0,
                            std::string aEquation = "");

        LinearModel(const LinearModel &orig);

        LinearModel(vector<PointF> &aData){
            set_data(aData);
        }
        
        void print(){
            std::cout << "Slope: " << vBetaHat << std::endl;
            std::cout << "Y-Intercept: " << vAlphaHat << std::endl;
            std::cout << "RSquared: " << vRSquared << std::endl;
            std::cout << "MinX: " << vMinX << std::endl;
            std::cout << "MaxX: " << vMaxX << std::endl;
        }
        
        /**
         * Computes the least squares regression for a vector of points.
         * @param aPoints vChartData Data for regression line
         * @return The linear model of the vector of points.
         */
        template<class T>
        LinearModel(std::vector< PointT<T> > aPoints){
            MatPoints lData = to_matpoints(aPoints);
            set_data(lData);
        }
        
        void recompute(double aMinX, double aMaxX);

        void set_data(vector<PointF> &aData);

        void set_data(vector<PointF> &aData, double aMinX, double aMaxX);
        
        /**
         * Computes the least squares regression for a vector of points.
         * The line of regression is only calculated for the points whose x values
         * fall within the range set by the min and max values.  Endpoints inclusive.
         * @param vChartData Data for regression line
         * @param aMinX Min value to calculate the regression line over.
         * @param aMaxX Max value to calculate the regression line over.
         * @return The linear model of the vector of points.
         */         
        void calculate_least_squares_regression(double argMinXValue, double argMaxXValue);
        
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
        void calculate_least_squares_regression(vector<PointF>::iterator argBegin, vector<PointF>::iterator argEnd);       
        
        private:

    };


}

#endif	/* LINEARMODEL_H */

