//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Nov  1 12:18:35 2015 by ROOT version 5.34/23
// from TTree sensorHitTree/sensorHitTree from RAW files
// found on file: Rawtuple_run444_dqm.root
//////////////////////////////////////////////////////////

#ifndef trawTupleBase_h
#define trawTupleBase_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <iostream>
#include <utility>
#include <vector>
#include <iomanip>
// Header file for the classes stored in the TTree if any.
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::cerr;

// Fixed size dimensions of array or collections stored in the TTree if any.

class trawTupleBase {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           l1Accept;
   Int_t           tdcCounter;
   Int_t           totalHits;
   Int_t           totalStubs;
   vector<int>     *dut0Ch0data;
   vector<int>     *dut0Ch1data;
   vector<int>     *dut1Ch0data;
   vector<int>     *dut1Ch1data;

   // List of branches
   TBranch        *b_l1Accept;   //!
   TBranch        *b_tdcCounter;   //!
   TBranch        *b_totalHits;   //!
   TBranch        *b_totalStubs;   //!
   TBranch        *b_dut0Ch0data;   //!
   TBranch        *b_dut0Ch1data;   //!
   TBranch        *b_dut1Ch0data;   //!
   TBranch        *b_dut1Ch1data;   //!

   //trawTupleBase(TTree *tree=0);
   trawTupleBase(const TString& inFile);
   virtual ~trawTupleBase();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef trawTupleBase_cxx
trawTupleBase::trawTupleBase(const TString& inFile) {
  TFile* f = TFile::Open(inFile);
  if (!f || !f->IsOpen()) {
    cerr << "File not found" << std::endl;
    exit(1);
  }
  fChain = dynamic_cast<TTree*>(f->Get("sensorHitTree"));
  if(!fChain) {
    cerr << "Tree does not exist in file" << std::endl;
    exit(1);
  }
  
  Init(fChain);
}
/*
trawTupleBase::trawTupleBase(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Rawtuple_run444_dqm.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Rawtuple_run444_dqm.root");
      }
      f->GetObject("sensorHitTree",tree);

   }
   Init(tree);
}
*/
trawTupleBase::~trawTupleBase()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t trawTupleBase::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t trawTupleBase::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void trawTupleBase::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   dut0Ch0data = 0;
   dut0Ch1data = 0;
   dut1Ch0data = 0;
   dut1Ch1data = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("l1Accept", &l1Accept, &b_l1Accept);
   fChain->SetBranchAddress("tdcCounter", &tdcCounter, &b_tdcCounter);
   fChain->SetBranchAddress("totalHits", &totalHits, &b_totalHits);
   fChain->SetBranchAddress("totalStubs", &totalStubs, &b_totalStubs);
   fChain->SetBranchAddress("dut0Ch0data", &dut0Ch0data, &b_dut0Ch0data);
   fChain->SetBranchAddress("dut0Ch1data", &dut0Ch1data, &b_dut0Ch1data);
   fChain->SetBranchAddress("dut1Ch0data", &dut1Ch0data, &b_dut1Ch0data);
   fChain->SetBranchAddress("dut1Ch1data", &dut1Ch1data, &b_dut1Ch1data);

   Notify();
}

Bool_t trawTupleBase::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void trawTupleBase::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t trawTupleBase::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef trawTupleBase_cxx
