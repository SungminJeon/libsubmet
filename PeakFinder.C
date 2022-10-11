#include "PeakFinder.h"
#include <math.h>

PeakFinder::PeakFinder() 
{

	Initialize();
}
/*
PeakFinder::PeakFinder(double sS, double sE, double lS, double lE)
{
	Initialize();
	sigStart = sS;
	sigEnd   = sE;
	ledStart = lS;
	ledEnd   = lE;
}
*/ //FIXME

PeakFinder::~PeakFinder() 
{

}

void PeakFinder::Initialize() 
{
	

        numbers . clear();

        double mean      = 0;
	double rms       = 0;
        double entries   = 0;
        double ledMean   = 0;
        double ledRMS    = 0;
	double ledHeight = 0;
	double ledTiming = -1;
        double pedMean   = 0;
        double pedRMS    = 0;
	double pedHeight = 0;
        double ledArea   = 0;     
        double sigStart  = 1;
        double sigEnd    = 4096;
        double ledStart  = -1;
        double ledEnd    = -1;	
	double pedTiming = 0;

}

std::vector<double> PeakFinder::GetNumbers()
{
	return numbers;
}
// TO DO LIST
// 1: FIND BETTER METHOD TO SHOW PRESENT TIME VARIABLES (method names are too long to call easily) 
// 2: EDIT AddNumber() & AddVector() to update ped, led height immediately. // DONE; 
// 3: OVERLOAD: Constructor (i.e. PeakFinder(double sigStart, double sigEnd, double ledStart, double ledEnd)) for the case where one would like to construct class with desired sig, led times 
// 4: pedTiming?? // ADDED TO PRIVATE MEMBERS; // DONE;
// 5: DCR algorithms.. should I add DCR i& threshold in the private members?.. 
// 6: --


void PeakFinder::AddPoint(double num) 
{

        double allNorm = sigEnd - sigStart + 1;
	double ledNorm = ledEnd - ledStart + 1;  // add to private member variables?
	double pedNorm = allNorm - ledNorm; 
	

	// Initial settings
	numbers . push_back(num);
        rms   = rms * rms;
	rms  += mean * mean;
	rms  *= allNorm;
	mean *= allNorm;

	pedRMS   = pedRMS * pedRMS;
	pedRMS  += pedMean * pedMean;
	pedRMS  *= pedNorm;
	pedMean *= pedNorm;

	ledRMS   = ledRMS * ledRMS;
        ledRMS  += ledMean * ledMean;
	ledRMS  *= ledNorm;
	ledMean *= ledNorm;

	// Add pedestal, led, sig rms and mean
	if ((entries + 1 >= sigStart) && (entries + 1 <= sigEnd))
	{
		rms += num * num;
		mean += num;

	        if ((entries + 1 >= sigStart) && (entries + 1 <= sigEnd) && !((entries + 1 >= ledStart) && (entries + 1 <= ledEnd)))
         	{
	        	pedMean += num;
			pedRMS  += num * num;

			// find pedHeight
			if (entries + 1 == sigStart)
			{
				pedHeight = num;
				pedTiming = entries + 1;
			}
			if (entries + 1 > sigStart)
			{
				if ( num < pedHeight )
				{
					pedHeight = num;
					pedTiming = entries + 1;
				}


			
	        	}
		}
		if ((entries + 1 >= sigStart) && (entries + 1 <= sigEnd) && (entries + 1 >= ledStart) && (entries + 1 <= ledEnd))
		{
			ledMean += num;
			ledRMS  += num * num;

			ledArea += num;

			// Find ledHight
			if (entries + 1 == ledStart)
			{
				ledHeight = num;
				ledTiming = entries + 1;
			}
			if (entries + 1 > ledStart)
			{
				if ( num < ledHeight )
				{
		          		ledHeight = num;
			          	ledTiming = entries + 1;
				}
			}
			
		}
	}

	entries++;
	
	mean /= allNorm;
	rms  /= allNorm;
	rms  -= mean * mean;
	rms   = sqrt(rms);

	pedMean /= pedNorm;
	pedRMS  /= pedNorm; 
	pedRMS  -= pedMean * pedMean;
	pedRMS   = sqrt(pedRMS);

	ledMean /= ledNorm;
	ledRMS  /= ledNorm;
	ledRMS  -= ledMean * ledMean;
	ledRMS   = sqrt(ledRMS);


	ledArea = pedMean * ledNorm - ledArea;
	
	pedHeight = pedMean - pedHeight;
	ledHeight = pedMean - ledHeight;
	
}



void PeakFinder::AddVector(std::vector<double> nums) 
{

	double allNorm = sigEnd - sigStart + 1;
	double ledNorm = ledEnd - ledStart + 1;
	double pedNorm = allNorm - ledNorm;


	int vectorsize = nums . size();
	for (int i = 0; i < vectorsize; i++ )
	{
		// Initial settings
		numbers . push_back(nums[i]);
		
		rms   = rms * rms;
		rms  += mean * mean;
		rms  *= allNorm;
		mean *= allNorm;

		pedRMS   = pedRMS * pedRMS;
		pedRMS  += pedMean * pedMean;
		pedRMS  *= pedNorm;
		pedMean *= pedNorm;

	        ledRMS   = ledRMS * ledRMS;
		ledRMS  += ledMean * ledMean;
		ledRMS  *= ledNorm;
		ledMean *= ledNorm;

		// Add pedestal, led, sig rms and mean
        	if ((entries + 1 >= sigStart) && (entries + 1 <= sigEnd))
         	{
	           	rms += nums[i] * nums[i];
           		mean += nums[i];

               	        if ((entries + 1 >= sigStart) && (entries + 1 <= sigEnd) && !((entries + 1 >= ledStart) && (entries + 1 <= ledEnd)))
                     	{
	                 	pedMean += nums[i];
	           		pedRMS  += nums[i] * nums[i];
       
 		         	// find pedHeight
                 		if (entries + 1 == sigStart)
      		        	{
			         	pedHeight = nums[i];
               				pedTiming = entries + 1;
	         		}
		        	if (entries + 1 > sigStart)
		        	{
               			     	if ( nums[i] < pedHeight )
	          			{
		              			pedHeight = nums[i];
			          		pedTiming = entries + 1;
              				}

 
 			
                 		}
			}
           		if ((entries + 1 >= sigStart) && (entries + 1 <= sigEnd) && (entries + 1 >= ledStart) && (entries + 1 <= ledEnd))
        		{
	           		ledMean += nums[i];
		        	ledRMS  += nums[i] * nums[i];

				ledArea += nums[i];

         			// Find ledHight
	          		if (entries + 1 == ledStart)
		        	{
			        	ledHeight = nums[i];
			         	ledTiming = entries + 1;
               			}
	         		if (entries + 1 > ledStart)
	        		{
		        		if ( nums[i] < ledHeight )
		 	        	{
		          	         	ledHeight = nums[i];
              			          	ledTiming = entries + 1;
	               			}
	           		}
			
			}
      		}

         	entries++;
	
          	mean /= allNorm;
         	rms  /= allNorm;
           	rms  -= mean * mean;
           	rms   = sqrt(rms);

         	pedMean /= pedNorm;
           	pedRMS  /= pedNorm; 
         	pedRMS  -= pedMean * pedMean;
           	pedRMS   = sqrt(pedRMS);

         	ledMean /= ledNorm;
            	ledRMS  /= ledNorm;
          	ledRMS  -= ledMean * ledMean;
          	ledRMS   = sqrt(ledRMS);


		ledArea  = pedMean * ledNorm - ledArea;

		pedHeight = pedMean - pedHeight;
		ledHeight = pedMean - ledHeight;
	}

}

double PeakFinder::GetEntries() 
{
	return entries;
}

double PeakFinder::Getsigtime()
{
	return sigEnd - sigStart + 1;
}

void PeakFinder::Changeledtime(double lS, double lE)
{
	ledStart  = lS;
	ledEnd    = lE;
	ledMean   = 0;
	ledHeight = 0;
	ledRMS    = 0;
	pedMean   = 0;
	pedRMS    = 0;
	pedHeight = 0;
	ledTiming = 0;
	pedTiming = 0;
	mean      = 0;
	rms       = 0;
	ledArea   = 0;

	double allNorm = sigEnd - sigStart + 1;
	double ledNorm = ledEnd - ledStart + 1;
	double pedNorm = allNorm - ledNorm;

	for ( int i = 1; i <= sigEnd; i++)
	{ 
		if ( i >= sigStart )
		{
			mean += numbers[i-1];
			rms  += numbers[i-1] * numbers[i-1];

			if ( i >= ledStart && i <= ledEnd )
			{
				ledMean += numbers[i-1];
				ledRMS  += numbers[i-1] * numbers[i-1];
				
				ledArea += numbers[i-1];
				
				if ( i == ledStart )
				{
					ledHeight = numbers[i-1];
					ledTiming = i;
				}
				if ( i > ledStart )
				{
					if ( numbers[i-1] < ledHeight )
					{
						ledHeight = numbers[i-1];
						ledTiming = i;
					}
				}	
			}
			else 
			{
				pedMean += numbers[i-1];
				pedRMS  += numbers[i-1] * numbers[i-1];

				if ( i == sigStart )
				{
					pedHeight = numbers[i-1];
					pedTiming = i;
				}
				if ( i > sigStart )
				{
					if ( numbers[i-1] < pedHeight )
					{
						pedHeight = numbers[i-1];
						pedTiming = i;
					}
				}
			}
		}

	}

	mean /= allNorm;
	rms  /= allNorm;
	rms  -= mean * mean;
	rms   = sqrt(rms);

	pedMean /= pedNorm;
	pedRMS  /= pedNorm;
	pedRMS  -= pedMean * pedMean;
	pedRMS   = sqrt(pedRMS);

	ledMean /= ledNorm;
	ledRMS  /= ledNorm;
	ledRMS  -= ledMean * ledMean;
	ledRMS   = sqrt(ledRMS);

	ledArea = pedMean * ledNorm - ledArea;

	pedHeight = pedMean - pedHeight;
	ledHeight = pedMean - ledHeight;
		
		
	

}

void PeakFinder::Changesigtime(double sS, double sE)
{
	sigStart = sS;
	sigEnd   = sE;
	ledMean   = 0;
	ledHeight = 0;
	ledRMS    = 0;
	pedMean   = 0;
	pedRMS    = 0;
	pedHeight = 0;
	ledTiming = 0;
	pedTiming = 0;
	mean      = 0;
	rms       = 0;
	ledArea   = 0;

	double allNorm = sigEnd - sigStart + 1;
	double ledNorm = ledEnd - ledStart + 1;
	double pedNorm = allNorm - ledNorm;

	for ( int i = 1; i <= sigEnd; i++)
	{ 
		if ( i >= sigStart )
		{
			mean += numbers[i-1];
			rms  += numbers[i-1] * numbers[i-1];

			if ( i >= ledStart && i <= ledEnd )
			{
				ledMean += numbers[i-1];
				ledRMS  += numbers[i-1] * numbers[i-1];
				
				ledArea += numbers[i-1];
				
				if ( i == ledStart )
				{
					ledHeight = numbers[i-1];
					ledTiming = i;
				}
				if ( i > ledStart )
				{
					if ( numbers[i-1] < ledHeight )
					{
						ledHeight = numbers[i-1];
						ledTiming = i;
					}
				}	
			}
			else 
			{
				pedMean += numbers[i-1];
				pedRMS  += numbers[i-1] * numbers[i-1];

				if ( i == sigStart )
				{
					pedHeight = numbers[i-1];
					pedTiming = i;
				}
				if ( i > sigStart )
				{
					if ( numbers[i-1] < pedHeight )
					{
						pedHeight = numbers[i-1];
						pedTiming = i;
					}
				}
			}
		}

	}

	mean /= allNorm;
	rms  /= allNorm;
	rms  -= mean * mean;
	rms   = sqrt(rms);

	pedMean /= pedNorm;
	pedRMS  /= pedNorm;
	pedRMS  -= pedMean * pedMean;
	pedRMS   = sqrt(pedRMS);

	ledMean /= ledNorm;
	ledRMS  /= ledNorm;
	ledRMS  -= ledMean * ledMean;
	ledRMS   = sqrt(ledRMS);

	ledArea = pedMean * ledNorm - ledArea;

	pedHeight = pedMean - pedHeight;
	ledHeight = pedMean - ledHeight;


}
/*
void PeakFinder::ChangeThreshold(double thold)
{
	threshold = thold;
}
*/
double PeakFinder::Getledtime()
{
	return ledEnd - ledStart + 1;
}

double PeakFinder::GetledStart()
{
	return ledStart;
}

double PeakFinder::GetledEnd()
{
	return ledEnd;
}
double PeakFinder::GetsigStart()
{
	return sigStart;
}
double PeakFinder::GetsigEnd()
{
	return sigEnd;
}
/*
double PeakFinder::GetThreshold()
{
	return threshold;
}
*/

double PeakFinder::GetledHeight()
{
	return ledHeight;
}

double PeakFinder::GetledRMS()
{
	return ledRMS;
}

double PeakFinder::GetledArea()
{
	return ledArea;
}

double PeakFinder::GetpedHeight()
{
	return pedHeight;
}

double PeakFinder::GetpedRMS()
{
	return pedRMS;
}

double PeakFinder::GetDCR(double threshold)
{
	double DCR;


	for ( int i=1; i <= sigEnd; i++)
	{
		// Falling edge count //
		if ( numbers[i-1] >= 











	return DCR;
}

double PeakFinder::GetledTiming()
{
	return ledTiming;
}
