#include "Stat.h"
#include "PeakFinder.h"

void test2()
{

	gSystem -> Load("Stat.so");

	PeakFinder* test = new PeakFinder();



	test -> AddPoint(1);
	test -> AddPoint(-1);
	test -> AddPoint(3);
	test -> AddPoint(-1);
	test -> AddPoint(5);
	test -> AddPoint(-3);
	test -> AddPoint(1);
	test -> AddPoint(-1);
	test -> ChangeSigtime
/*
        for (double i = 1; i <= 100; i++) 
	{
		test -> AddNumber(i);
	}
*/
//      cout << "test for skewness & kurtosis in Stat library" << endl;
//	cout << "skew 1 : " << test -> GetSkew1() << endl;
//	cout << "skew 2 : " << test -> GetSkew2() << endl;
//	cout << "skew 3 : " << test -> GetSkew3() << endl;
//	cout << "kurt 1 : " << test -> GetKurt1() << endl;
//	cout << "kurt 2 : " << test -> GetKurt2() << endl;
//	cout << "kurt 3 : " << test -> GetKurt3() << endl;
//	cout << "max    : " << test -> GetMax() << endl;
//	cout << "min    : " << test -> GetMin() << endl;
	cout << "pulses : " << test -> GetNpeaks(0.0) << endl; 
        cout << "============================= TEST ENDED =================================" << endl;

}
