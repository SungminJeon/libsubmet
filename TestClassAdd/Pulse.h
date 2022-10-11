#ifndef SUBMET_Pulse
#define SUBMET_Pulse


#include <vector>
#include "TObject.h"

class Pulse: public TObject{
	
	public:

		Pulse();
		~Pulse();

		void Initialize();
		void AddPoint(double num);
		void AddTimeCoordinate(double tC);
		void AddTimeCoordinate(int tC);
//		void AddVector(double nums);
                void SetThreshold(double thold);
		void SetPedMean(double pM);
		void CalculateProperties();


		 double	GetMean();
		 double GetRMS();
		 double GetVar();
		 double GetKurt();
		 double GetSkew();
		 double GetHeight();
		 double GetArea();
		 std::vector<double> GetPoints();
		 std::vector<double> GetTimeCoordinate();
		 double GetN();
		 double GetPeakTiming();
		 

		 ClassDef(Pulse,1) 







	private:

		double mean;
		double rms;
		double var;
		double kurt1;
		double skew1;
		double threshold;
		double pedMean;
		double Height;
		double Area;
		double N;
		double PeakTiming;
		std::vector<double> numbers;
		std::vector<double> time;





};

#endif
