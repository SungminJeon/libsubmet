#include <math.h>

#include "SPulse.h"

ClassImp(SPulse)

SPulse::SPulse() 
{
	Initialize();
}

SPulse::~SPulse()
{
}

void SPulse::Initialize()
{
	md_Mean      = 0;
	md_Var       = 0;
	md_Skew      = 0;
	md_Kurt      = 0;
	md_Threshold = 0;
	md_PedMean   = 0;
	md_Height    = 0;
	mi_N         = 0;
	mf_PeakTime  = 0;
	md_MeanTime  = 0;
	mv_Volts . clear();
	mv_Times . clear();
}

void SPulse::AddVolt(float volt)
{
	mv_Volts . push_back(volt);
	mi_N++;
}

void SPulse::AddTime(float time)
{
	mv_Times . push_back(time);
}

void SPulse::SetThreshold(double thold)
{
	md_Threshold = thold;
}

void SPulse::SetPedMean(double pM)
{
	md_PedMean = pM;
}

void SPulse::CalculateProperties()     
{
	// Initialize Properties 
	md_Mean     = 0;
	md_Var      = 0;
	md_Skew     = 0;
	md_Kurt     = 0;
	md_Height   = 0;
	md_MeanTime = 0;
	mf_PeakTime = 0;



	for ( unsigned short int i = 0; i < mi_N; i++ )
	{
		md_Mean += 1. * mv_Volts[i];
		md_Var  += 1. * mv_Volts[i] * mv_Volts[i];
		md_Skew += 1. * mv_Volts[i] * mv_Volts[i] * mv_Volts[i];
		md_Kurt += 1. * mv_Volts[i] * mv_Volts[i] * mv_Volts[i] * mv_Volts[i];

		md_MeanTime += 1. * mv_Times[i] * (md_PedMean - mv_Volts[i]);
		
		// Peak finding
		if ( i == 0 )
		{
			md_Height   = mv_Volts[i];
			mf_PeakTime = mv_Times[i];
		}
		else
		{
			if ( mv_Volts[i] < md_Height )
			{
				md_Height   = mv_Volts[i];
				mf_PeakTime = mv_Times[i];
			}
		}
	}

	md_Mean /= mi_N;
	md_Var  /= mi_N;
	md_Skew /= mi_N;
	md_Kurt /= mi_N;

	md_Kurt = md_Kurt
			- 4. * md_Mean * md_Skew
			+ 6. * md_Mean * md_Mean * md_Var
			- 3. * md_Mean * md_Mean * md_Mean * md_Mean;
	
	md_Skew = md_Skew
			- 3. * md_Mean * md_Var
			+ 2. * md_Mean * md_Mean * md_Mean;
		
	md_Var   = md_Var - md_Mean * md_Mean;

	md_Kurt /= md_Var * md_Var;
	md_Kurt -= 3.;
	md_Kurt  = ((mi_N + 1.) * md_Kurt + 6.) * (mi_N - 1.) / (mi_N - 2.) / (mi_N - 3.); // G2 definition

	md_Skew /= pow(md_Var, 1.5);
	md_Skew  = md_Skew * sqrt(mi_N * (mi_N - 1.)) / (mi_N - 2.);

	if ( mi_N < 4 ) md_Kurt = 0;
	if ( mi_N < 3 ) md_Skew = 0;

	// Post-process
	md_Mean = md_PedMean - md_Mean;
	md_MeanTime /= md_Mean * mi_N;
	md_Height = md_PedMean - md_Height;

	return;
}

void SPulse::CalculateProperties(float ut)     
{
	// Initialize Properties 
	md_Mean     = 0;
	md_Var      = 0;
	md_Skew     = 0;
	md_Kurt     = 0;
	md_Height   = 0;
	md_MeanTime = 0;
	mf_PeakTime = 0;

	for ( unsigned short int i = 0; i < mi_N; i++ )
	{
		md_Mean += 1. * mv_Volts[i] * ut;
		md_Var  += 1. * mv_Volts[i] * mv_Volts[i] * ut;
		md_Skew += 1. * mv_Volts[i] * mv_Volts[i] * mv_Volts[i] * ut;
		md_Kurt += 1. * mv_Volts[i] * mv_Volts[i] * mv_Volts[i] * mv_Volts[i] * ut;
		
		md_MeanTime += 1. * mv_Times[i] * (md_PedMean - mv_Volts[i]);
		
		// Peak finding
		if ( i == 0 )
		{
			md_Height   = mv_Volts[i];
			mf_PeakTime = mv_Times[i];
		}
		else
		{
			if ( mv_Volts[i] < md_Height )
			{
				md_Height   = mv_Volts[i];
				mf_PeakTime = mv_Times[i];
			}
		}
	}

	md_Mean /= mi_N * ut;
	md_Var  /= mi_N * ut;
	md_Skew /= mi_N * ut;
	md_Kurt /= mi_N * ut;

	md_Kurt = md_Kurt
			- 4. * md_Mean * md_Skew
			+ 6. * md_Mean * md_Mean * md_Var
			- 3. * md_Mean * md_Mean * md_Mean * md_Mean;
	
	md_Skew = md_Skew
			- 3. * md_Mean * md_Var
			+ 2. * md_Mean * md_Mean * md_Mean;
		
	md_Var   = md_Var - md_Mean * md_Mean;

	md_Kurt /= md_Var * md_Var;
	md_Kurt -= 3.;
	md_Kurt  = ((mi_N + 1.) * md_Kurt + 6.) * (mi_N - 1.) / (mi_N - 2.) / (mi_N - 3.); // G2 definition

	md_Skew /= pow(md_Var, 1.5);
	md_Skew  = md_Skew * sqrt(mi_N * (mi_N - 1.)) / (mi_N - 2.);

	if ( mi_N < 4 ) md_Kurt = 0;
	if ( mi_N < 3 ) md_Skew = 0;

	// Post-process
	md_Mean = md_PedMean - md_Mean;
	md_MeanTime /= md_Mean * mi_N * ut;
	md_Height = md_PedMean - md_Height;

	return;
}

void SPulse::CalculatePropertiesI()
{
	// Initialize Properties 
	md_Mean     = 0;
	md_Var      = 0;
	md_Skew     = 0;
	md_Kurt     = 0;
	md_Height   = 0;
	md_MeanTime = 0;
	mf_PeakTime = 0;
	

	// To get proper md_MeanTime
	md_MeanTime += 1. * mv_Times[mi_N - 1] * (md_PedMean - mv_Volts[mi_N - 1]);

	// Calculate properties with the non uniform time intervals.. i.e this method depends on time coordnates of the event.
	for ( unsigned short int i = 0; i < mi_N - 1; i++ )
	{
		md_Mean += 1. * (mv_Volts[i] + mv_Volts[i+1])  *  (mv_Times[i+1] - mv_Times[i]) / 2.0;
		md_Var  += 1. * (mv_Volts[i] * mv_Volts[i] + mv_Volts[i + 1] * mv_Volts[i+1])  *  (mv_Times[i+1] - mv_Times[i]) / 2.0;
		md_Skew += 1. * (mv_Volts[i] * mv_Volts[i] * mv_Volts[i] + mv_Volts[i+1] * mv_Volts[i+1] * mv_Volts[i+1])  *  (mv_Times[i+1] - mv_Times[i]) / 2.0 ;
		md_Kurt += 1. * (mv_Volts[i] * mv_Volts[i] * mv_Volts[i] * mv_Volts[i] + mv_Volts[i+1] * mv_Volts[i+1] * mv_Volts[i+1] * mv_Volts[i+1])  *  (mv_Times[i+1] - mv_Times[i]) / 2.0;

		md_MeanTime += 1. * mv_Times[i] * (md_PedMean - mv_Volts[i]);

		// Peak finding
		if ( i == 0 )
		{
			md_Height   = mv_Volts[i];
			mf_PeakTime = mv_Times[i];
		}
		else
		{
			if ( mv_Volts[i] < md_Height )
			{
				md_Height   = mv_Volts[i];
				mf_PeakTime = mv_Times[i];
			}
		}


	}

	if ( mv_Volts[mi_N - 1] < md_Height )
	{
		md_Height   = mv_Volts[mi_N - 1];
		mf_PeakTime = mv_Times[mi_N - 1];
	}

	md_Mean /= (mv_Times[mi_N - 1] - mv_Times[0]);
	md_Var  /= (mv_Times[mi_N - 1] - mv_Times[0]);
	md_Skew /= (mv_Times[mi_N - 1] - mv_Times[0]);
	md_Kurt /= (mv_Times[mi_N - 1] - mv_Times[0]);


	md_Kurt = md_Kurt
		- 4. * md_Mean * md_Skew
		+ 6. * md_Mean * md_Mean * md_Var
		- 3. * md_Mean * md_Mean * md_Mean * md_Mean;

	md_Skew = md_Skew
		- 3. * md_Mean * md_Var
		+ 2. * md_Mean * md_Mean * md_Mean;

	md_Var   = md_Var - md_Mean * md_Mean;

	md_Kurt /= md_Var * md_Var;
	md_Kurt -= 3.;
	// md_Kurt  = ((mi_N + 1.) * md_Kurt + 6.) * (mi_N - 1.) / (mi_N - 2.) / (mi_N - 3.); // in this method we use "g2" definition since we cannot define sample kurtosis definition in integral form

	md_Skew /= pow(md_Var, 1.5);
	// md_Skew  = md_Skew * sqrt(mi_N * (mi_N - 1.)) / (mi_N - 2.); // in this method we use "g1" definition since we cannot define sample skewness definition in integral form

	if ( mi_N < 4 ) md_Kurt = 0;
	if ( mi_N < 3 ) md_Skew = 0;

	// Post-process
	md_Mean = md_PedMean - md_Mean;
	md_MeanTime /= md_Mean * (mv_Times[mi_N - 1] - mv_Times[0]);
	md_Height = md_PedMean - md_Height;

	return;

}





double SPulse::GetMean()
{
	return md_Mean;
}

double SPulse::GetRMS()
{
	return sqrt(md_Var);
}

double SPulse::GetVar()
{
	return md_Var;
}

double SPulse::GetSkew()
{
	return md_Skew;
}

double SPulse::GetKurt()
{
	return md_Kurt;
}

double SPulse::GetHeight()
{
	return md_Height;
}

double SPulse::GetArea(bool mode)
{	
	// MODE "True"  = non - uniform time interval mode
	// MODE "False" = uniform time interval mode
	if ( mode == 1 )
	{
		return md_Mean * (mv_Times[mi_N - 1] - mv_Times[0]);
	}
	else 
	{
		return md_Mean * mi_N;
	}
}

unsigned short int SPulse::GetN()
{
	return mi_N;
}

std::vector<float> SPulse::GetVolts()
{
	return mv_Volts;
}

std::vector<float> SPulse::GetTimes()
{
	return mv_Times;
}

float SPulse::GetPeakTime()
{
	return mf_PeakTime;
}

double SPulse::GetMeanTime()
{
	return md_MeanTime;
}
