#include "Pulse.h"
#include <math.h>

ClassImp(Pulse)

Pulse::Pulse() 
{
	Initialize();
}
Pulse::~Pulse()
{
}
/*		

	

//		void AddVector(double nums);
 








	private:

		double mean;
		double rms;
		double var;
		double kurt1;
		double kurt2;
		double kurt3;
		double skew1;
		double skew2;
		double skew3;
		double threshold;
		double pedMean;
		double Height;
		double Area;
		std::vector<double> numbers;
		std::vector<double> time;

*/


void Pulse::Initialize()
{
       double mean       = 0;
       double rms        = 0;
       double var        = 0;
       double kurt1      = 0;
       double skew1      = 0;
       double threshold  = 0;
       double pedMean    = 0;
       double Height     = 0;
       double Area       = 0;
       double N          = 0;
       double PeakTiming = 0;
       numbers . clear();
       time    . clear();


}       

void Pulse::AddPoint(double num)
{
	numbers . push_back(num);
	N++;

}
void Pulse::AddTimeCoordinate(double tC)
{
	time . push_back(tC);

}

void Pulse::AddTimeCoordinate(int tC)
{
	time . push_back(tC);

}

void Pulse::SetThreshold(double thold)
{
	threshold = thold;
}

void Pulse::SetPedMean(double pM)
{
	pedMean = pM;
}

void Pulse::CalculateProperties()     // if one uses this method with 'for' segmentation violation error occures when using Event::PulseFinder() method.. what occurs this happen?????
{
	
	mean   = 0;
	rms    = 0;
	kurt1  = 0;
	skew1  = 0;
	var    = 0;
	Height = 0;
	Area   = 0;
        

	for ( int i = 0; i < N; i++)
	{
		mean  += numbers[i];
		var   += numbers[i] * numbers[i];
		skew1 += numbers[i] * numbers[i] * numbers[i];
		kurt1 += numbers[i] * numbers[i] * numbers[i] * numbers[i];
		Area  += numbers[i]; 

		if (i == 0)
		{
			Height     = numbers[i];
			PeakTiming = i;
		}
		else 
		{
			if ( numbers[i] < Height )
			{
				Height = numbers[i];
				PeakTiming = i;
			}
		}
		
	}
	

	/////// E(X^n) ///////
	mean /= N; 
	var /= N;
	skew1 /= N;
	kurt1 /= N;
        //////////////////////
	

	////// Calculate Kurtosis, Skewness, Variance, RMS, Mean ///////
	
	kurt1 = kurt1 - 4 * mean * skew1 + 6 * mean * mean * var - 3 * mean * mean * mean * mean;
	skew1 = skew1 - 3 * mean * var + 2 * mean * mean;
	
	var   = var - mean * mean;
	rms   = sqrt(var);

	kurt1 /= var * var;
	kurt1 *= ((N + 1.0) * kurt1 + 6.0) * (N - 1.0) / (N - 2.0) / (N - 3.0); // G2 definition

	skew1 /= rms * rms * rms;
	skew1 *= skew1 * sqrt(N * (N - 1.0)) / (N - 2.0);

	if ( N == 1 || N == 2 )
	{
		skew1 = 0;
		kurt1 = 0;
	}
	else if ( N == 3)
	{
		kurt1 = 0;
	}

	////// Calculate Pulse Height, Area //////
	
	Height = pedMean - Height;
	Area   = pedMean * N - Area;


	
	
}

double Pulse::GetMean()
{
	return mean;
}

double Pulse::GetRMS()
{
	return rms;
}

double Pulse::GetVar()
{
	return var;

}

double Pulse::GetSkew()
{
	return skew1;

}

double Pulse::GetKurt()
{
	return kurt1;

}

double Pulse::GetN()
{

	return N;
}

double Pulse::GetHeight()
{
	return Height;

}

double Pulse::GetArea()
{
	return Area;

}

std::vector<double> Pulse::GetPoints()
{
	return numbers;
}

std::vector<double> Pulse::GetTimeCoordinate()
{
	return time;
}

double Pulse::GetPeakTiming()
{
	return PeakTiming;
}


























