=======
## Beam Test Data Analysis 
##Merging Code: Takes DUT Ntuple with flat Tree structure and Telescope Ntuple with Event Class structure and merges into one Analysis Tree for user
The code fill the Track vector inside the  ntuple
## Installation

Set up ROOT(works with ROOT 6)

After checking out the code:-
make cint

make 

## Usage
##
./ntuplemerger \<EDMTupleName\> \<TelescopeTupleName\> \<RunNumber\>

It produces 1 file AnalysisTree_RunNumber.root
