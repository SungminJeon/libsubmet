#include <math.h>
#include "Event.h"
#include "Pulse.h"




Event::Event()
{
	Initialize();
}

Event::Event(double sS, double sE)
{

	Initialize();
	sigStart = sS;
	sigEnd   = sE;
}
Event::Event(double sS, double sE, double thold)
{
	Initialize();
	sigStart  = sS;
	sigEnd    = sE;
	threshold = thold;
}

Event::~Event()
{
	// all pointer should return its heap memories
	//	delete pPulseContainer;
	PulseContainer -> Clear("C");

}

void Event::Initialize()
{
	numbers . clear();
	double mean      = 0;
	double rms       = 0;
	double var       = 0;
	double skew1     = 0;
	double skew2     = 0;
	double skew3     = 0;
	double kurt1     = 0;
	double kurt2     = 0;
	double kurt3     = 0;
	double nop       = 0;
	double sigStart  = 0;
	double sigEnd    = 4095;
	double N         = 0;   
	double entries   = 0;
	double threshold = 0;
	//	PulseContainer . Clear("C"); // For preventing memory leaks
	PulseContainer = new TClonesArray("Pulse", 1000);


}
/*
void Event::Initialize(double sS, double sE)
{
	numbers . clear();
	double mean      = 0;
	double rms       = 0;
	double var       = 0;
	double skew1     = 0;
	double skew2     = 0;
	double skew3     = 0;
	double kurt1     = 0;
	double kurt2     = 0;
	double kurt3     = 0;
	double nop       = 0;
	double sigStart  = sS;
	double sigEnd    = sE;
	double N         = 0;   
	double entries   = 0;
	double threshold = 0;
	PulseContainer = new TClonesArray("Pulse", 1000);

}
void Event::Initialize(double sS, double sE, double thold)
{
	numbers . clear();
	double mean      = 0;
	double rms       = 0;
	double var       = 0;
	double skew1     = 0;
	double skew2     = 0;
	double skew3     = 0;
	double kurt1     = 0;
	double kurt2     = 0;
	double kurt3     = 0;
	double nop       = 0;
	double sigStart  = sS;
	double sigEnd    = sE;
	double N         = 0;   
	double entries   = 0;
	double threshold = thold;
	PulseContainer = new TClonesArray("Pulse", 1000);

}
*/

// TO DO LIST //
// 1. Exception for skew, kurt (i.e. return 0 when they are not defined in N entries)
// 2. use another method to pulsecontainer actually contain properties of pulses
// 3. make methods to access the pulse informations (i.e. GetPulse(i) { return  PulseContainer -> At(i);  } )
// 4. complete CalculateProperties() in the Pulse.C 
//
//
//
//
//
//
//
void Event::AddPoint(double num)
{

	numbers . push_back(num);



	///// Choosing signal window /////
	if ( entries + 1 >= sigStart + 1  && entries + 1 <= sigEnd + 1 )
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
			//			stdev = 0;

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
			//			stdev = rms * N / (N - 1);
			var = rms;
			rms = sqrt(rms);
			//			stdev = sqrt(stdev);


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
			//			stdev = 0;    
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

			//			stdev = rms * N / (N-1.0); 
			var = rms;
			rms = sqrt(rms);
			//			stdev = sqrt(stdev);
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

	entries++;	


}


// List of private members
// 1. mean
// 2. rms
// 3. var
// 4. skew
// 5. kurt
// 6. number of pulses
// 7. TClonesArray of pulses
//
//
//
// List of methods
// 1. void Initialize()
// 2. void AddPoint()
// 3. void AddVector()
//




std::vector<double> Event::GetNumbers()
{
	return numbers;
}

double Event::GetMean() 
{

	return mean;
}

double Event::GetVar()
{
	return var;
}

double Event::GetRMS()
{
	return rms;
}

double Event::GetSkew()
{
	return skew2;
}

double Event::GetKurt()
{
	return kurt2;
}

double Event::GetThreshold()
{
	return threshold;
}

unsigned int Event::GetNumberOfPulses(double thold)
{
	/////////////////////////////////////////////////////////////////
	//////////// PART1:  Defining number of pulses///////////////////
	/////////////////////////////////////////////////////////////////

	nop = 0;
	threshold = thold;
	for ( int i = sigStart; i <= sigEnd; i++ )
	{
		if ( i == sigStart && numbers[i] <= thold )
		{
			nop = 1;
		}
		else if (  i > sigStart && i <= sigEnd )
		{


			if ( numbers[i] <= thold && numbers[i-1] > thold )  // 얘는 지금 시작할 때임
			{

				nop++;	

			}




		}
	}


	return nop;
}
unsigned int Event::GetNumberOfPulses()
{
	return nop;
}
double Event::GetEntries()
{
	return entries;
}


void Event::PulseFinder(double thold)
{
	///////////////////////////////////////////////////////////////////
	///////////// PART1: Setting initial conditions ///////////////////
	///////////////////////////////////////////////////////////////////
	threshold = thold;
	nop = 0;
	Pulse* pulse;
	TClonesArray &PC = *PulseContainer;



	///////////////////////////////////////////////////////////////////
	///////////// PART2: Finding Pulses and Making Pulse classes //////
	///////////////////////////////////////////////////////////////////


	for ( int i = sigStart; i <= sigEnd; i++ )
	{
		if ( i == sigStart && numbers[i] <= thold )
		{
			nop = 1;
			pulse = new (PC[nop-1]) Pulse(); // FIXME 
          		pulse -> AddPoint(numbers[i]);
			pulse -> AddTimeCoordinate(i);
		}
		/*
		   if ( i == sigStart && numbers[i] > thold )
		   {
		   nop = 0;
		   }
		   */
		// 1. 펄스가 시작했을 때
		// 2. 펄스가 아직 안끝났을 때
		// 3. 펄스가 끝났을 때
		// 4. 펄스가 감지가 안됐을 때  네 상황으로 if문을 잘 구분해서 적어야.. 위의 세 상황이 아니므로 적을 필요가 없나?

		   else if (  i > sigStart && i < sigEnd )
		   {
			   if ( numbers[i] <= thold && numbers[i-1] <= thold ) // 얘는 아직 안끝났을 때
			   {

				   pulse -> AddPoint(numbers[i]);
      				   pulse -> AddTimeCoordinate(i);
			   }

			   else if ( numbers[i] <= thold && numbers[i-1] > thold )  // 얘는 지금 시작할 때임
			   {

				   nop++;	// 
				   
				   pulse = new (PC[nop-1]) Pulse(); 
				   pulse -> AddPoint(numbers[i]);
 				   pulse -> AddTimeCoordinate(i);	// NOTES ON AddTimeCoordinate(double time) method: should have overloading function AddTimeCoordinate(int time); DONE;

			   }
			   else if ( numbers[i - 1] <= thold && numbers[i] > thold ) // 펄스가 끝났을 때
			   {
				   pulse -> SetThreshold(thold);
				   pulse -> SetPedMean(mean);
				   pulse -> CalculateProperties();
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, nop--; //
			   }

		   }
		   else if ( i == sigEnd )
		   {
			   if ( numbers[i] <= thold && numbers[i-1] <=thold )
			   {
				   pulse -> AddPoint(numbers[i]);
				   pulse -> AddTimeCoordinate(i);
				   pulse -> SetThreshold(thold);
				   pulse -> SetPedMean(mean);
				   pulse -> CalculateProperties();
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, nop--; //
	


			   }
			   else if ( numbers[i] <= thold && numbers[i-1] > thold)
			   {
				   nop++;

				   pulse = new (PC[nop-1]) Pulse();
				   pulse -> AddPoint(numbers[i]);
				   pulse -> AddTimeCoordinate(i);

				   pulse -> SetThreshold(thold);
				   pulse -> SetPedMean(mean);
				   pulse -> CalculateProperties();
			   }

		   }


	}



}




void Event::PulseFinder(double pedestal, double thold)
{
	///////////////////////////////////////////////////////////////////
	///////////// PART1: Setting initial conditions ///////////////////
	///////////////////////////////////////////////////////////////////
	threshold = thold;
	nop = 0;
	Pulse* pulse;
	TClonesArray &PC = *PulseContainer;



	///////////////////////////////////////////////////////////////////
	///////////// PART2: Finding Pulses and Making Pulse classes //////
	///////////////////////////////////////////////////////////////////


	for ( int i = sigStart; i <= sigEnd; i++ )
	{
		if ( i == sigStart && numbers[i] <= thold )
		{
			nop = 1;
			pulse = new (PC[nop-1]) Pulse(); // FIXME 
          		pulse -> AddPoint(numbers[i]);
			pulse -> AddTimeCoordinate(i);
		}
		/*
		   if ( i == sigStart && numbers[i] > thold )
		   {
		   nop = 0;
		   }
		   */
		// 1. 펄스가 시작했을 때
		// 2. 펄스가 아직 안끝났을 때
		// 3. 펄스가 끝났을 때
		// 4. 펄스가 감지가 안됐을 때  네 상황으로 if문을 잘 구분해서 적어야.. 위의 세 상황이 아니므로 적을 필요가 없나?

		   else if (  i > sigStart && i < sigEnd )
		   {
			   if ( numbers[i] <= thold && numbers[i-1] <= thold ) // 얘는 아직 안끝났을 때
			   {

				   pulse -> AddPoint(numbers[i]);
      				   pulse -> AddTimeCoordinate(i);
			   }

			   else if ( numbers[i] <= thold && numbers[i-1] > thold )  // 얘는 지금 시작할 때임
			   {

				   nop++;	// 
				   
				   pulse = new (PC[nop-1]) Pulse(); 
				   pulse -> AddPoint(numbers[i]);
 				   pulse -> AddTimeCoordinate(i);	// NOTES ON AddTimeCoordinate(double time) method: should have overloading function AddTimeCoordinate(int time); DONE;

			   }
			   else if ( numbers[i - 1] <= thold && numbers[i] > thold ) // 펄스가 끝났을 때
			   {
				   pulse -> SetThreshold(thold);
				   pulse -> SetPedMean(pedestal);
				   pulse -> CalculateProperties();
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, nop--; //
			   }

		   }
		   else if ( i == sigEnd )
		   {
			   if ( numbers[i] <= thold && numbers[i-1] <=thold )
			   {
				   pulse -> AddPoint(numbers[i]);
				   pulse -> AddTimeCoordinate(i);
				   pulse -> SetThreshold(thold);
				   pulse -> SetPedMean(pedestal);
				   pulse -> CalculateProperties();
                                   // Pulse rejection: if Pulse entires are fewer than 4 -> sample kurtosis and skewness cannot be defined.. 
				   // if( pulse -> GetN() < 4 ) { pulse -> Initialize();, nop--; //
	


			   }
			   else if ( numbers[i] <= thold && numbers[i-1] > thold)
			   {
				   nop++;

				   pulse = new (PC[nop-1]) Pulse();
				   pulse -> AddPoint(numbers[i]);
				   pulse -> AddTimeCoordinate(i);

				   pulse -> SetThreshold(thold);
				   pulse -> SetPedMean(pedestal);
				   pulse -> CalculateProperties();
			   }

		   }


	}



}




///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// NOTES ON PulseFinder(thold) method /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////



// Algorithm
// 1. Find pulse's initial point and call PulseContainer[nop-1] and allocate dynamic memory to this (which is Pulse class)
// 2. Definition of initial pulse point at the sigStart: if numbers[sigStart] <= thold; -> pulse started 
// 3. pulse -> SetPedMean(mean);, pulse -> SetThreshold(thold);, pulse -> CalculateProperties(); should be added to put all properties of pulses in pulse class(pulse class do not calculate properties automatically.) 

// NOTES ON TClonesArray
// 1. TClonesArray* PulseContainer -> defined as pointer in header file
// 2. When class Event constructed, Constructor of this class immediately allocate heap memories to PulseContainer
// 3. When class Event destructed, PulseContainer -> Clear("C"); in destructor makes all heap memories that allocated to PulseContainer free









void Event::ChangeSigWindow(double sS, double sE)
{

	sigStart = sS;
	sigEnd   = sE;
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



	for ( int i = sigStart; i <= sigEnd; i++)
	{
		if ( i >= sigStart )
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



Pulse* Event::GetPulse(int i)
{
        Pulse* pulse = (Pulse*) PulseContainer -> At(i);
	return pulse; 
}

TClonesArray* Event::GetPulses()
{
	return PulseContainer;
}
