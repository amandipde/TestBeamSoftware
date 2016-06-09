#ifndef NtupleMerger_h
#define NtupleMerger_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>

#include <iostream>
#include <utility>
#include <vector>
#include <iomanip>
#include<stdint.h>
#include <map>
#include <string>

#include "DataFormats.h"
#include "TSystem.h"
#include "TChain.h"
#include "TH1I.h"
#include "TH1D.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::cerr;

class NtupleMerger {
  public :
    NtupleMerger(const std::string dutTuple, const std::string telTuple, const std::string dqmTuple, const std::string outTuple);
    virtual ~NtupleMerger();

    bool branchFound(TTree* chain,const string& b,std::vector<std::string>& brList_);
    void setInputBranchAddresses();

    void filltrigTrackmap();
    void eventLoop();
    //void clearEvent();
    void endJob();
  private :
    TFile* dutF_;
    TFile* telF_;
    TFile* dqmF_;
    TTree *dutchain_; 
    TTree *telchain_;
    TTree *dqmchain_;
    TTree* outTree_;
    TFile* fout_;
     
    //input format
    std::vector<int>* cbcErrorVal_;
    std::vector<int>* cbcPLAddressVal_;
    int tdcCounterFromdqm_;  
    tbeam::TelescopeEvent* telEvent_;
    bool periodicityFlag_;
    bool pFlag_;
    bool goodEventFlag_;

    //branches to update
    //TBranch* condBranch_;
    TBranch* telBranch_;
    TBranch* periodicityBranch_;
    TBranch* goodEvBranch_;
    
    //TBranch* eventQualityBranch_; 

    //output format
    
    //
    tbeam::TelescopeEvent* telOutputEvent_;
    tbeam::condEvent* condEvent_;
    tbeam::dutEvent* dutEvent_;
    tbeam::dutEvent* outdutEvent_;
    //TBranch* condBranch_;

    std::map<Int_t,tbeam::TelescopeEvent>* trigTrackmap_;
    long int nTelchainentry_;
    long int nDutchainentry_; 
    long int nDqmchainentry_; 
    long int nEventstoLoop_;
    //validation histograms
    TFile* fval;
    TH1D* tdc1;
    TH1D* tdc2;
    TH1D* tdc3;
    TH1D* tdc4;
    TH1D* tdc5;
    TH1D* tdc6;
    TH1I* pflagfromdqm;
    TH1I* pflagmanual;
    TH1I* pflagmismatch;
    TH1I* isGoodEventF;
    TH1I* cbcErrF;
    TH1I* tdcmismatch;
    TH1D* tdcdiff;
};
#endif