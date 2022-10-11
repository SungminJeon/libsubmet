#ifndef SUBMET_Event
#define SUBMET_Event


#include <vector>
#include "TClonesArray.h"
#include "Pulse.h"
#include "TObject.h"

//
//
//
class SEvent: public TObject{

	public:
		SEvent();
		SEvent(double sS, double sE);
		SEvent(double sS, double sE, double thold);
		~SEvent();

		void Initialize();
		void Initialize(double sS, double sE);
		void Initialize(double sS, double sE, double thold);

		void AddPoint(double num);
//		void AddVector(std::vector<double> nums);
		void PulseFinder(double threshold);
		void PulseFinder(double pedestal, double thold);

		

		double GetMean();
		double GetRMS();
		double GetVar();
		double GetKurt();
		double GetSkew();
		double GetEntries();     
		unsigned int GetNumberOfPulses(double threshold);
		unsigned int GetNumberOfPulses();
		double GetThreshold();
		std::vector<double> GetNumbers();


		void ChangeSigWindow(double sS, double sE);
		Pulse* GetPulse(int i);
		TClonesArray* GetPulses();


		ClassDef(SEvent, 1)
	// TObject inheritance part should be added here.. : public inheritance?
	//
	//
	//
	private: 

		double mean;       //pedestal mean;
		double rms;        //pedestal rms; 
		double var;
		double skew1;
		double skew2;
		double skew3;
		double kurt1;
		double kurt2;
		double kurt3;
		double N;                        
	        double entries;
		double threshold;

	        	
		std::vector<double> numbers;  //GetPoints(); returns it
		unsigned int nop; //GetNumberOfPulses(); returns it

		double sigStart;  // time window
		double sigEnd;    // time window 

//		TClonesArray PulseContainer("Pulse", 10000); // storing infos of pulses in a single event.
		TClonesArray* PulseContainer;

};

#endif
