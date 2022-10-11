#include "SPulse.h"
#include "SEvent.h"
#include "Stat.h"


void test4()
{

	gSystem -> Load("libsubmet.so");
	gSystem -> Load("Stat.so");

	SEvent* evt = new SEvent(0, 1024);
	SEvent* evt2 = new SEvent(0, 1024);
	SEvent* evt3 = new SEvent(0, 1.024e-6);
	Stat* stat  = new Stat();
	SPulse* pulse = new SPulse();
	SPulse* pulse2 = new SPulse();

	// Generating events
	for ( unsigned int i = 0; i < 1024; i++)
	{
		evt  -> AddTime(1 * i);
		evt2 -> AddTime(1 * i);
		evt3 -> AddTime(1.0e-9 * i); 

		if ( (i >= 0 && i < 64) || ( i < 1024 && i >= 960 ) )
		{
			evt  -> AddVolt(-1.5);
			evt2 -> AddVolt(-1.5);
			evt3 -> AddVolt(-1.5);
		}
		else if ( (i >= 64 && i < 128 ) || ( i < 960 && i >= 896) )
		{
			evt  -> AddVolt(-2.5);
			evt2 -> AddVolt(-2.5);
			evt3 -> AddVolt(-2.5);
		}
		else if ( (i >= 128 && i < 256 ) || ( i < 896 && i >= 768) )
		{
			evt  -> AddVolt(-3.5);
			evt2 -> AddVolt(-3.5);
			evt3 -> AddVolt(-3.5);
		}
		else if ( (i >= 256 && i < 512 ) || ( i < 768 && i >= 512) )
		{
			evt  -> AddVolt(-4.5);
			evt2 -> AddVolt(-4.5);
			evt3 -> AddVolt(-4.5);
		}


	}

	evt  -> PulseFinderNotice(0, -0.1, 0);
	evt2 -> PulseFinderN(0, 0, -0.1, 1, 0); 
	evt3 -> PulseFinderI(0, 0, -0.1, 0);
	
	evt -> CalculateProperties(1);
	evt3 -> CalculatePropertiesI();


	// Test for function of classes //

	std::cout << "TEST FOR NEW METHODS: CalculatePropertiesI() " << std::endl;
	std::cout << "since CalculateProperties(ut) method works well, Set values from this method as standard" << std::endl;
	std::cout << " "<< std::endl;
	std::cout << " Mean value " << std::endl;
	std::cout << " CalculateProperties(ut): " << evt -> GetMean()  << std::endl;
	std::cout << " CalculatePropertiesI() : " << evt3 -> GetMean() << std::endl;
	std::cout << " "<< std::endl;
	std::cout << " RMS value " << std::endl;
	std::cout << " CalculateProperties(ut): " << evt -> GetRMS()  << std::endl;
	std::cout << " CalculatePropertiesI() : " << evt3 -> GetRMS() << std::endl;
	std::cout << " " << std::endl;
	std::cout << " Skew value " << std::endl;
	std::cout << " CalculateProperties(ut): " << evt -> GetSkew()  << std::endl;
	std::cout << " CalculatePropertiesI() : " << evt3 -> GetSkew() << std::endl;
	std::cout << " " << std::endl;
	std::cout << " Kurt value "<< std::endl;
	std::cout << " CalculateProperties(ut): " << evt -> GetKurt()  << std::endl;
	std::cout << " CalculatePropertiesI() : " << evt3 -> GetKurt() << std::endl;
	std::cout << " "<< std::endl;








	// Test for function of classes //
	std::cout << " Test for  PulseFinderN() & PulseFinderI() methods  " << std::endl;
	std::cout << " 1. pointerof the pulse                             " << std::endl;
	std::cout << "pointer of the Pulse in TClonesArray (PulseFinderDrs)     : " << evt -> GetPulse(0) << std::endl;
	std::cout << "pointer of the Pulse in TClonesArray (PulseFinderN)       : " << evt2 -> GetPulse(0) << std::endl;
	std::cout << "pointer of the Pulse in TClonesArray (PulseFinderI)       : " << evt3 -> GetPulse(0) << std::endl;
	std::cout << " 2. Mean comparison  " << std::endl;
	std::cout << "mean value of the pulse (PulseFinderDrs)                  : " << (evt -> GetPulse(0)) -> GetMean() << std::endl;
	std::cout << "mean value of the pulse (PulseFinderN)                    : " << (evt2-> GetPulse(0)) -> GetMean() << std::endl;
	std::cout << "mean value of the pulse (PulseFinderI)                    : " << (evt3 -> GetPulse(0)) -> GetMean() << std::endl;
	std::cout << " 3. RMS comparison  " << std::endl;
	std::cout << "RMS value of the pulse (PulseFinderDrs)                   : " << (evt -> GetPulse(0)) -> GetRMS() << std::endl;
	std::cout << "RMS value of the pulse (PulseFinderN)                     : " << (evt2-> GetPulse(0)) -> GetRMS() << std::endl;
	std::cout << "RMS value of the pulse (PulseFinderI)                     : " << (evt3 -> GetPulse(0)) -> GetRMS() << std::endl;
	std::cout << " 2. Skew comparison  " << std::endl;
	std::cout << "mean value of the pulse (PulseFinderDrs)                  : " << (evt -> GetPulse(0)) -> GetSkew() << std::endl;
	std::cout << "mean value of the pulse (PulseFinderN)                    : " << (evt2-> GetPulse(0)) -> GetSkew() << std::endl;
	std::cout << "mean value of the pulse (PulseFinderI)                    : " << (evt3 -> GetPulse(0)) -> GetSkew() << std::endl;
	std::cout << " 2. Kurt comparison  " << std::endl;
	std::cout << "mean value of the pulse (PulseFinderDrs)                  : " << (evt -> GetPulse(0)) -> GetKurt() << std::endl;
	std::cout << "mean value of the pulse (PulseFinderN)                    : " << (evt2-> GetPulse(0)) -> GetKurt() << std::endl;
	std::cout << "mean value of the pulse (PulseFinderI)                    : " << (evt3 -> GetPulse(0)) -> GetKurt() << std::endl;





	




	// EXTRA CHECK
	std::cout << " Extra test on PulseFinder " << std::endl;
	std::cout << " number of pulse " << std::endl;
	std::cout << " PulseFinderDrs4() : " << evt -> GetNumberOfPulses() << std::endl;
	std::cout << " PulseFinderN()    : " << evt2 -> GetNumberOfPulses() << std::endl;
	std::cout << " PulseFinderI()    : " << evt3 -> GetNumberOfPulses() << std::endl;
	std::cout << " is a pulse found? : " << ((evt -> GetPulse(0))-> GetVolts())[256] << std::endl;
	std::cout << " is a pulse found? : " << ((evt2 -> GetPulse(0))-> GetVolts())[256] << std::endl;
	std::cout << " entries of a pulse : " << (evt -> GetPulse(0)) -> GetN() << std::endl;

	std::cout << "        TEST END           " << std::endl;

/*

	// Adding Points //
	evt -> AddVolt(0);
	evt -> AddVolt(-1);
	evt -> AddVolt(-2);
	evt -> AddVolt(-3);
	evt -> AddVolt(-4);
	evt -> AddVolt(-2);
	evt -> AddVolt(-1);
	evt -> AddVolt(0);
	evt -> AddVolt(-1);
	evt -> AddVolt(-2);
	evt -> PulseFinderNotice(0,-0.1);

	evt2 -> AddVolt(0);
	evt2 -> AddVolt(-1);
	evt2 -> AddVolt(-2);
	evt2 -> AddVolt(-3);
	evt2 -> AddVolt(-4);
	evt2 -> AddVolt(-2);
	evt2 -> AddVolt(-1);
	evt2 -> AddVolt(0);
	evt2 -> AddVolt(-1);
	evt2 -> AddVolt(-2);
	evt2 -> PulseFinderDrs4(1.0, 0, -0.1);


	stat -> AddNumber(-1);
	stat -> AddNumber(-2);
	stat -> AddNumber(-3);
	stat -> AddNumber(-4);
	stat -> AddNumber(-2);
	stat -> AddNumber(-1);

	
	pulse -> AddVolt(-1);
	pulse -> AddVolt(-2);
	pulse -> AddVolt(-3);
	pulse -> AddVolt(-4);
	pulse -> AddVolt(-2);
	pulse -> AddVolt(-1);
	pulse -> AddTime(1);
	pulse -> AddTime(1);
	pulse -> AddTime(1);
	pulse -> AddTime(1);
	pulse -> AddTime(1);
	pulse -> AddTime(1);



	pulse -> CalculateProperties();
		
	// Test for function of classes //
	std::cout << " 1. Pulse  Pointer  " << std::endl;
	std::cout << "pointer of the Pulse in TClonesArray        : " << evt -> GetPulse(0) << std::endl;
	std::cout << " 2. Mean comparison  " << std::endl;
	std::cout << "mean value of the pulse (Stat)              : " << stat -> GetMean() << std::endl;
	std::cout << "mean value of the pulse (Pulse)             : " << (evt -> GetPulse(0)) -> GetMean() << std::endl;
	std::cout << "mean value of the pulse (Pulse)             : " << pulse -> GetMean() << std::endl;
	std::cout << "mean value of the drs pulse (Pulse)         : " << (evt2 -> GetPulse(0)) -> GetMean() << std::endl;

	std::cout << " 3. rms comparison  " << std::endl;
	std::cout << "rms value of the pulse (Stat)               : " << stat -> GetRMS() << std::endl;
	std::cout << "rms value of the pulse (Pulse)              : " << (evt -> GetPulse(0)) -> GetRMS() << std::endl;
	std::cout << "rms value of the pulse (Pulse)              : " << pulse -> GetRMS() << std::endl;
	std::cout << "rms value of the drs pulse (Pulse)          : " << (evt2 -> GetPulse(0)) -> GetRMS() << std::endl;


	std::cout << " 4. Skewness comparsison       "   << std::endl;
	std::cout << "skew value of the pulse (Stat)              : " << stat -> GetSkew() << std::endl;
	std::cout << "skew value of the pulse (Pulse)             : " << (evt -> GetPulse(0)) -> GetSkew() << std::endl; 
	std::cout << "skew value of the pulse (Pulse)             : " << pulse -> GetSkew() << std::endl;
	std::cout << "skew value of the drs pulse (Pulse)         : " << (evt2 -> GetPulse(0)) -> GetSkew() << std::endl;


	std::cout << " 5. Kurtosis comparison        " << std::endl;
	std::cout << "kurt value of the pulse (Stat)              : " << stat -> GetKurt() << std::endl;
	std::cout << "kurt value of the pulse (Pulse)             : " << (evt -> GetPulse(0))-> GetKurt() << std::endl;
	std::cout << "kurt value of the pulse (Pulse)             : " << pulse -> GetKurt() << std::endl;
	std::cout << "kurt value of the drs pulse (Pulse)         : " << (evt2 -> GetPulse(0)) -> GetKurt() << std::endl;


	std::cout << "        TEST  ENDED            " << std::endl;

*/

}
