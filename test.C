#include "Stat.h" 
#include "PeakFinder.h"
void test()
{
	gSystem -> Load("Stat.so");

	Stat* test = new Stat();
	PeakFinder* test2 = new PeakFinder();

	TTree* sample = new TTree();
	sample -> ReadFile("sample.csv", "num/D");
	double num;
	sample -> SetBranchAddress("num", &num);

	
	for ( int i = 0; i < sample -> GetEntries(); i++ )
	{
		sample -> GetEntry(i);
		test -> AddNumber(num);
		
	}

//	test -> AddNumber(1);
//	test -> AddNumber(2);
//	test -> AddNumber(3);
//	test -> AddNumber(4);
//	test -> AddNumber(4);
//	test -> AddNumber(4);
//	test -> AddNumber(5);
//	test -> AddNumber(6);
//	test -> AddNumber(7);
//	cout << "skewness should be 0" << endl;       // SKEWNESS CHECKED    KURTOSIS CHECKED
//	
/*
	cout << "Mean : " << test -> GetMean() << endl;
        cout << "RMS :  " << test -> GetRMS() << endl;
	cout << "N : " << test ->GetN() << endl;
	cout << "stdev : " << test -> GetStDev() << endl;
*/	
	

//      test -> AddNumber(2);

	

/*	cout << test -> GetMean() << endl;
        cout << "RMS : sqrt(0.25) = "  << test -> GetRMS() << endl;
	cout << test -> GetN() << endl;
	cout << "stdev : " << test -> GetStDev() << endl;
*/

//	test -> AddNumber(3);


/*	cout << test -> GetMean() << endl;
	cout << "RMS : sqrt(2/3) = " << test -> GetRMS() << endl;
	cout << test -> GetN() << endl;
	cout << "stdev : " << test -> GetStDev() << endl;
*/


//	test -> AddNumber(4);

/*	cout << test -> GetMean() << endl;
	cout << "RMS : sqrt(1.25) = " << test -> GetRMS() << endl;
	cout << test -> GetN() << endl;
	cout << "stdev : " << test -> GetStDev() << endl;


        cout << "lines below this line are for testing sqrt function in C library" << endl;

        
	cout << "sqrt 2 = " << sqrt(2) << endl;
	cout << "sqrt 0.25 =" << sqrt(0.25) << endl;
	cout << "sqrt 2/3 = " << sqrt(0.6666667) << endl;
	cout << "sqrt 1.25 = " << sqrt(1.25) << endl;
*/


//	test -> AddNumber(5);
	

        cout << "mean  : " << test -> GetMean() << endl;
	cout << "rms   : " << test -> GetRMS() << endl;
	cout << "stdev : " << test -> GetStDev() << endl;
	cout << "N     : " << test -> GetN() << endl;
	cout << "var   : " << test -> GetVar() << endl;
        cout << "skew1 : " << test -> GetSkew1() << endl;
	cout << "skew2 : " << test -> GetSkew() << endl;
	cout << "skew3 : " << test -> GetSkew3() << endl;
	cout << "kurt1 : " << test -> GetKurt1() << endl;
	cout << "kurt2 : " << test -> GetKurt() << endl;
	cout << "kurt3 : " << test -> GetKurt3() << endl;
	cout << "max   : " << test -> GetMax() << endl;
	cout << "min   : " << test -> GetMin() << endl;
//	cout << "nums  : " << test -> GetNumbers() << endl;
        

	test -> Initialize();

        cout << "mean  : " << test -> GetMean() << endl;
	cout << "rms   : " << test -> GetRMS() << endl;
	cout << "stdev : " << test -> GetStDev() << endl;
	cout << "N     : " << test -> GetN() << endl;
	cout << "var   : " << test -> GetVar() << endl;
        cout << "skew1 : " << test -> GetSkew1() << endl;
	cout << "skew2 : " << test -> GetSkew() << endl;
	cout << "skew3 : " << test -> GetSkew3() << endl;
	cout << "kurt1 : " << test -> GetKurt1() << endl;
	cout << "kurt2 : " << test -> GetKurt() << endl;
	cout << "kurt3 : " << test -> GetKurt3() << endl;
	cout << "max   : " << test -> GetMax() << endl;
	cout << "min   : " << test -> GetMin() << endl;

        cout << "==========================TEST ENDED===============================" << endl;
}
