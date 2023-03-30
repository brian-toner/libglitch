#include "miscfunctions.h"

namespace glch{
    
    int year(){        
        time_t lNow = time(NULL);
        struct tm *lTime = localtime(&lNow);
        return lTime->tm_year+1900;      
    }

    int month(){        
        time_t lNow = time(NULL);
        struct tm *lTime = localtime(&lNow);
        return lTime->tm_mon+1;      
    }
    
    int day(){        
        time_t lNow = time(NULL);
        struct tm *lTime = localtime(&lNow);
        return lTime->tm_mday;      
    }    

    std::string wday(){
        std::string lWDay[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
        time_t lNow = time(NULL);
        struct tm *lTime = localtime(&lNow);
        return lWDay[lTime->tm_wday];      
    }  
    
    int hour(){        
        time_t lNow = time(NULL);
        struct tm *lTime = localtime(&lNow);
        return lTime->tm_hour+1;      
    }       

    int minute(){
        time_t lNow = time(NULL);
        struct tm *lTime = localtime(&lNow);
        return lTime->tm_min+1;      
    }  

    int second(){
        time_t lNow = time(NULL);
        struct tm *lTime = localtime(&lNow);
        return lTime->tm_sec;     
    }  
    

    
    /**
    * Copies one data vector to another.
    * @param aBegin The pointer to the destination vector.
    * @param aDataStart The pointer to the source vector.
    * @param aDataEnd The pointer to the element after the last element of the source vector.
    */
   void copy_data_vector(char* aDst, const char* aDataStart, const char* aDataEnd){
       
       char* lSrcSt = (char*)aDataStart;
       char* lSrcEnd = (char*)aDataEnd;
       size_t lElements = lSrcEnd-lSrcSt;
       char* lDstSt = (char*)aDst;
       char* lDstEnd = lDstSt+lElements;
       
       for(char* it = lDstSt; it != lDstEnd; it++, lSrcSt++){
           (*it) = (*lSrcSt);
       }

       return;
   }
    
    /**
     * Finds ideal dimensions for a matrix with aSize elements
     * @param aSize Number of elements.
     * @return vector of two elements containing the size of the matrix.
     */
    std::vector<int> find_dims(int aSize){
        std::vector<int> lRet1;
        std::vector<int> lRet2;
        lRet1.resize(2,1);
        lRet2.resize(2,1);
        int lSize = aSize;

        int lSqrt = sqrt(aSize);
        if( (lSqrt - sqrt(aSize)) == 0){
            lRet1.at(0) = lSqrt;
            lRet1.at(1) = lSqrt;
            return lRet1;
        }

        int c = 1;
        for ( int i = 2; i <= lSize; ++i ){

            while ( lSize % i == 0 ) {
                lSize /= i;
                lRet1.at(c%2) *= i;
                c++;
            }

        }

        c = 1;
        lSize = aSize;
        for ( int i = 2; i <= lSize; ++i, c++ ){

            while ( lSize % i == 0 ) {
                lSize /= i;
                lRet2.at(c%2) *= i;
            }

        }

        //cout << fabs(lRet2.at(0) - lRet2.at(1)) << " : " << fabs(lRet1.at(0) - lRet1.at(1)) << endl;
        if( fabs(lRet2.at(0) - lRet2.at(1)) < fabs(lRet1.at(0) - lRet1.at(1)) ){
            return lRet2;
        }

        return lRet1;
    }

    
    /**
     * Maps one set of numbers into another set.
     * @param aInput: Number we are mapping from
     * @param aToRange: Range we are mapping to
     * @param aToMin: Min we are mapping to
     * @param aFromRange: Range we are mapping from.
     * @param aFromMin: Min we are mapping from
     * @return Mapped Value
     */
    double map_point(double aInput, double aToRange, double aToMin, double aFromRange, double aFromMin, bool aFlip){
        double locReturn = 0;

        if(aFlip){
            double tMap = (aInput - aFromMin)/(aFromRange); 
            locReturn = aToRange - (tMap) * (aToRange) + aToMin; 
        } else {
            locReturn = (aInput - aFromMin)/(aFromRange) * (aToRange) + aToMin; 
        }

        return locReturn;
    }
    
    double map_point_exclude_zero(double aInput, double aToRange, double aToMin, int aFromRange, int aFromMin){
        double locReturn = 0;

        if(aInput == 0){
            return 0;
        }
        
        locReturn = (aInput - aFromMin)/(aFromRange) * (aToRange) + aToMin+1; 
        

        return locReturn;
    }
    
    /**
     * Computes the percent error between the ideal value and measured value.
     * @param aIdeal Ideal value
     * @param aMeasured Measured value
     * @return The percent error between the two values.
     */
    double percent_error(double aIdeal, double aMeasured){
        return( round((aMeasured-aIdeal)/aIdeal*100.0,2) );
    }
    
    /**
     * Rounds a decimal value to a specified number of places
     * @param aNumber The number to round
     * @param aPlaces The number of places to round off to
     * @return The rounded number.
     */
    double round(double aNumber, int aPlaces){
        double aPower = pow(10,aPlaces);

        double lRet = ((long)( (aNumber*aPower+0.5) ))/aPower;
        return lRet;

    }    
    
    /**
     * Converts a Pascal 48 bit real number into a double.
     * @param realValue The value to convert
     * @return The value converted into a double.
     */
    double real48ToDouble(char *aRealValue){

            double lMantissa = 1.0;
            char lExponent = aRealValue[0] - 129;
            
            for (int i = 46; i >= 8; i--){
                if ((aRealValue[i / 8] >> (i % 8)) & 0x01){
                    lMantissa += pow(2.0, i - 47);
                }
            }

            // Test for null value
            if (lMantissa == 1.0 && lExponent == 127){
                return 0.0;
            }

            // Sign bit check
            if (aRealValue[5] & 0x80){
                lMantissa *= -1.0;
            }
            
            return lMantissa * pow(2.0, lExponent);
    }
    
    double quotient(double aDividend, double aDivisor){
        return (long)(aDividend/aDivisor);
    }
    
    double remainderf(double aDividend, double aDivisor){
        return (aDividend/aDivisor-quotient(aDividend,aDivisor));
    }
    
    double modf(double aDividend, double aDivisor){
        return (remainderf(aDividend,aDivisor))*(aDivisor);
    }
    
    /*-------------------------------------------------------------------------
       Calculate the closest but lower power of two of a number
       twopm = 2**m <= n
       Return TRUE if 2**m == n
    */
    bool power_of_two(int n,int &m,int &twopm){
        if (n <= 1) {
            m = 0;
            twopm = 1;
            return(false);
        }

        m = 1;
        twopm = 2;
        
        do {
           m++;
           twopm *= 2;
        } while (2*(twopm) <= n);

        if (twopm != n){
           return(false);
        } else {
           return(true);
        }
    }
    

    /*-------------------------------------------------------------------------
       This computes an in-place complex-to-complex FFT
       x and y are the real and imaginary arrays of 2^m points.
       dir =  1 gives forward transform
       dir = -1 gives reverse transform

         Formula: forward
                      N-1
                      ---
                  1   \          - j k 2 pi n / N
          X(n) = ---   >   x(k) e                    = forward transform
                  N   /                                n=0..N-1
                      ---
                      k=0

          Formula: reverse
                      N-1
                      ---
                      \          j k 2 pi n / N
          X(n) =       >   x(k) e                    = forward transform
                      /                                n=0..N-1
                      ---
                      k=0
    */
    
    int FFT(int dir,int m, std::vector<double> &x, std::vector<double> &y){
        
        long nn,i,i1,j,k,i2,l,l1,l2;
        double c1,c2,tx,ty,t1,t2,u1,u2,z;

        /* Calculate the number of points */
        nn = 1;
        for (i=0;i<m;i++){
           nn *= 2;
        }
        
        /* Do the bit reversal */
        i2 = nn >> 1;
        j = 0;
        for (i=0;i<nn-1;i++) {
           if (i < j) {
              tx = x[i];
              ty = y[i];
              x[i] = x[j];
              y[i] = y[j];
              x[j] = tx;
              y[j] = ty;
           }
           k = i2;
           while (k <= j) {
              j -= k;
              k >>= 1;
           }
           j += k;
        }

        /* Compute the FFT */
        c1 = -1.0;
        c2 = 0.0;
        l2 = 1;
        for (l=0;l<m;l++) {
            l1 = l2;
            l2 <<= 1;
            u1 = 1.0;
            u2 = 0.0;
            for (j=0;j<l1;j++) {
                for (i=j;i<nn;i+=l2) {
                    i1 = i + l1;
                    t1 = u1 * x[i1] - u2 * y[i1];
                    t2 = u1 * y[i1] + u2 * x[i1];
                    x[i1] = x[i] - t1;
                    y[i1] = y[i] - t2;
                    x[i] += t1;
                    y[i] += t2;
                }
                z =  u1 * c1 - u2 * c2;
                u2 = u1 * c2 + u2 * c1;
                u1 = z;
            }
            c2 = sqrt((1.0 - c1) / 2.0);
            if (dir == 1){
                c2 = -c2;
            }
            c1 = sqrt((1.0 + c1) / 2.0);
        }

        /* Scaling for forward transform */
        if (dir == 1) {
            for (i=0;i<nn;i++) {
                x[i] /= (double)nn;
                y[i] /= (double)nn;
            }
        }

        return(true);
    }    
    
    double gauss(double x, double y, double x0, double y0, double A, double a, double b, double c){
        return A*exp(-1*(a*(x-x0)*(x-x0) - 2*b*(x-x0)*(y-y0) + c*(y-y0)*(y-y0)));
    }
    
    double gauss_dx(double x, double y, double x0, double y0, double A, double a, double b, double c){
        return A*(2*b*(y - y0) - 2*a*(x - x0))*exp(-a*(x - x0)*(x - x0) + 2*b*(x - x0)*(y - y0) - c*(y - y0)*(y - y0));
    }
    
    double gauss_dy(double x, double y, double x0, double y0, double A, double a, double b, double c){
        return A*(2*b*(x - x0) - 2*c*(y - y0))*exp(-a*(x - x0)*(x - x0) + 2*b*(x - x0)*(y - y0) - c*(y - y0)*(y - y0));
    }
    
    double normal_dist(double aX, double aMean, double aStdev){
        return 1/(aStdev*sqrt(2*M_PI))*exp(-.5*((aX-aMean)/aStdev)*((aX-aMean)/aStdev) );
    }
    
    std::vector<unsigned long> sieve_of_eratosthenes(long x) {
        unsigned long lNumbPrimes = 1;
        unsigned long lNumbInts = x;
        unsigned long lCurrentPrime = 2;

        std::vector<unsigned long> lPrimesTF(lNumbInts,1);
        std::vector<unsigned long> lPrimeList(x,0);

        lPrimesTF[0] = 0;
        lPrimesTF[1] = 0;
        lPrimeList[0] = 2;

        //while(lNumbPrimes < x) {
        for(unsigned long j = 0; j < sqrt(lNumbInts); j++){
            //std::cout << lNumbInts << " : " << lNumbPrimes << " : " << std::endl;
            //while(lNumbPrimes < x) {
            lCurrentPrime = lPrimeList[lNumbPrimes-1];
            for(unsigned long i = lCurrentPrime+1; i < lNumbInts; i++){
                if(lPrimesTF[i] != 0){
                    if(i%lCurrentPrime == 0){
                        lPrimesTF[i] = 0;
                    }
                }
            }

            for(unsigned long i = lCurrentPrime+1; i < lNumbInts; i++){
                if(lPrimesTF[i] == 1){
                    //std::cout << "Found: " << i << std::endl;
                    lPrimeList[lNumbPrimes] = i;
                    lNumbPrimes ++;
                    break;
                }
            }

        }

        return(lPrimesTF);
    }
    
    unsigned long prime_upper_bound(unsigned long x){

        double lUpperBound = x+1;
        double lLowerBound = lUpperBound*log(lUpperBound);
        double m  = lLowerBound/log(lLowerBound);

        unsigned long lRet = 0;

        while(m < x+1){
            m = lUpperBound/log(lUpperBound);
            lUpperBound += lLowerBound*0.01;
        }

        return lUpperBound;

    }
    
    unsigned long approx_prime(unsigned long x){

        double lUpperBound = x+1;
        double lLowerBound = lUpperBound*log(lUpperBound);
        double m  = lLowerBound/log(lLowerBound);

        unsigned long lRet = 0;

        while(m < x+1){
            m = lUpperBound/log(lUpperBound);
            lUpperBound += lLowerBound*0.01;
        }

        //std::cout << (long)lUpperBound << " : " << (long)lLowerBound << std::endl;
        lRet = round((lUpperBound+lLowerBound)/2+.5,0)*1.01;
        if(lRet%2 == 0){
            lRet--;
        }
        return lRet;

    }
    
    std::vector<unsigned long> sieve_two(unsigned long x){

        unsigned long MAX = x; //approx_prime(x);
        unsigned long SQRT_MAX = sqrt(MAX) + 1;
        std::vector<unsigned long> array(MAX,1);

        array[0] = false;
        array[1] = false;  

        //--//
        for (unsigned long i = 2; i < MAX; i++) {
            if (array[i]) {
                unsigned long j = i + i;
                while (j < MAX) {
                    array[j] = false;
                    j += i;
                }
            }
        }

        return array;

    }
    
    std::vector<unsigned long> primes(unsigned long x){

        
        //unsigned long n = approx_prime(x)+10;
        unsigned long n = prime_upper_bound(x);

        //NumericVector lPrimesTF = sieve_of_eratosthenes(n);
        std::vector<unsigned long> lPrimesTF = sieve_two(n);
        std::vector<unsigned long> lPrimeList(x,0);
        lPrimeList.at(0) = 2;
        
        unsigned long lCount = 0;
        for(unsigned long i = 0; i < lPrimesTF.size(); i++){
            
            if(lPrimesTF[i] == 1){
                if(lCount < lPrimeList.size() ){
                    lPrimeList[lCount] = i;
                    lCount ++;
                } else {
                    break;
                }
            }
        }

        return(lPrimeList);
    }
    
    unsigned long prime(unsigned long x){
        std::vector<unsigned long> lRet = primes(x);
        return (*(lRet.end()-1));
    }
    
    std::vector<unsigned long> factors(unsigned long x){

        std::vector<unsigned long> lFactorList;

        for(unsigned long i = 1; i <= x; i++){
            if(x%i == 0){
                lFactorList.push_back(i);
            }
        }


        return lFactorList;
    }
    
    std::vector<unsigned long> vectorized_pascals(std::vector<unsigned long>& input, unsigned long modular, unsigned long rowNumber){
        
        std::vector<unsigned long> P(input.size()+1,0);
        P.at(1) = 1;
        
        for(unsigned long n = 2; n < rowNumber+1; n++){
            P.at(n) = (input.at(n)+input.at(n-1))%modular;
        }
        
        return P;
    }
    
    void counting_rows(std::vector<unsigned long>& counts, std::vector<unsigned long>& input, unsigned long rowNumber){

        for(unsigned long a = 1; a < rowNumber+1; a++){
            counts.at(input.at(a)+1)++;
        }
        
        
    }
    
    unsigned long counting_every_row(unsigned long maxPrime){
        //std::cout << "Prime: " << prime(maxPrime) << std::endl;
        
        std::vector<unsigned long> x = primes(maxPrime);
        
        unsigned long lastRow = x.back();
        std::vector<unsigned long> counts(lastRow+1,0);
        std::vector<unsigned long> vectorize(lastRow+1,0);
        unsigned long modular = lastRow;
        
        for(unsigned long n = 1; n < lastRow+1; n++){
            vectorize = vectorized_pascals(vectorize,modular,n);
            counting_rows(counts,vectorize,n);
        }

        return counts.at(2);
        
    }
    
    std::vector<unsigned long> counting_every_row_all(unsigned long maxPrime){
        //std::cout << "Prime: " << prime(maxPrime) << std::endl;
        
        std::vector<unsigned long> x = primes(maxPrime);
        
        unsigned long lastRow = x.back();
        std::vector<unsigned long> counts(lastRow+1,0);
        std::vector<unsigned long> vectorize(lastRow+1,0);
        unsigned long modular = lastRow;
        
        for(unsigned long n = 1; n < lastRow+1; n++){
            vectorize = vectorized_pascals(vectorize,modular,n);
            counting_rows(counts,vectorize,n);
        }

        counts.at(0) = lastRow;
        return counts;
        
    }
    
//    std::vector<unsigned long> triangle_sieve(unsigned long x) {
//
//        std::vector<unsigned long> lPrimesTF(x,x);
//
//        for(unsigned long i = 1; i <= x; i++){
//
//            std::vector<unsigned long> lFactors = factors(i);
//
//            for(unsigned long j = 0; j < lFactors.size(); j++){
//                lPrimesTF(i-1,lFactors(j)-1) = 1;
//
//            }
//
//        }
//
//        return(lPrimesTF);
//
//    }
//    
//    std::vector<unsigned long> triangle_sieve_primes(unsigned long x) {
//
//        std::vector<unsigned long> lPrimesTF(x,x);
//
//        for(unsigned long i = 1; i <= x; i++){
//
//            std::vector<unsigned long> lFactors = factors(i);
//
//            for(unsigned long j = 0; j < lFactors.size(); j++){
//                lPrimesTF(i-1,lFactors(j)-1) = 1;
//
//            }
//
//            if(lFactors.size() == 2){
//                for(unsigned long j = 1; j < i-1; j++){
//                    lPrimesTF(i-1,j) = .25;
//                }
//            }
//
//        }
//
//        return(lPrimesTF);
//
//    }
    
}