#include <vector>



class PeakFinder{
	public:
		PeakFinder();
		~PeakFinder();

		void Initialize();
//		double GetNpeaks(); 
		std::vector<double> GetNumbers();
		void AddPoint(double num);
		void AddVector(std::vector<double> nums);
//		double GetSpeaks();
		double GetEntries();
		void Changeledtime(double lS, double lE); // CHANGING ledStart, ledEND
	        void Changesigtime(double sS, double sE); // CHANGING sigStart, sigEND
		void ChangeThreshold(double thold);
	        double GetThreshold();
                double Getledtime();
		double GetledStart();
		double GetledEnd();
                double GetsigStart();
		double GetsigEnd();
		double Getsigtime();
		double GetDCR(double threshold);
		double GetledHeight();
		double GetledRMS();
		double GetledArea();
		double GetpedHeight();
		double GetpedRMS();
		double GetledTiming();


	private:

		double mean;
		double rms;
		std::vector<double> numbers;
		double entries;
		double ledMean;
		double ledRMS;
		double ledHeight;
		double ledTiming;
		double pedMean;
		double pedRMS;
		double pedTiming;
		double pedHeight;
		double ledArea;
		double sigStart;
		double sigEnd;
		double ledStart;
		double ledEnd;
		double DCR;
//		double threshold;
//		int spulses;
//		int npulses;
};
