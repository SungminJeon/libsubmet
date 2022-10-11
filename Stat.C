#include "Stat.h"
#include <math.h>
//#include <iostream>
// 생성자 
Stat::Stat()
{
	Initialize();
}

// 소멸자
Stat::~Stat()
{
}

void Stat::Initialize()
{
	numbers . clear();
	mean  = 0;
	stdev = 0;
	var   = 0;
	rms   = 0;
	N     = 0;
	skew1 = 0; // g1
	skew2 = 0; // G1
	skew3 = 0; // b1
	kurt1 = 0; // g2
	kurt2 = 0; // G2
        kurt3 = 0; // b2
	max   = 0;
	min   = 0;
} 
double Stat::GetMean()
{
	return mean;
}

double Stat::GetStDev()
{
	return stdev;
}

double Stat::GetVar()
{
	return var;
}

double Stat::GetRMS()
{
	return rms;
}

double Stat::GetN()
{
	return N;
}

std::vector<double> Stat::GetNumbers()
{
	return numbers;
}
double Stat::GetSkew1()
{
	return skew1;
}
double Stat::GetSkew()
{
	return skew2;
}
double Stat::GetSkew3()
{
	return skew3;
}
double Stat::GetKurt1()
{
	return kurt1;
}
double Stat::GetKurt()
{
	return kurt2;
}
double Stat::GetKurt3()
{
	return kurt3;
}
double Stat::GetMax()
{
	return max;
}
double Stat::GetMin()
{
	return min;
}

void Stat::AddNumber(double num)
{
	numbers . push_back(num);
        
        ///// MOMENTS PART /////
	if (rms == 0)
	{
		///// PART1 : DERIVE N * E(X^n) FROM PREVIOUS MOMENTS /////
		kurt1 = 0;              
		kurt2 = 0;
		kurt3 = 0;
		skew1 = 0;
		skew2 = 0;
		skew3 = 0;
		stdev = 0;

		kurt1 *= rms * rms * rms * rms;
		kurt1 -= 3 * mean * mean * mean * mean;
		kurt1 -= 6 * mean * mean * rms * rms;
		kurt1 += 4 * mean * ((skew1 * rms * rms * rms) + (mean * mean * mean) + (3 * mean * rms * rms)); 
	        kurt1 *= N;

		skew1 *= rms * rms * rms;
		skew1 += mean * mean * mean;
		skew1 += 3 * mean * rms * rms;
		skew1 *= N;

		rms = rms * rms;
		rms += mean * mean;
		rms *= N; 
		mean *= N;

                ///// PART2 : CALCULATE E(X^n) INCLUDING 'num' THEN DERIVE MOMENTS /////
		N++;
		mean += num;
		mean /= N;
		rms += num * num;
		rms /= N;
		rms -= mean * mean;                
                stdev = rms * N / (N - 1);
		var = rms;
		rms = sqrt(rms);
		stdev = sqrt(stdev);
                

		if ( rms == 0)
		{
			skew1 = 0;
			kurt1 = -3;
		}
		else
		{
         		skew1 += num * num * num;
			skew1 /= N;
			skew1 -= 3 * mean * rms * rms;
			skew1 -= mean * mean * mean;
			skew1 /= rms * rms * rms;


			kurt1 += num * num * num * num;
			kurt1 /= N;
			kurt1 -= 4 * mean * ((skew1 * rms * rms * rms) + (mean * mean * mean) + 3 * (mean * rms * rms));
			kurt1 += 3 * mean * mean * mean * mean;
			kurt1 += 6 * mean * mean * rms * rms;
			kurt1 /= rms * rms * rms * rms;
			kurt1 -= 3;


		}

	}
	else
	{	


		
	        ///// PART1 : DERIVE N * E(X^n) FROM PREVIOUS MOMENTS /////
                kurt1 += 3.0;
	        kurt1 *= pow(rms, 4);
	        kurt1 -= 3.0 * pow(mean, 4);
	        kurt1 -= 6 * pow(mean, 2) * pow(rms, 2);
                kurt1 += 4 * mean * ((skew1 * rms * rms * rms) + (mean * mean * mean) + (3 * mean * rms * rms));
	        kurt1 *= N;

                skew1 *= rms * rms * rms;
                skew1 += mean * mean * mean;
	        skew1 += 3 * mean * rms * rms;
                skew1 *= N;

		rms = rms * rms;
		rms  += mean * mean;
		stdev = 0;    
	        skew2 = 0;    
	        skew3 = 0;    
	        kurt2 = 0;
	        kurt3 = 0;
	        mean *= N;
	        rms  *= N;
	
        	///// PART2 : CALCULATE E(X^n) INCLUDING 'num' THEN DERIVE MOMENTS /////
        	N++;

	        mean += num;
        	mean /= N;

	        rms += num * num;
        	rms /= N;
        	rms -= mean * mean;
	
        	stdev = rms * N / (N-1.0); 
		var = rms;
        	rms = sqrt(rms);
        	stdev = sqrt(stdev);
                if ( rms == 0.0)
		{
			skew1 = 0.0;
			kurt1 = -3.0;
		}
		else
		{
                 	skew1 += num * num * num;
                	skew1 /= N;
                    	skew1 -= 3.0 * mean * rms * rms;
                 	skew1 -= mean * mean * mean;
                   	skew1 /= rms * rms * rms;
        
	
	
                        kurt1 += num * num * num * num;
                    	kurt1 /= N;
                    	kurt1 -= 4.0 * mean * ((skew1 * rms * rms * rms) + (mean * mean * mean) + (3.0 * mean * rms * rms));
                 	kurt1 += 6.0 * mean * mean * rms * rms;
                     	kurt1 += 3.0 * mean * mean * mean * mean;
                        kurt1 /= rms * rms * rms * rms;
                     	kurt1 -= 3.0;
			
		}
                                      

	}
	skew3 = skew1 * sqrt((N - 1.0) * (N - 1.0) * (N - 1.0)) / sqrt(N * N * N);
	skew2 = skew3 * N * N / (N - 1.0) / (N - 2.0);

	kurt2 = ((N + 1.0) * kurt1 + 6.0) * (N - 1.0) / (N - 2.0) / (N - 3.0);
	kurt3 = (kurt1 + 3.0) * (1.0 - (2.0 / N) + (1.0 / N / N)) - 3.0;
	///// NOTES FOR ADDING HIGHER MOMENTUM : FOR DERIVE E(X^n) FROM MOMENTS, CONSIDER HIGHER MOMENTS FIRST /////		
			

			
	///// MAXIMUM, MINIMUM PART /////
	
        if ( N == 1 )
	{
		max = num;
		min = num;

	}
	else 
	{
		if ( max <= num )
		{
			max = num;
		}
		
		if ( min >= num )
		{
			min = num;
		}
	}


}
