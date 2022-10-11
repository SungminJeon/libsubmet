#ifndef SUBMET_Pulse
#define SUBMET_Pulse

#include <vector>
#include "TObject.h"


class SPulse: public TObject
{
  public:
	SPulse();
	~SPulse();

	void Initialize();

	void AddVolt(float volt);	//FIXME
	void AddTime(float time);	//FIXME

	void SetVolts(std::vector<float> volts);	//FIXME
	void SetTimes(std::vector<float> times);	//FIXME
	void SetThreshold(double thold);
	void SetPedMean(double pM);

	void CalculateProperties();
	void CalculateProperties(float ut);
	void CalculatePropertiesI();

	// Return statistical variables
	double GetMean();
	double GetRMS();
	double GetVar();
	double GetSkew();
	double GetKurt();

	// Geometric variables
	double GetHeight();
	double GetArea(bool mode = 1);

	std::vector<float> GetVolts();     // FIXME
	std::vector<float> GetTimes();     // FIXME
	
	unsigned short int GetN();
	float  GetPeakTime(); // Time at the maximum point	//FIXME 
	double GetMeanTime();             // Averaged time weighted by volts

  private:
	double md_Mean;
	double md_Var;
	double md_Skew;
	double md_Kurt;
	double md_Threshold;
	double md_PedMean;
	double md_Height;
	unsigned short int mi_N;
	float  mf_PeakTime;              // FIXME
	double md_MeanTime;              
	std::vector<float> mv_Volts;     // FIXME
	std::vector<float> mv_Times;     // FIXME 

	ClassDef(SPulse, 1);
};

#endif
