#ifndef SUBMET_Event
#define SUBMET_Event

#include <vector>
#include "TClonesArray.h"
#include "TObject.h"

#include "SPulse.h"

class SEvent: public TObject
{
  public:
	SEvent();
	SEvent(float roiS, float roiE);
	~SEvent();

	void Initialize(float roiS = 0, float roiE = 4095);

	void AddVolt(float num);
	void AddVolts(std::vector<float> nums);
	void AddTime(float time); //FIXME

	void SetThreshold(double thold);
//	bool SetSelfSup(bool selfSup);

	void CalculateProperties(float ut = 1.0);	// ut = 'unit time interval'
	void CalculatePropertiesI();		// for integral definition of properties

	void PulseFinderN(bool selfsup, double pedestal = 0, double thold = 0, float ut = 1.0, unsigned int ent = 0);		// self subtraction mode: cut = sigma * 10, notice
	void PulseFinderNotice(unsigned int ent = 0);
	void PulseFinderNotice(double pedestal, double thold, unsigned int ent = 0);		// pedestal mode. notice
	void PulseFinderDrs4(float ut, unsigned int ent = 0);		// self subtraction mode: cuut = sigma * 10, drs4
	void PulseFinderDrs4(float ut, double pedestal, double thold, unsigned int ent = 0); 	// pedestal mode, drs4
	void PulseFinderI(bool selfsup, double pedestal = 0, double thold = 0, unsigned int ent = 0);
	void ClearPulseContainer();
	
		

	double GetMean();
	double GetRMS();
	double GetVar();
	double GetKurt();
	double GetSkew();
	double GetEntries();     
	unsigned int GetNumberOfPulses(double threshold);
	unsigned int GetNumberOfPulses();
	double GetThreshold();
	std::vector<float> GetNumbers();
	std::vector<float> GetTimes();


	void ChangeSigWindow(float roiS, float roiE);
	SPulse* GetPulse(int i);
	TClonesArray* GetPulses();
		


		ClassDef(SEvent, 1);
	// TObject inheritance part should be added here.. : public inheritance?
	//
	//
	//
  private: 
	double md_Mean;
	double md_Var;
	double md_Skew;
	double md_Kurt;
	unsigned short int mi_N;
	double md_Threshold;
	bool mb_SelfSup;

	std::vector<float> mv_Volts;  //GetNumbers(); returns it
	std::vector<float> mv_Times;  //GetTimes(); returns it
	unsigned short int mi_NoP; //GetNumberOfPulses(); returns it

	float mf_RoiStart;  // time window
	float mf_RoiEnd;    // time window

	TClonesArray* mv_Ps;
};

#endif
