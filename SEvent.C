#include <math.h>

#include "SEvent.h"

ClassImp(SEvent)

SEvent::SEvent()
{
	Initialize();
	mv_Ps = new TClonesArray("SPulse", 1366);
}

SEvent::SEvent(float roiS, float roiE)
{
	Initialize(roiS, roiE);
	mv_Ps = new TClonesArray("SPulse", 1366);
}

SEvent::~SEvent()
{
	mv_Ps -> Clear("C");

}

void SEvent::Initialize(float roiS, float roiE)
{
	md_Mean      = 0;
	md_Var       = 0;
	md_Skew      = 0;
	md_Kurt      = 0;
	mi_N         = 0;
	md_Threshold = 0;
	mb_SelfSup   = true;

	mv_Volts . clear();
	mv_Volts . reserve(4096);
	mv_Times . clear();
	mv_Times . reserve(4096);

	mi_NoP       = 0;
	mf_RoiStart  = roiS;
	mf_RoiEnd    = roiE;
}

void SEvent::AddVolt(float num)
{
	mv_Volts . push_back(num);
	mi_N++;
}
void SEvent::AddTime(float time)
{
	mv_Times . push_back(time);
}

void SEvent::SetThreshold(double thold)
{
	md_Threshold = thold;
}

	// mode for calculate properties 
	// 1. drs / need unit change coefficient as input variable i.e CalculateProperties(drs board case...)
	// 2. notice board

void SEvent::CalculateProperties(float ut)     
{
	// Initialize Properties
	md_Mean = 0;
	md_Var  = 0;
	md_Skew = 0;
	md_Kurt = 0;

	// Set local variables for initial, final point
	unsigned short int li_Start = 0; // convention: li = local integer variable
	unsigned short int li_End   = 0;


	// Find initial point
	for ( unsigned short int i = 0; i < mi_N; i++)
	{

		if ( mv_Times[i] >= mf_RoiStart )
		{
			li_Start = i;
			break;
		}
		
	}

	// Find final point 
	for ( unsigned short int i = mi_N - 1; i >= 0; i--)
	{
		if ( mv_Times[i] <= mf_RoiEnd )
		{
			li_End = i;
			break;
		}
	}

	for ( unsigned short int i = li_Start; i <= li_End; i++ )
	{
		md_Mean += 1. * mv_Volts[i] * ut;
		md_Var  += 1. * mv_Volts[i] * mv_Volts[i] * ut;
		md_Skew += 1. * mv_Volts[i] * mv_Volts[i] * mv_Volts[i] * ut;
		md_Kurt += 1. * mv_Volts[i] * mv_Volts[i] * mv_Volts[i] * mv_Volts[i] * ut;
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

	return;
}


void SEvent::CalculatePropertiesI()
{
	// Initialize Properties
	md_Mean = 0;
	md_Var  = 0;
	md_Skew = 0;
	md_Kurt = 0;

	// Set local variables for initial, final point
	unsigned short int li_Start = 0; // convention: li = local integer variable
	unsigned short int li_End   = 0;


	// Find initial point
	for ( unsigned short int i = 0; i < mi_N; i++)
	{

		if ( mv_Times[i] >= mf_RoiStart )
		{
			li_Start = i;
			break;
		}
		
	}

	// Find final point 
	for ( unsigned short int i = mi_N - 1; i >= 0; i--)
	{
		if ( mv_Times[i] <= mf_RoiEnd )
		{
			li_End = i;
			break;
		}
	}

			


	// Calculate properties with the non uniform time intervals.. i.e this method depends on time coordnates of the event.
	for ( unsigned short int i = li_Start; i < li_End; i++ )
	{
		md_Mean += 1. * (mv_Volts[i] + mv_Volts[i+1])  *  (mv_Times[i+1] - mv_Times[i]) / 2.0;
		md_Var  += 1. * (mv_Volts[i] * mv_Volts[i] + mv_Volts[i+1] * mv_Volts[i+1])  *  (mv_Times[i+1] - mv_Times[i]) / 2.0;
		md_Skew += 1. * (mv_Volts[i] * mv_Volts[i] * mv_Volts[i] + mv_Volts[i+1] * mv_Volts[i+1] * mv_Volts[i+1])  *  (mv_Times[i+1] - mv_Times[i]) / 2.0 ;
		md_Kurt += 1. * (mv_Volts[i] * mv_Volts[i] * mv_Volts[i] * mv_Volts[i] + mv_Volts[i+1] * mv_Volts[i+1] * mv_Volts[i+1] * mv_Volts[i+1])  *  (mv_Times[i+1] - mv_Times[i]) / 2.0;
	}

	md_Mean /= (mf_RoiEnd - mf_RoiStart);
	md_Var  /= (mf_RoiEnd - mf_RoiStart);
	md_Skew /= (mf_RoiEnd - mf_RoiStart);
	md_Kurt /= (mf_RoiEnd - mf_RoiStart);

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

	return;









}














std::vector<float> SEvent::GetNumbers()
{
	return mv_Volts;
}

std::vector<float> SEvent::GetTimes()
{
	return mv_Times;
}

double SEvent::GetMean() 
{

	return md_Mean;
}

double SEvent::GetVar()
{
	return md_Var;
}

double SEvent::GetRMS()
{
	return sqrt(md_Var);
}

double SEvent::GetSkew()
{
	return md_Skew;
}

double SEvent::GetKurt()
{
	return md_Kurt;
}

double SEvent::GetThreshold()
{
	return md_Threshold;
}

unsigned int SEvent::GetNumberOfPulses(double thold)
{
	/////////////////////////////////////////////////////////////////
	//////////// PART1:  Defining number of pulses///////////////////
	/////////////////////////////////////////////////////////////////

	unsigned int NumberofPulses;
	for ( int i = mf_RoiStart; i <= mf_RoiEnd; i++ )
	{
		if ( i == mf_RoiStart && mv_Volts[i] <= thold )
		{
			NumberofPulses = 1;
		}
		else if (  i > mf_RoiStart && i <= mf_RoiEnd )
		{


			if ( mv_Volts[i] <= thold && mv_Volts[i-1] > thold )  // 얘는 지금 시작할 때임
			{

				NumberofPulses++;	

			}
		}
	}


	return NumberofPulses;
}
unsigned int SEvent::GetNumberOfPulses()
{
	return mi_NoP;
}
double SEvent::GetEntries()
{
	return mi_N;
}

//////////////////////////////////////////////////////////////////////////////////
///////////////// PulseFinder for notice board ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// 1. Self Subtraction mode 
void SEvent::PulseFinderNotice(unsigned int ent)
{
	//////////////////////////////////////////////////////////////////
	///////////// PART0: Calculateing Properties of the  Event ///////
	//////////////////////////////////////////////////////////////////
	CalculateProperties();

	///////////////////////////////////////////////////////////////////
	///////////// PART1: Setting initial conditions ///////////////////
	///////////////////////////////////////////////////////////////////
	delete mv_Ps;
	mv_Ps = new TClonesArray("SPulse", 1366); // For preventing memory leaks due to duplicate declaration which might occur when one uses PulseFinder twice to same event class..
	md_Threshold = md_Mean - 10. * sqrt(md_Var); 
	mi_NoP = 0;
	SPulse* pulse;
	TClonesArray &PC = *mv_Ps; //FIXME



	///////////////////////////////////////////////////////////////////
	///////////// PART2: Finding Pulses and Making Pulse classes //////
	///////////////////////////////////////////////////////////////////

	// Set local variables for initial, final point
	unsigned short int li_Start = 0; // convention: li = local integer variable
	unsigned short int li_End   = 0;


	// Find initial point
	for ( unsigned short int i = 0; i < mi_N; i++)
	{

		if ( mv_Times[i] >= mf_RoiStart )
		{
			li_Start = i;
			break;
		}

	}

	// Find final point 
	for ( unsigned short int i = mi_N - 1; i >= 0; i--)
	{
		if ( mv_Times[i] <= mf_RoiEnd )
		{
			li_End = i;
			break;
		}
	}


	for ( int i = li_Start; i <= li_End; i++ )
	{
		if ( i == li_Start && mv_Volts[i] <= md_Threshold )
		{
			mi_NoP = 1;
			pulse = new (PC[mi_NoP-1]) SPulse(); // FIXME 
          		pulse -> AddVolt(mv_Volts[i]);
			pulse -> AddTime(i);
		}
		/*
		   if ( i == mf_RoiStart && numbers[i] > thold )
		   {
		   mi_NoP = 0;
		   }
		   */
		// 1. 펄스가 시작했을 때
		// 2. 펄스가 아직 안끝났을 때
		// 3. 펄스가 끝났을 때
		// 4. 펄스가 감지가 안됐을 때  네 상황으로 if문을 잘 구분해서 적어야.. 위의 세 상황이 아니므로 적을 필요가 없나?

		   else if (  i > li_Start && i < li_End )
		   {
			   if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold ) // 얘는 아직 안끝났을 때
			   {

				   pulse -> AddVolt(mv_Volts[i]);
      				   pulse -> AddTime(i);
			   }

			   else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold )  // 얘는 지금 시작할 때임
			   {

				   mi_NoP++;	// 
				   
				   pulse = new (PC[mi_NoP-1]) SPulse(); 
				   pulse -> AddVolt(mv_Volts[i]);
 				   pulse -> AddTime(i);	// NOTES ON AddTime(double time) method: should have overloading function AddTime(int time); DONE;

			   }
			   else if ( mv_Volts[i - 1] <= md_Threshold && mv_Volts[i] > md_Threshold ) // 펄스가 끝났을 때
			   {
				   if ( pulse -> GetN() > ent )		// FIXME
				   {
				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(md_Mean);
				   	pulse -> CalculateProperties();
				   }
				   else 
				   {	
					mv_Ps -> RemoveAt(mi_NoP-1);
					mi_NoP--;
				   }		
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
			   }

		   }
		   else if ( i == li_End )
		   {
			   if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold )
			   {
				   pulse -> AddVolt(mv_Volts[i]);
				   pulse -> AddTime(i);
				   if ( pulse -> GetN() > ent )		// FIXME
				   {
				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(md_Mean);
				   	pulse -> CalculateProperties();
				   }
				   else
				   {
					mv_Ps -> RemoveAt(mi_NoP-1);
					mi_NoP--;
				   }
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
	


			   }
			   else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold)
			   {
				   if ( ent < 1 )		// FIXME
				   {
				   	mi_NoP++;

				   	pulse = new (PC[mi_NoP-1]) SPulse();
				   	pulse -> AddVolt(mv_Volts[i]);
				   	pulse -> AddTime(i);

				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(md_Mean);
				   	pulse -> CalculateProperties();
				   }
			   }

		   }


	}



}




void SEvent::PulseFinderNotice(double pedMean, double thold, unsigned int ent)
{
	///////////////////////////////////////////////////////////////////
	///////////// PART1: Setting initial conditions ///////////////////
	///////////////////////////////////////////////////////////////////
	delete mv_Ps;
	mv_Ps = new TClonesArray("SPulse", 1366); // For preventing memory leaks due to duplicate declaration which might occur when one uses PulseFinder twice to same event class..
	md_Threshold = thold;
	mi_NoP = 0;
	SPulse* pulse;
	TClonesArray &PC = *mv_Ps; // FIXME

	///////////////////////////////////////////////////////////////////
	///////////// PART2: Finding Pulses and Making Pulse classes //////
	///////////////////////////////////////////////////////////////////

	// Set local variables for initial, final point
	unsigned short int li_Start = 0; // convention: li = local integer variable
	unsigned short int li_End   = 0;


	// Find initial point
	for ( unsigned short int i = 0; i < mi_N; i++)
	{

		if ( mv_Times[i] >= mf_RoiStart )
		{
			li_Start = i;
			break;
		}

	}

	// Find final point 
	for ( unsigned short int i = mi_N - 1; i >= 0; i--)
	{
		if ( mv_Times[i] <= mf_RoiEnd )
		{
			li_End = i;
			break;
		}
	}


	for ( int i = li_Start; i <= li_End; i++ )
	{
		if ( i == li_Start && mv_Volts[i] <= md_Threshold )
		{
			mi_NoP = 1;
			pulse = new (PC[mi_NoP-1]) SPulse(); // FIXME 
          		pulse -> AddVolt(mv_Volts[i]);
			pulse -> AddTime(i);
		}
		
		// 1. 펄스가 시작했을 때
		// 2. 펄스가 아직 안끝났을 때
		// 3. 펄스가 끝났을 때
		// 4. 펄스가 감지가 안됐을 때  네 상황으로 if문을 잘 구분해서 적어야.. 위의 세 상황이 아니므로 적을 필요가 없나?

		   else if (  i > li_Start && i < li_End )
		   {
			   if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold ) // 얘는 아직 안끝났을 때
			   {

				   pulse -> AddVolt(mv_Volts[i]);
      				   pulse -> AddTime(i);
			   }

			   else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold )  // 얘는 지금 시작할 때임
			   {

				   mi_NoP++;	// 
				   
				   pulse = new (PC[mi_NoP-1]) SPulse(); 
				   pulse -> AddVolt(mv_Volts[i]);
 				   pulse -> AddTime(i);	// NOTES ON AddTime(double time) method: should have overloading function AddTime(int time); DONE;

			   }
			   else if ( mv_Volts[i - 1] <= md_Threshold && mv_Volts[i] > md_Threshold ) // 펄스가 끝났을 때
			   {
				   if ( pulse -> GetN() > ent )
				   {
				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(pedMean);
				   	pulse -> CalculateProperties();
				   }
				   else 
				   {
					mv_Ps -> RemoveAt(mi_NoP-1);
					mi_NoP--;
				   }
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
			   }

		   }
		   else if ( i == li_End )
		   {
			   if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold )
			   {
				   pulse -> AddVolt(mv_Volts[i]);
				   pulse -> AddTime(i);
				   if ( pulse -> GetN() > ent )
				   {
				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(pedMean);
				   	pulse -> CalculateProperties();
				   }
				   else 
				   {
					mv_Ps -> RemoveAt(mi_NoP-1);
					mi_NoP--;
				   }
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
	


			   }
			   else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold)
			   {
				   if( ent < 1 )
				   {
				   	mi_NoP++;

				   	pulse = new (PC[mi_NoP-1]) SPulse();
				   	pulse -> AddVolt(mv_Volts[i]);
				   	pulse -> AddTime(i);

				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(pedMean);
				   	pulse -> CalculateProperties();
				   }
			   }

		   }


	}







}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// PulseFinder for drs4 evaluation board ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


//////////// 1. self subtraction mode ///////////////////////
void SEvent::PulseFinderDrs4(float ut, unsigned int ent)
{
	//////////////////////////////////////////////////////////////////
	///////////// PART0: Calculateing Properties of the  Event ///////
	//////////////////////////////////////////////////////////////////
	CalculateProperties(ut);

	///////////////////////////////////////////////////////////////////
	///////////// PART1: Setting initial conditions ///////////////////
	///////////////////////////////////////////////////////////////////
	delete mv_Ps;
	mv_Ps = new TClonesArray("SPulse", 1366); // For preventing memory leaks due to duplicate declaration which might occur when one uses PulseFinder twice to same event class..
	md_Threshold = md_Mean - 10. * sqrt(md_Var); 
	mi_NoP = 0;
	SPulse* pulse;
	TClonesArray &PC = *mv_Ps; //FIXME



	///////////////////////////////////////////////////////////////////
	///////////// PART2: Finding Pulses and Making Pulse classes //////
	///////////////////////////////////////////////////////////////////

	// Set local variables for initial, final point
	unsigned short int li_Start = 0; // convention: li = local integer variable
	unsigned short int li_End   = 0;


	// Find initial point
	for ( unsigned short int i = 0; i < mi_N; i++)
	{

		if ( mv_Times[i] >= mf_RoiStart )
		{
			li_Start = i;
			break;
		}

	}

	// Find final point 
	for ( unsigned short int i = mi_N - 1; i >= 0; i--)
	{
		if ( mv_Times[i] <= mf_RoiEnd )
		{
			li_End = i;
			break;
		}
	}

	for ( int i = li_Start; i <= li_End; i++ )
	{
		if ( i == li_Start && mv_Volts[i] <= md_Threshold )
		{
			mi_NoP = 1;
			pulse = new (PC[mi_NoP-1]) SPulse(); // FIXME 
          		pulse -> AddVolt(mv_Volts[i]);
			pulse -> AddTime(i * ut);
		}
		/*
		   if ( i == mf_RoiStart && numbers[i] > thold )
		   {
		   mi_NoP = 0;
		   }
		   */
		// 1. 펄스가 시작했을 때
		// 2. 펄스가 아직 안끝났을 때
		// 3. 펄스가 끝났을 때
		// 4. 펄스가 감지가 안됐을 때  네 상황으로 if문을 잘 구분해서 적어야.. 위의 세 상황이 아니므로 적을 필요가 없나?

		   else if (  i > li_Start && i < li_End)
		   {
			   if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold ) // 얘는 아직 안끝났을 때
			   {

				   pulse -> AddVolt(mv_Volts[i]);
      				   pulse -> AddTime(i * ut);
			   }

			   else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold )  // 얘는 지금 시작할 때임
			   {

				   mi_NoP++;	// 
				   
				   pulse = new (PC[mi_NoP-1]) SPulse(); 
				   pulse -> AddVolt(mv_Volts[i]);
 				   pulse -> AddTime(i * ut);	// NOTES ON AddTime(double time) method: should have overloading function AddTime(int time); DONE;

			   }
			   else if ( mv_Volts[i - 1] <= md_Threshold && mv_Volts[i] > md_Threshold ) // 펄스가 끝났을 때
			   {
				   if ( pulse -> GetN() > ent )
				   {
				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(md_Mean);
				   	pulse -> CalculateProperties(ut);
				   }
				   else
				   {
					mv_Ps -> RemoveAt(mi_NoP-1);
					mi_NoP--;
				   }
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
			   }

		   }
		   else if ( i == li_End)
		   {
			   if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold )
			   {
				   pulse -> AddVolt(mv_Volts[i]);
				   pulse -> AddTime(i * ut);

				   if ( pulse -> GetN() > ent )
				   {
				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(md_Mean);
				   	pulse -> CalculateProperties(ut);
				   }
				   else 
				   {
					mv_Ps -> RemoveAt(mi_NoP-1);
					mi_NoP--;
				   }
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
	


			   }
			   else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold)
			   {
				   if ( ent < 1 )
				   {
				   	mi_NoP++;

				   	pulse = new (PC[mi_NoP-1]) SPulse();
				   	pulse -> AddVolt(mv_Volts[i]);
				   	pulse -> AddTime(i * ut);

				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(md_Mean);
				   	pulse -> CalculateProperties(ut);
				   }
			   }

		   }


	}



}



////// 2. set pedestal mode
void SEvent::PulseFinderDrs4(float ut,  double pedMean, double thold, unsigned int ent)
{
	///////////////////////////////////////////////////////////////////
	///////////// PART1: Setting initial conditions ///////////////////
	///////////////////////////////////////////////////////////////////
	delete mv_Ps;
	mv_Ps = new TClonesArray("SPulse", 1366); // For preventing memory leaks due to duplicate declaration which might occur when one uses PulseFinder twice to same event class..
	md_Threshold = thold;
	mi_NoP = 0;
	SPulse* pulse;
	TClonesArray &PC = *mv_Ps; // FIXME

	///////////////////////////////////////////////////////////////////
	///////////// PART2: Finding Pulses and Making Pulse classes //////
	///////////////////////////////////////////////////////////////////
		
	// Set local variables for initial, final point
	unsigned short int li_Start = 0; // convention: li = local integer variable
	unsigned short int li_End   = 0;


	// Find initial point
	for ( unsigned short int i = 0; i < mi_N; i++)
	{

		if ( mv_Times[i] >= mf_RoiStart )
		{
			li_Start = i;
			break;
		}

	}

	// Find final point 
	for ( unsigned short int i = mi_N - 1; i >= 0; i--)
	{
		if ( mv_Times[i] <= mf_RoiEnd )
		{
			li_End = i;
			break;
		}
	}


	for ( int i = li_Start; i <= li_End; i++ )
	{
		if ( i == li_Start && mv_Volts[i] <= md_Threshold )
		{
			mi_NoP = 1;
			pulse = new (PC[mi_NoP-1]) SPulse(); // FIXME 
          		pulse -> AddVolt(mv_Volts[i]);
			pulse -> AddTime(i * ut);
		}
		/*
		   if ( i == mf_RoiStart && numbers[i] > thold )
		   {
		   mi_NoP = 0;
		   }
		   */
		// 1. 펄스가 시작했을 때
		// 2. 펄스가 아직 안끝났을 때
		// 3. 펄스가 끝났을 때
		// 4. 펄스가 감지가 안됐을 때  네 상황으로 if문을 잘 구분해서 적어야.. 위의 세 상황이 아니므로 적을 필요가 없나?

		   else if (  i > li_Start && i < li_End )
		   {
			   if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold ) // 얘는 아직 안끝났을 때
			   {

				   pulse -> AddVolt(mv_Volts[i]);
      				   pulse -> AddTime(i * ut);
			   }

			   else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold )  // 얘는 지금 시작할 때임
			   {

				   mi_NoP++;	// 
				   
				   pulse = new (PC[mi_NoP-1]) SPulse(); 
				   pulse -> AddVolt(mv_Volts[i]);
 				   pulse -> AddTime(i * ut);	// NOTES ON AddTime(double time) method: should have overloading function AddTime(int time); DONE;

			   }
			   else if ( mv_Volts[i - 1] <= md_Threshold && mv_Volts[i] > md_Threshold ) // 펄스가 끝났을 때
			   {
				   if ( pulse -> GetN() > ent )
				   {
				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(pedMean);
				   	pulse -> CalculateProperties(ut);
				   }
				   else
				   {
					mv_Ps -> RemoveAt(mi_NoP-1);
					mi_NoP--;
				   }
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
			   }

		   }
		   else if ( i == li_End )
		   {
			   if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold )
			   {
				   pulse -> AddVolt(mv_Volts[i]);
				   pulse -> AddTime(i * ut);
				   
				   if ( pulse -> GetN() > ent )
				   {
				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(pedMean);
				   	pulse -> CalculateProperties(ut);
				   }
				   else
				   {
					mv_Ps -> RemoveAt(mi_NoP-1);
					mi_NoP--;
				   }
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
	


			   }
			   else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold)
			   {
				   if ( ent < 1)
				   {
				   	mi_NoP++;

				   	pulse = new (PC[mi_NoP-1]) SPulse();
				   	pulse -> AddVolt(mv_Volts[i]);
				   	pulse -> AddTime(i * ut);

				   	pulse -> SetThreshold(md_Threshold);
				   	pulse -> SetPedMean(pedMean);
				   	pulse -> CalculateProperties(ut);
				   }
			   }

		   }


	}







}
void SEvent::PulseFinderN(bool selfsup, double pedMean, double thold, float ut, unsigned int ent)
{
	mb_SelfSup = selfsup;
		
	// Set local variables for initial, final point
	unsigned short int li_Start = 0; // convention: li = local integer variable
	unsigned short int li_End   = 0;


	// Find initial point
	for ( unsigned short int i = 0; i < mi_N; i++)
	{

		if ( mv_Times[i] >= mf_RoiStart )
		{
			li_Start = i;
			break;
		}

	}

	// Find final point 
	for ( unsigned short int i = mi_N - 1; i >= 0; i--)
	{
		if ( mv_Times[i] <= mf_RoiEnd )
		{
			li_End = i;
			break;
		}
	}

	if (mb_SelfSup == false)
	{
	
		///////////////////////////////////////////////////////////////////
		///////////// PART1: Setting initial conditions ///////////////////
		///////////////////////////////////////////////////////////////////
		delete mv_Ps;
		mv_Ps = new TClonesArray("SPulse", 1366); // For preventing memory leaks due to duplicate declaration which might occur when one uses PulseFinder twice to same event class..
		md_Threshold = thold;
		mi_NoP = 0;
		SPulse* pulse;
		TClonesArray &PC = *mv_Ps; // FIXME

		///////////////////////////////////////////////////////////////////
		///////////// PART2: Finding Pulses and Making Pulse classes //////
		///////////////////////////////////////////////////////////////////


		for ( int i = li_Start; i <= li_End; i++ )
		{
			if ( i == li_Start && mv_Volts[i] <= md_Threshold )
			{
				mi_NoP = 1;
				pulse = new (PC[mi_NoP-1]) SPulse(); // FIXME 
				pulse -> AddVolt(mv_Volts[i]);
				pulse -> AddTime(i * ut);
			}
			
			// 1. 펄스가 시작했을 때
			// 2. 펄스가 아직 안끝났을 때
			// 3. 펄스가 끝났을 때
			// 4. 펄스가 감지가 안됐을 때  네 상황으로 if문을 잘 구분해서 적어야.. 위의 세 상황이 아니므로 적을 필요가 없나?

			else if (  i > li_Start && i < li_End )
			{
				if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold ) // 얘는 아직 안끝났을 때
				{

					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(i * ut);
				}

				else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold )  // 얘는 지금 시작할 때임
				{

					mi_NoP++;	// 

					pulse = new (PC[mi_NoP-1]) SPulse(); 
					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(i * ut);	// NOTES ON AddTime(double time) method: should have overloading function AddTime(int time); DONE;

				}
				else if ( mv_Volts[i - 1] <= md_Threshold && mv_Volts[i] > md_Threshold ) // 펄스가 끝났을 때
				{
					if ( pulse -> GetN() > ent )
					{
						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(pedMean);
						pulse -> CalculateProperties(ut);
					}
					else
					{
						mv_Ps -> RemoveAt(mi_NoP-1);
						mi_NoP--;
					}
					// Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
					// if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
				}

			}
			else if ( i == li_End)
			{
				if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold )
				{
					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(i * ut);

					if ( pulse -> GetN() > ent )
					{
						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(pedMean);
						pulse -> CalculateProperties(ut);
					}
					else
					{
						mv_Ps -> RemoveAt(mi_NoP-1);
						mi_NoP--;
					}
					// Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
					// if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //



				}
				else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold)
				{
					if ( ent < 1)
					{
						mi_NoP++;

						pulse = new (PC[mi_NoP-1]) SPulse();
						pulse -> AddVolt(mv_Volts[i]);
						pulse -> AddTime(i * ut);

						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(pedMean);
						pulse -> CalculateProperties(ut);
					}
				}

			}


		}
	}
	else
	{
		//////////////////////////////////////////////////////////////////
		///////////// PART0: Calculateing Properties of the  Event ///////
		//////////////////////////////////////////////////////////////////
		CalculateProperties(ut);

		///////////////////////////////////////////////////////////////////
		///////////// PART1: Setting initial conditions ///////////////////
		///////////////////////////////////////////////////////////////////
		delete mv_Ps;
		mv_Ps = new TClonesArray("SPulse", 1366); // For preventing memory leaks due to duplicate declaration which might occur when one uses PulseFinder twice to same event class..
		md_Threshold = md_Mean - 10. * sqrt(md_Var); 
		mi_NoP = 0;
		SPulse* pulse;
		TClonesArray &PC = *mv_Ps; //FIXME



		///////////////////////////////////////////////////////////////////
		///////////// PART2: Finding Pulses and Making Pulse classes //////
		///////////////////////////////////////////////////////////////////


		for ( int i = li_Start; i <= li_End; i++ )
		{
			if ( i == li_Start && mv_Volts[i] <= md_Threshold )
			{
				mi_NoP = 1;
				pulse = new (PC[mi_NoP-1]) SPulse(); // FIXME 
				pulse -> AddVolt(mv_Volts[i]);
				pulse -> AddTime(i * ut);
			}
			
			// 1. 펄스가 시작했을 때
			// 2. 펄스가 아직 안끝났을 때
			// 3. 펄스가 끝났을 때
			// 4. 펄스가 감지가 안됐을 때  네 상황으로 if문을 잘 구분해서 적어야.. 위의 세 상황이 아니므로 적을 필요가 없나?

			else if (  i > li_Start && i < li_End)
			{
				if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold ) // 얘는 아직 안끝났을 때
				{

					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(i * ut);
				}

				else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold )  // 얘는 지금 시작할 때임
				{

					mi_NoP++;	// 

					pulse = new (PC[mi_NoP-1]) SPulse(); 
					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(i * ut);	// NOTES ON AddTime(double time) method: should have overloading function AddTime(int time); DONE;

				}
				else if ( mv_Volts[i - 1] <= md_Threshold && mv_Volts[i] > md_Threshold ) // 펄스가 끝났을 때
				{
					if ( pulse -> GetN() > ent )
					{
						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(md_Mean);
						pulse -> CalculateProperties(ut);
					}
					else
					{
						mv_Ps -> RemoveAt(mi_NoP-1);
						mi_NoP--;
					}
					// Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
					// if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
				}

			}
			else if ( i == li_End)
			{
				if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold )
				{
					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(i * ut);

					if ( pulse -> GetN() > ent )
					{
						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(md_Mean);
						pulse -> CalculateProperties(ut);
					}
					else 
					{
						mv_Ps -> RemoveAt(mi_NoP-1);
						mi_NoP--;
					}
					// Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
					// if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //



				}
				else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold)
				{
					if ( ent < 1 )
					{
						mi_NoP++;

						pulse = new (PC[mi_NoP-1]) SPulse();
						pulse -> AddVolt(mv_Volts[i]);
						pulse -> AddTime(i * ut);

						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(md_Mean);
						pulse -> CalculateProperties(ut);
					}
				}
			}
		}
	}
	

}
void SEvent::PulseFinderI(bool selfsup,  double pedMean, double thold, unsigned int ent)
{
	mb_SelfSup = selfsup;

	if (mb_SelfSup == false)
	{
	
		///////////////////////////////////////////////////////////////////
		///////////// PART1: Setting initial conditions ///////////////////
		///////////////////////////////////////////////////////////////////
		delete mv_Ps;
		mv_Ps = new TClonesArray("SPulse", 1366); // For preventing memory leaks due to duplicate declaration which might occur when one uses PulseFinder twice to same event class..
		md_Threshold = thold;
		mi_NoP = 0;
		SPulse* pulse;
		TClonesArray &PC = *mv_Ps; // FIXME

		///////////////////////////////////////////////////////////////////
		///////////// PART2: Finding Pulses and Making Pulse classes //////
		///////////////////////////////////////////////////////////////////

		// Set local variables for initial, final point
		unsigned short int li_Start = 0; // convention: li = local integer variable
		unsigned short int li_End   = 0;


		// Find initial point
		for ( unsigned short int i = 0; i < mi_N; i++)
		{

			if ( mv_Times[i] >= mf_RoiStart )
			{
				li_Start = i;
				break;
			}

		}

		// Find final point 
		for ( unsigned short int i = mi_N - 1; i >= 0; i--)
		{
			if ( mv_Times[i] <= mf_RoiEnd )
			{
				li_End = i;
				break;
			}
		}

		for ( int i = li_Start; i <= li_End; i++ )
		{
			if ( i == li_Start && mv_Volts[i] <= md_Threshold )
			{
				mi_NoP = 1;
				pulse = new (PC[mi_NoP-1]) SPulse(); // FIXME 
				pulse -> AddVolt(mv_Volts[i]);
				pulse -> AddTime(mv_Times[i]);
			}
			
			// 1. 펄스가 시작했을 때
			// 2. 펄스가 아직 안끝났을 때
			// 3. 펄스가 끝났을 때
			// 4. 펄스가 감지가 안됐을 때  네 상황으로 if문을 잘 구분해서 적어야.. 위의 세 상황이 아니므로 적을 필요가 없나?

			else if (  i > li_Start && i < li_End )
			{
				if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold ) // 얘는 아직 안끝났을 때
				{

					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(mv_Times[i]);
				}

				else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold )  // 얘는 지금 시작할 때임
				{

					mi_NoP++;	// 

					pulse = new (PC[mi_NoP-1]) SPulse(); 
					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(mv_Times[i]);	// NOTES ON AddTime(double time) method: should have overloading function AddTime(int time); DONE;

				}
				else if ( mv_Volts[i - 1] <= md_Threshold && mv_Volts[i] > md_Threshold ) // 펄스가 끝났을 때
				{
					if ( pulse -> GetN() > ent )
					{
						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(pedMean);
						pulse -> CalculatePropertiesI();
					}
					else
					{
						mv_Ps -> RemoveAt(mi_NoP-1);
						mi_NoP--;
					}
					// Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
					// if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
				}

			}
			else if ( i == li_End )
			{
				if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold )
				{
					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(mv_Times[i]);

					if ( pulse -> GetN() > ent )
					{
						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(pedMean);
						pulse -> CalculatePropertiesI();
					}
					else
					{
						mv_Ps -> RemoveAt(mi_NoP-1);
						mi_NoP--;
					}
					// Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
					// if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //



				}
				else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold)
				{
					if ( ent < 1)
					{
						mi_NoP++;

						pulse = new (PC[mi_NoP-1]) SPulse();
						pulse -> AddVolt(mv_Volts[i]);
						pulse -> AddTime(mv_Times[i]);

						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(pedMean);
						pulse -> CalculatePropertiesI();
					}
				}

			}


		}
	}
	else
	{
		//////////////////////////////////////////////////////////////////
		///////////// PART0: Calculateing Properties of the  Event ///////
		//////////////////////////////////////////////////////////////////
		CalculatePropertiesI();

		///////////////////////////////////////////////////////////////////
		///////////// PART1: Setting initial conditions ///////////////////
		///////////////////////////////////////////////////////////////////
		delete mv_Ps;
		mv_Ps = new TClonesArray("SPulse", 1366); // For preventing memory leaks due to duplicate declaration which might occur when one uses PulseFinder twice to same event class..
		md_Threshold = md_Mean - 10. * sqrt(md_Var); 
		mi_NoP = 0;
		SPulse* pulse;
		TClonesArray &PC = *mv_Ps; //FIXME



		///////////////////////////////////////////////////////////////////
		///////////// PART2: Finding Pulses and Making Pulse classes //////
		///////////////////////////////////////////////////////////////////

		// Set local variables for initial, final point
		unsigned short int li_Start = 0; // convention: li = local integer variable
		unsigned short int li_End   = 0;


		// Find initial point
		for ( unsigned short int i = 0; i < mi_N; i++)
		{

			if ( mv_Times[i] >= mf_RoiStart )
			{
				li_Start = i;
				break;
			}

		}

		// Find final point 
		for ( unsigned short int i = mi_N - 1; i >= 0; i--)
		{
			if ( mv_Times[i] <= mf_RoiEnd )
			{
				li_End = i;
				break;
			}
		}

		for ( int i = li_Start; i <= li_End; i++ )
		{
			if ( i == li_Start && mv_Volts[i] <= md_Threshold )
			{
				mi_NoP = 1;
				pulse = new (PC[mi_NoP-1]) SPulse(); // FIXME 
				pulse -> AddVolt(mv_Volts[i]);
				pulse -> AddTime(mv_Times[i]);
			}
			
			// 1. 펄스가 시작했을 때
			// 2. 펄스가 아직 안끝났을 때
			// 3. 펄스가 끝났을 때
			// 4. 펄스가 감지가 안됐을 때  네 상황으로 if문을 잘 구분해서 적어야.. 위의 세 상황이 아니므로 적을 필요가 없나?

			else if (  i > li_Start && i < li_End)
			{
				if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold ) // 얘는 아직 안끝났을 때
				{

					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(mv_Times[i]);
				}

				else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold )  // 얘는 지금 시작할 때임
				{

					mi_NoP++;	// 

					pulse = new (PC[mi_NoP-1]) SPulse(); 
					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(mv_Times[i]);	// NOTES ON AddTime(double time) method: should have overloading function AddTime(int time); DONE;

				}
				else if ( mv_Volts[i - 1] <= md_Threshold && mv_Volts[i] > md_Threshold ) // 펄스가 끝났을 때
				{
					if ( pulse -> GetN() > ent )
					{
						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(md_Mean);
						pulse -> CalculatePropertiesI();
					}
					else
					{
						mv_Ps -> RemoveAt(mi_NoP-1);
						mi_NoP--;
					}
					// Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
					// if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //
				}

			}
			else if ( i == li_End)
			{
				if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] <= md_Threshold )
				{
					pulse -> AddVolt(mv_Volts[i]);
					pulse -> AddTime(mv_Times[i]);

					if ( pulse -> GetN() > ent )
					{
						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(md_Mean);
						pulse -> CalculatePropertiesI();
					}
					else 
					{
						mv_Ps -> RemoveAt(mi_NoP-1);
						mi_NoP--;
					}
					// Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
					// if( pulse -> GetN() < 4 ) { pulse -> Initialize();, mi_NoP--; //



				}
				else if ( mv_Volts[i] <= md_Threshold && mv_Volts[i-1] > md_Threshold)
				{
					if ( ent < 1 )
					{
						mi_NoP++;

						pulse = new (PC[mi_NoP-1]) SPulse();
						pulse -> AddVolt(mv_Volts[i]);
						pulse -> AddTime(mv_Times[i]);

						pulse -> SetThreshold(md_Threshold);
						pulse -> SetPedMean(md_Mean);
						pulse -> CalculatePropertiesI();
					}
				}
			}

		}
	}


}


///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// NOTES ON PulseFinder(thold) method /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////



// Algorithm
// 1. Find pulse's initial point and call mv_Ps[mi_NoP-1] and allocate dynamic memory to this (which is Pulse class)
// 2. Definition of initial pulse point at the mf_RoiStart: if numbers[mf_RoiStart] <= thold; -> pulse started 
// 3. pulse -> SetPedMean(mean);, pulse -> SetThreshold(thold);, pulse -> CalculateProperties(); should be added to put all properties of pulses in pulse class(pulse class do not calculate properties automatically.) 

// NOTES ON TClonesArray
// 1. TClonesArray* mv_Ps -> defined as pointer in header file
// 2. When class Event constructed, Constructor of this class immediately allocate heap memories to mv_Ps
// 3. When class Event destructed, mv_Ps -> Clear("C"); in destructor makes all heap memories that allocated to mv_Ps free








/*
void SEvent::ChangeSigWindow(double sS, double sE)
{

	mf_RoiStart = sS;
	mf_RoiEnd   = sE;
	N        = 0;
	mean     = 0;
	rms      = 0;
	var      = 0;
	skew1    = 0;
	skew2    = 0;
	skew3    = 0;
	kurt1    = 0;
	kurt2    = 0;
	kurt3    = 0;



	for ( int i = mf_RoiStart; i <= mf_RoiEnd; i++)
	{
		if ( i >= mf_RoiStart )
		{
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
				//				stdev = 0;

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
				mean += numbers[i];
				mean /= N;
				rms += numbers[i] * numbers[i];
				rms /= N;
				rms -= mean * mean;                
				//				stdev = rms * N / (N - 1);
				var = rms;
				rms = sqrt(rms);
				//				stdev = sqrt(stdev);


				if ( rms == 0)
				{
					skew1 = 0;
					kurt1 = -3;
				}
				else
				{
					skew1 += numbers[i] * numbers[i] * numbers[i];
					skew1 /= N;
					skew1 -= 3 * mean * rms * rms;
					skew1 -= mean * mean * mean;
					skew1 /= rms * rms * rms;


					kurt1 += numbers[i] * numbers[i] * numbers[i] * numbers[i];
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
				//				stdev = 0;    
				skew2 = 0;    
				skew3 = 0;    
				kurt2 = 0;
				kurt3 = 0;
				mean *= N;
				rms  *= N;

				///// PART2 : CALCULATE E(X^n) INCLUDING 'num' THEN DERIVE MOMENTS /////
				N++;

				mean += numbers[i];
				mean /= N;

				rms += numbers[i] * numbers[i];
				rms /= N;
				rms -= mean * mean;

				//				stdev = rms * N / (N-1.0); 
				var = rms;
				rms = sqrt(rms);
				//				stdev = sqrt(stdev);
				if ( rms == 0.0)
				{
					skew1 = 0.0;
					kurt1 = -3.0;
				}
				else
				{
					skew1 += numbers[i] * numbers[i] * numbers[i];
					skew1 /= N;
					skew1 -= 3.0 * mean * rms * rms;
					skew1 -= mean * mean * mean;
					skew1 /= rms * rms * rms;



					kurt1 += numbers[i] * numbers[i] * numbers[i] * numbers[i];
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
		}




	}
	if ( N == 1 || N == 2 )
	{
		skew1 = 0;
		skew2 = 0;
		skew3 = 0;
		kurt1 = 0;
		kurt2 = 0;
		kurt3 = 0;
	}
	else if ( N == 3)
	{
		kurt1 = 0;
		kurt2 = 0;
		kurt3 = 0;
	}
}
*/


SPulse* SEvent::GetPulse(int i)
{
        SPulse* pulse = (SPulse*) mv_Ps -> At(i);
	return pulse; 
}

TClonesArray* SEvent::GetPulses()
{
	return mv_Ps;
}

void SEvent::ClearPulseContainer()
{
	mv_Ps -> Clear();
}


