TH1D *his;

void test()
{
  his = new TH1D("his", "Energy distribution of #it{e^{-}}: Al plate T 70 mm", 150, 0., 150.);
  his->SetXTitle("[MeV]");

  auto file = new TFile("../resultT70.root", "READ");
  auto tree = (TTree *)file->Get("AlTarget");
  tree->SetBranchStatus("*", kFALSE);

  Int_t pdg;
  tree->SetBranchStatus("PDGCode", kTRUE);
  tree->SetBranchAddress("PDGCode", &pdg);

  Double_t ene;
  tree->SetBranchStatus("KineticEnergy", kTRUE);
  tree->SetBranchAddress("KineticEnergy", &ene);

  Double_t Pz;
  tree->SetBranchStatus("Pz", kTRUE);
  tree->SetBranchAddress("Pz", &Pz);

  const auto nParticles = tree->GetEntries();
  for (auto i = 0; i < nParticles; i++) {
    tree->GetEntry(i);
    if (pdg == 11 && ene > 0. && Pz > 0.) {  // PDG code 22 is Gamma.
      his->Fill(ene);
    }
  }

  his->Draw();
}
