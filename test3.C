#include "Pulse.h"
#include "SEvent.h"
#include "Stat.h"


void test3() 
{

	gSystem -> Load("libsubmet.so");
	gSystem -> Load("Stat.so");

	SEvent* evt = new SEvent(0,9);
	Stat* stat  = new Stat();

	// Adding Points //
	evt -> AddPoint(0);
	evt -> AddPoint(-1);
	evt -> AddPoint(-2);
	evt -> AddPoint(-3);
	evt -> AddPoint(-4);
	evt -> AddPoint(-2);
	evt -> AddPoint(-1);
	evt -> AddPoint(0);
	evt -> AddPoint(-1);
	evt -> AddPoint(-2);
	evt -> PulseFinder(-0.1);

	stat -> AddNumber(-1);
	stat -> AddNumber(-2);
	stat -> AddNumber(-3);
	stat -> AddNumber(-4);
	stat -> AddNumber(-2);
	stat -> AddNumber(-1);


	// Test for function of classes //
	std::cout << " 1. Pulse  Pointer  " << std::endl;
	std::cout << "pointer of the Pulse in TClonesArray : " << evt -> GetPulse(0) << std::endl;
	std::cout << " 2. Mean comparison  " << std::endl;
	std::cout << "mean value of the pulse (Stat)              : " << stat -> GetMean() << std::endl;
	std::cout << "mean value of the pulse (Pulse)             : " << (evt -> GetPulse(0)) -> GetMean() << std::endl;
	std::cout << " 3. rms comparison  " << std::endl;
	std::cout << "rms value of the pulse (Stat)              : " << stat -> GetMean() << std::endl;
	std::cout << "rms value of the pulse (Pulse) " << (evt -> GetPulse(0)) -> GetRMS() << std::endl;
	std::cout << " 4. Skewness comparsison       "   << std::endl;
	std::cout << "skew value of the pulse (Stat) " << stat -> GetSkew() << std::endl;
	std::cout << "skew value of the pulse (Pulse) " << (evt -> GetPulse(0)) -> GetSkew() << std::endl;
	std::cout << " 5. Kurtosis comparison        " << std::endl;
	std::cout << "kurt value of the pulse (Stat) " << stat -> GetKurt() << std::endl;
	std::cout << "kurt value of the pulse (Pulse) " << (evt -> GetPulse(0))-> GetKurt() << std::endl;
	
	

        std::cout << " Test Ended " << std::endl;
}


