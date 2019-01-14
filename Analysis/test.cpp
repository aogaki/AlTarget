#include <iostream>

#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TVector3.h>
#include <TCanvas.h>
#include <TGraphPolar.h>


class TAnalyzer
{
public:
   TAnalyzer();
   ~TAnalyzer();

   void FillData();
   void CountElectron();

   Double_t GetNPhotons(){return fNPho;};

   void GetEfficiency();
   
   TH1D *HisEne;
   TGraphPolar *GrPol;

private:
   void GetPolar();
   
   TH1D *HisTheta;

   TChain *fChainElectron;
   TChain *fChainPhoton;

   Int_t fPDG;
   Double_t fEne;
   TVector3 fP;

   TVector3 fInitP;

   Double_t fNPho;
   Double_t fNEle;
   Double_t fWeight;
};


TAnalyzer::TAnalyzer()
{
   HisEne = new TH1D("his", "Energy distribution of #it{#gamma}: Al block T 50. mm", 1500, 0., 1500.);
   HisEne->SetXTitle("[MeV]");
   HisEne->SetYTitle("#Photons / cm^{-2} / Electron");

   HisTheta = new TH1D("HisTheta", "", 3600, 0., 360.);

   GrPol = nullptr;

   fNEle = 1.;
   fNPho = 0.;
   
  
   fChainPhoton = new TChain("AlTarget");
   fChainPhoton->Add("Data*.root");
  
   fChainPhoton->SetBranchStatus("*", kFALSE);

   fChainPhoton->SetBranchStatus("PDGCode", kTRUE);
   fChainPhoton->SetBranchAddress("PDGCode", &fPDG);

   fChainPhoton->SetBranchStatus("KineticEnergy", kTRUE);
   fChainPhoton->SetBranchAddress("KineticEnergy", &fEne);
   
   fChainPhoton->SetBranchStatus("Px", kTRUE);
   fChainPhoton->SetBranchAddress("Px", &fP[0]);
   fChainPhoton->SetBranchStatus("Py", kTRUE);
   fChainPhoton->SetBranchAddress("Py", &fP[1]);
   fChainPhoton->SetBranchStatus("Pz", kTRUE);
   fChainPhoton->SetBranchAddress("Pz", &fP[2]);


   fChainElectron = new TChain("Init");
   fChainElectron->Add("Data*.root");
  
   fChainElectron->SetBranchStatus("*", kFALSE);

   fChainElectron->SetBranchStatus("Px", kTRUE);
   fChainElectron->SetBranchAddress("Px", &fInitP[0]);
   fChainElectron->SetBranchStatus("Py", kTRUE);
   fChainElectron->SetBranchAddress("Py", &fInitP[1]);
   fChainElectron->SetBranchStatus("Pz", kTRUE);
   fChainElectron->SetBranchAddress("Pz", &fInitP[2]);
}

TAnalyzer::~TAnalyzer()
{}

void TAnalyzer::FillData()
{
   fWeight = 1. / 9. / fNEle; // #photon / cm^-2 / #electron
   
   const auto nParticles = fChainPhoton->GetEntries();
   for (auto i = 0; i < nParticles; i++) {
      fChainPhoton->GetEntry(i);
      if (fPDG == 22 && fEne > 0.) {  // PDG code 22 is Gamma.
         fNPho++;
         HisEne->Fill(fEne, fWeight);
         auto theta = fP.Theta() * 180 / TMath::Pi();
         if(fP.Phi() < 0.) theta = 360. - theta;
         HisTheta->Fill(theta);
      }
   }
   
   GetPolar();
}

void TAnalyzer::CountElectron()
{
   Double_t counter = 0.;
   const auto nParticles = fChainElectron->GetEntries();
   for (auto i = 0; i < nParticles; i++) {
      fChainElectron->GetEntry(i);
      if(fInitP[2] > 0.) {
         auto x = fabs(1. * fInitP[0] / fInitP[2]);
         auto y = fabs(1. * fInitP[1] / fInitP[2]);
         if(x < 15. && y < 15.) counter++;
      }
   }

   fNEle = counter;
}

void TAnalyzer::GetPolar()
{
   TGraphErrors *gr = new TGraphErrors(HisTheta);
   const Int_t n = gr->GetN();
   Double_t *y = gr->GetY();
   Double_t err[n];
   Double_t max = HisTheta->GetMaximum();
   for(Int_t i = 0; i < n; i++){
      y[i] /= max;
      err[i] = 0.;
   }
   GrPol = new TGraphPolar(n, gr->GetX(), y, err, err);
   GrPol->SetTitle("");
   GrPol->SetLineColor(kRed);
   GrPol->SetLineWidth(2);

}

void TAnalyzer::GetEfficiency()
{
   std::cout << "Conversion efficiency: "
             << fNPho / fNEle
             << std::endl;
}


TAnalyzer *ana;

void test()
{
   ana = new TAnalyzer();
   ana->CountElectron();
   ana->FillData();

   std::cout << ana->GetNPhotons() << std::endl;
   ana->HisEne->Draw();
   
   auto canvas = new TCanvas("canv", "canv", 900, 900);
   ana->GrPol->Draw();

   ana->GetEfficiency();
}
