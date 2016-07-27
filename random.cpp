#include "random.h"


namespace glch{

    /**
     * Generates a random float between min and max values (exclusive end points). e.g. domain of (min,max)
     * @param aMin Minimum value.
     * @param aMax Maximum value.
     * @return Random floating point between min and max exclusive.
     */
    float randf(float aMin, float aMax){
        return randf()*(aMax-aMin) + aMin;
    }
    
    /**
     * Seeds the RNG with the current time.  This can not be performed more 
     * than once every second.
     * @return The random seed used.
     */
    size_t seed_rand(){
        time_t lTimer;
        time(&lTimer);
        srand(lTimer);
        return lTimer;
    }

    /**
     * Uses the box-muller transformation to produce a 1d normal random distribution.
     * @param aMu Mean.
     * @param aSigma Standard deviation.
     * @return 1d point in the random distribution.
     */    
    double normal(double aMu, double aSigma){
        double z_0 = sqrt(-2.0*log(randf()))*cos(2*M_PI*randf());
        //double z_1 = sqrt(-2.0*log(randf()))*sin(2*M_PI*randf());

        return z_0*aSigma+aMu;
    }    

    /**
     * Uses the box-mull transformation to produce 2d normal random distribution.
     * @param aMu Mean.
     * @param aSigma Standard deviation.
     * @return 2d point in the random distribution.
     */    
    PointF normal_2d(double aMu, double aSigma){
        double z_0 = sqrt(-2.0*log(randf()))*cos(2*M_PI*randf());
        double z_1 = sqrt(-2.0*log(randf()))*sin(2*M_PI*randf());

        return PointF(z_0*aSigma+aMu,z_1*aSigma+aMu);
    }   
    
    /**
     * Generates a vector of size aSize, with a normal distribution.
     * @param aSize Size of the vector.
     * @param aMu Mean.
     * @param aSigma Standard deviation.
     * @return A normal distribution of size aSize.
     */    
    std::vector<double> normal_vector(size_t aSize, double aMu, double aSigma){
        std::vector<double> lRet;
        lRet.resize(aSize);
        
        for(size_t i = 0; i < aSize; i++){
            lRet.at(i) = normal(aMu,aSigma);
        }
        
        return lRet;
    }
    
    /**
     * Creates a vector of points containing Brownian motion.  Stores this vector in argOut 
     * @param aMin T-start
     * @param aMax T-final
     * @param aTimeSteps Number of time steps the divide the interval
     * @param aOut Vector where we are storing the generated Brownian motion.
     */
    void brownian(double aMin, double aMax, size_t aTimeSteps, std::vector<PointF> & aOut){
        
        double locVariance = (aMax-aMin)/(double)aTimeSteps;         //Variance

        //Initializing the output
        aOut.clear();

        //Generating our normal vector, mean = 0, stdev = sqrt(variance), n = TimeSteps, stored in varData
        std::vector<double> lData = normal_vector(aTimeSteps,0,sqrt(locVariance));

        double locNextXPos = 0; //Current x position
        
        //Looping through our time steps storing in argOut
        for(size_t i = 0; i < aTimeSteps; i ++){
            locNextXPos += locVariance;
            PointF locCopy = PointF(locNextXPos, lData.at(i));      //Setting x,y data
            aOut.push_back(locCopy);                          //Storing x,y
        }
        
        //Starting point is at 0,0
        aOut.insert(aOut.begin(), PointF(0.0,0.0));

        //Cumulative sum
        for(size_t i = 1; i < aOut.size(); i++){
            aOut.at(i).y += aOut.at(i-1).y;
        }

    }    

    /**
     * Creates a vector of points containing Brownian motion.  Stores this vector in argOut 
     * @param aMin T-start
     * @param aMax T-final
     * @param aTimeSteps Number of time steps the divide the interval
     * @param aOut Vector where we are storing the generated Brownian motion.
     */
    void brownian(double aMin, double aMax, size_t aTimeSteps, std::vector<double> & aOut){
        
        double locVariance = (aMax-aMin)/(double)aTimeSteps;         //Variance

        //Initializing the output
        aOut.clear();

        //Generating our normal vector, mean = 0, stdev = sqrt(variance), n = TimeSteps, stored in varData
        std::vector<double> lData = normal_vector(aTimeSteps,0,sqrt(locVariance));

        //Looping through our time steps storing in argOut
        for(size_t i = 0; i < aTimeSteps; i ++){
            aOut.push_back(lData.at(i));                          //Storing x,y
        }
        
        //Starting point is at 0,0
        aOut.insert(aOut.begin(), 0.0);

        //Cumulative sum
        for(size_t i = 1; i < aOut.size(); i++){
            aOut.at(i) += aOut.at(i-1);
        }

    }
    
}