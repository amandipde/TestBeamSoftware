#ifndef __TelescopeEvent__h
#define __TelescopeEvent__h
#include<stdint.h>
#include<iostream>
#include<iomanip>
#include<vector>
using std::vector;
/*
typedef struct{
    Double_t dxdz;//x-Gradient along beam direction 
    Double_t dydz;//y-Gradient along beam direction
    Double_t xPos;//Track impact x-position at the reference plane
    Double_t yPos;//Track impact y-position at the reference plane
    Double_t chi2ndf;//Chi-square from track fitting
    //Double_t ndof;//#degrees of freedom
    //optional requirement
    Double_t xPosErr;//Track impact x-position error
    Double_t yPosErr;//Track impact y-position error
    Double_t xPosPrevHit;
    Double_t yPosPrevHit;
    Double_t xPosErrPrevHit;
    Double_t yPosErrPrevHit;
    Double_t xPosNextHit;
    Double_t yPosNextHit;
    Double_t xPosErrNextHit;
    Double_t yPosErrNextHit;
    int trigger;// trigger/event number used for sync. with event from DUT
    int runNumber;
    long int timestamp;
} TelescopeEvent;
*/
class TelescopeEvent: public TObject {
public:
    Double_t  dxdz;//x-Gradient along beam direction 
    Double_t  dydz;//y-Gradient along beam direction
    Double_t  xPos;//Track impact x-position at the reference plane
    Double_t yPos;//Track impact y-position at the reference plane
    Double_t  chi2ndf;//Chi-square from track fitting
    //Double_t ndof;//#degrees of freedom
    //optional requirement
    Double_t xPosErr;//Track impact x-position error
    Double_t yPosErr;//Track impact y-position error
    Double_t xPosPrevHit;
    Double_t yPosPrevHit;
    Double_t xPosErrPrevHit;
    Double_t yPosErrPrevHit;
    Double_t xPosNextHit;
    Double_t yPosNextHit;
    Double_t xPosErrNextHit;
    Double_t yPosErrNextHit;
    Double_t xPosPrevHitGlobal;
    Double_t yPosPrevHitGlobal;
    Double_t zPosPrevHitGlobal;
    Double_t xPosErrPrevHitGlobal;
    Double_t yPosErrPrevHitGlobal;
    Double_t zPosErrPrevHitGlobal;
    Double_t xPosNextHitGlobal;
    Double_t yPosNextHitGlobal;
    Double_t zPosNextHitGlobal;
    Double_t xPosErrNextHitGlobal;
    Double_t yPosErrNextHitGlobal;
    Double_t zPosErrNextHitGlobal;



    int trigger;// trigger/event number used for sync. with event from DUT
    int runNumber;
    long int timestamp; 
ClassDef(TelescopeEvent,1)
};
#endif
