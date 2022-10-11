#include <vector>

class Stat{
  public:
	Stat();
	~Stat();

	void Initialize();

	double GetMean();
	double GetStDev();
	double GetVar();
	double GetRMS();
	double GetN();
	std::vector<double> GetNumbers();
	double GetSkew1();
        double GetSkew();
        double GetSkew3();	
	double GetKurt1();
	double GetKurt();
	double GetKurt3();
	double GetMax();
	double GetMin();

	void AddNumber(double num);

  private:
	std::vector<double> numbers;
	unsigned int N;
	double mean;
	double stdev;
	double var;
	double rms;
	double skew;
	double kurt;
	double skew1;
	double skew2;
	double skew3;
	double kurt1;
	double kurt2;
	double kurt3;
	double max;
	double min;
};
