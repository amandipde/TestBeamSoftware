#include "NtupleMerger.h"
#include<iomanip>
using std::setw;

NtupleMerger::NtupleMerger(const std::string dutTuple, const std::string telTuple, const std::string runNumber) :
  telFound_(true),
  telOutputEvent_(new tbeam::TelescopeEvent()),//for output
  telEvent_(new tbeam::TelescopeEvent()),//for input
  dutEvent_(new tbeam::Event()),
  outdutEvent_(new tbeam::Event())
{
  
  dutF_ = TFile::Open(dutTuple.c_str());
  if(!dutF_) {
    std::cout << dutTuple << " could not be onened!!" << std::endl;
    exit(1);
  }
  dutchain_ = dynamic_cast<TTree*>(dutF_->Get("treeMaker/tbeamTree"));
  nDutchainentry_ = static_cast<long int>(dutchain_->GetEntries());
  
  telF_ = TFile::Open(telTuple.c_str());
  if(!telF_) {
    std::cout << telTuple << " could not be onened!!" << std::endl;
    telFound_ = false;
    //exit(1);
  } else {
    telchain_ = dynamic_cast<TTree*>(telF_->Get("tracks")); //Tree Name to be chacked
    if(telchain_)  {
      nTelchainentry_ = static_cast<long int>(telchain_->GetEntries());
      telFound_ = telFound_ && nTelchainentry_;
    } else telFound_ = false;
  }  
  
  nEventstoLoop_ = nDutchainentry_;
  std::cout << "DUT Entries=" << nDutchainentry_
            << "\nTelescope Entries=" << nTelchainentry_
            << "\nLooping Over " << nEventstoLoop_ 
            << std::endl;

  setInputBranchAddresses();

  //  if(dutF_) bookValidationHistograms(runNumber); 

  std::string outTuple = "AnalysisTree_" + runNumber + ".root";
  fout_ = TFile::Open(outTuple.c_str(),"recreate");
  outTree_ = new TTree("analysisTree","");
  if(dutF_)  outTree_->Branch("Event", &outdutEvent_);
  //  if(telFound_)  outTree_->Branch("TelescopeEvent",&telOutputEvent_);
}

void NtupleMerger::setInputBranchAddresses() {
  //set the address of the input DUT tree
  if(dutF_) {
    dutchain_->SetBranchStatus("*",1);
    dutchain_->SetBranchAddress("Event", &dutEvent_);
  }
  if(telFound_) {
    /*
    //set the address of the input Telescope tree
    telchain_->SetBranchAddress("nTrackParams", &telEvent_->nTrackParams);
    telchain_->SetBranchAddress("euEvt", &telEvent_->euEvt);
    telchain_->SetBranchAddress("xPos", &telEvent_->xPos);
    telchain_->SetBranchAddress("yPos", &telEvent_->yPos);
    telchain_->SetBranchAddress("dxdz", &telEvent_->dxdz);
    telchain_->SetBranchAddress("dydz", &telEvent_->dydz);
    telchain_->SetBranchAddress("trackNum", &telEvent_->trackNum);
    telchain_->SetBranchAddress("iden", &telEvent_->iden);
    telchain_->SetBranchAddress("chi2", &telEvent_->chi2);
    telchain_->SetBranchAddress("ndof", &telEvent_->ndof);
    */
  }
}

/*

void NtupleMerger::bookValidationHistograms(const std::string run) {
  std::string fname = "validation_" + run +".root";
  //book validation histograms
  fval = TFile::Open(fname.c_str(),"recreate");
  tdc1 = new TH1D("tdc1","TDC phase before filter(edm)",16,-0.5,15.5);
  tdc2 = new TH1D("tdc2","TDC phase after periodicity filter(edm)",16,-0.5,15.5);
  tdc3 = new TH1D("tdc3","TDC phase after good event filter(edm)",16,-0.5,15.5);
  
  tdc4 = new TH1D("tdc4","TDC phase before filter(dqm)",16,-0.5,15.5);
  tdc5 = new TH1D("tdc5","TDC phase after periodicity filter(dqm)",16,-0.5,15.5);
  tdc6 = new TH1D("tdc6","TDC phase after good event filter(dqm)",16,-0.5,15.5);
  
  eventFilter = new TH1I("goodEventCounter","Good flag",5,-0.5,4.5);
  hitmatch = new TH1I("hitmatch","#Hits match raw vs edm",2,-0.5,1.5);
  hitdqm = new TH1D("hitdqm","Total Hits dqm",50,-0.5,49.5);
  hitedm = new TH1D("hitedm","Total Hits edm",50,-0.5,49.5);
}
*/
void NtupleMerger::filltrigTrackmap() {
  if(telFound_) {
    std::cout << "Filling Trigger Track Map" << std::endl;
    for (Long64_t jentry=0; jentry<nTelchainentry_;jentry++) {
      Long64_t ientry = telchain_->GetEntry(jentry);
      if (jentry%1000 == 0)  
        cout << " Events processed. " << std::setw(8) << jentry 
             << "\t loadTree="<< ientry 
             << "\t ntracks=" << telEvent_->nTracks << endl;
      if (ientry < 0) break;
      tbeam::TelescopeEvent telTemp(*telEvent_);
      trigTrackmap_->insert({telEvent_->event,telTemp});
    }
  }
}

void NtupleMerger::eventLoop() {
  filltrigTrackmap();
  for (Long64_t jentry=0; jentry<nDutchainentry_;jentry++) {//nEventstoLoop_
    Long64_t dutentry = dutchain_->GetEntry(jentry);
    if (jentry%1000 == 0)  {
      cout << " Events processed. " << std::setw(8) << jentry 
	   << "\t Load DUT=" << dutentry 
	   << "\t TelescopeFound=" << telFound_ 
           << endl;
    }
    auto& dtemp = *dutEvent_;
    if(telFound_ && trigTrackmap_->find(dtemp.event) == trigTrackmap_->end())      continue;
    
    if(telFound_){
      telOutputEvent_ = &trigTrackmap_->at(dtemp.event);
      for(int itrks=0; itrks<telOutputEvent_->nTracks; itrks++){
	tbeam::Track trkTemp(telOutputEvent_->xPos->at(itrks),telOutputEvent_->xPos->at(itrks),telOutputEvent_->dxdz->at(itrks),telOutputEvent_->dydz->at(itrks),telOutputEvent_->chi2->at(itrks),telOutputEvent_->ndof->at(itrks),telOutputEvent_->xPosError->at(itrks),telOutputEvent_->yPosError->at(itrks));
	dtemp.tracks.push_back(trkTemp);
      }
    }
    outdutEvent_ = &dtemp;
    //Fill output tree
    outTree_->Fill();

  }  
  endJob();
}


void NtupleMerger::endJob() {
  outTree_->AutoSave();
  if(fout_) fout_->Close();
  if(telFound_) telF_->Close();
  if(dutF_) dutF_->Close();
}

NtupleMerger::~NtupleMerger() {
  //if(dutchain_) delete dutchain_;
  //if(telchain_) delete telchain_;
  //if(dqmchain_) delete dqmchain_;
  //if(telEvent_) delete telEvent_;
  //if(condEvent_) delete condEvent_;
}

int main(int argc, char** argv) {
  if(argc !=4)   {
    std::cout << "Wrong Usage!!Use one of the following" << std::endl;
    std::cout << "Usage: ./ntuplemerger <EDMTupleName> <TelescopeTupleName> <RunNumber>" << std::endl;
    exit(1);
  }
  else {
    NtupleMerger m(argv[1],argv[2],argv[3]);
    m.eventLoop();
  } 
  return 0;
}
