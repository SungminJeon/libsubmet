#include "TSystem.h"

#include "Pulse.h"
#include "Event.h"

void example()
{
	gSystem -> Load("libsubmet.so"); // 이거는 우리가 ROOT, 즉 ROOT 내의 C 인터프리터인 Cling을 쓰고싶을 때 라이브러리 로드로 넣는 것이고
	                                 // gnu 컴파일러로 독립된 프로그램을 만들고 싶으면 동적링크를 해야함


        ///Initial Settings //
	





	FILE* fp; 
	int evt = 0;
	short data[16384];
	int adc; // ADC count
	std::vector<int> vTime;
	std::vector<int> vVolt;

	Event* event;
	TFile* file = new TFile("TestOutput.root", "recreate");
	TTree* tree = new TTree();
	tree -> Branch(TClonesArray, &pPulseContainer);

	
	
//	실험데이터 읽어와서 16384씩 끊어서 읽기... 거기에 있죠? MakeTree.. 그걸 대충 갖다 붙이고

	for ( ... .. )
	{
		event = new Event();
		// 숫자 넣어보고
		TClonesArray* arr = event -> GetPulses() // 얘가 TClonesArray를 리턴해야겠죠?

		tree -> Fill();
		delete event를 하시든 Init을 하시든 어쨌든 비우고.. 새로 4096개 점을 채워야 하니까
	}
	
	tree -> Write();
	file -> Close();
	
//	이거는 CERN ROOT 파일 출력 예시고
//	.txt로 뽑아다가 줘야함

	return;
}
/*
	// Local variables for data acquisition
	int evt = 0;
	FILE* fp;
	short data[16384];
	int adc; // ADC count
	std::vector<int> vTime;
	std::vector<int> vVolt;

	//////////////////////////////////////////////////
	// Read data points
	//////////////////////////////////////////////////
	fp = fopen(input, "rb");
	while( evt < Nevent )
	{
		evt = evt + 1;

		// Read an event
		fread(data, 2, 16384, fp);

		for ( int ch = 0; ch < 4; ch++ )
		{
			// Skip channels masked to 0
			if ( !chMask[ch] ) continue;
			
			// Initialize
			vVolt . clear();
			vVolt . reserve(4096);
			mean = 0;

			// Loop over points
			for ( int i = 0; i < 4096; i++)
			{
				adc = data[4*i + ch] & 0xFFFF;
				vVolt[i] = adc;
				hPe[ch] -> Fill(i, adc);

				if ( i < timeMax ) mean += adc;
			}

			mean /= timeMax;

			// RMS calculation
			rms = 0;
			for ( int i = 0; i < timeMax; i++ )
			{
				rms += (vVolt[i] - mean) * (vVolt[i] - mean) / timeMax;
			}
			rms = TMath::Sqrt(rms);

			hM[ch] -> Fill(mean);


	// Prepare object pointers for outputs
	TH1D* hA[4];
	TH1D* hM[4];
	TH1D* hH[4];
	TH1D* hR[4];
	TH1D* hP[4];
	TH1D* hN[4];
	TH2D* hRA[4];
	TH2D* hHA[4];
	TH2D* hPe[4];
	TTree* tAna[4];
	TString sTemp;
	double area, rms, mean, height, pedestal;
	int npulses;

	// Define objects
	for ( int ch = 0; ch < 4; ch++ )
	{
		// Skip channels masked to 0
		if ( !chMask[ch] ) continue;

		sTemp . Form("area_ch%d", ch);
		hA[ch] = new TH1D(sTemp . Data(), sTemp . Data(), 4096, -.5, TMath::Power(2, 24)); // Area distribution
		sTemp . Form("mean_ch%d", ch);
		hM[ch] = new TH1D(sTemp . Data(), sTemp . Data(), 4096, 3071.5, 4095.5); // Mean distribution
		sTemp . Form("height_ch%d", ch);
		hH[ch] = new TH1D(sTemp . Data(), sTemp . Data(), 4096, -.5, 4095.5); // Height distribution
		sTemp . Form("rms_ch%d", ch);
		hR[ch] = new TH1D(sTemp . Data(), sTemp . Data(), 4096, 0, 100); // RMS distribution
		sTemp . Form("pedestal_ch%d", ch);
		hP[ch] = new TH1D(sTemp . Data(), sTemp . Data(), 4096, -.5, 4095.5); // Pedestal distribution
		sTemp . Form("npulses_ch%d", ch);
		hN[ch] = new TH1D(sTemp . Data(), sTemp . Data(), 11, -.5, 10.5); // # of pulses distribution
		sTemp . Form("rms-area_ch%d", ch);
		hRA[ch] = new TH2D(sTemp . Data(), sTemp . Data(), 4096, -.5, TMath::Power(2, 24) -.5, 4096, 0, 100); // RMS vs Area
		hRA[ch] -> SetOption("colz");
		sTemp . Form("height-area_ch%d", ch);
		hHA[ch] = new TH2D(sTemp . Data(), sTemp . Data(), 4096, -.5, TMath::Power(2, 24) -.5, 4096, -.5, 4095.5); // Height vs Area
		hHA[ch] -> SetOption("colz");
		sTemp . Form("pers_ch%d", ch);
		hPe[ch] = new TH2D(sTemp . Data(), sTemp . Data(), 4096, -.5, 4095.5, 4096, -.5, 4095.5); // Persistence plot
		hPe[ch] -> SetOption("colz");
		sTemp . Form("ana_ch%d", ch);
		tAna[ch] = new TTree(sTemp . Data(), sTemp . Data());
		tAna[ch] -> Branch("area"    , &area    );
		tAna[ch] -> Branch("mean"    , &mean    );
		tAna[ch] -> Branch("rms"     , &rms     );
		tAna[ch] -> Branch("height"  , &height  );
		tAna[ch] -> Branch("pedestal", &pedestal);
		tAna[ch] -> Branch("npulses" , &npulses );
*/
