
#include "StepAct.hh"
#include "G4SystemOfUnits.hh"


StepAct::StepAct(EventAct *eventAct):event(eventAct)
{

}

void StepAct::UserSteppingAction(const G4Step *aStep)

{


    if ((aStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName()=="Source") &&
            (aStep->GetTrack()->GetDynamicParticle()->GetParticleDefinition()->GetParticleName()=="neutron") &&
            (aStep->GetPostStepPoint()->GetStepStatus()==fGeomBoundary)
    )

    {
        event->AddEnDep1(aStep->GetTrack()->GetKineticEnergy());
    };


    if
       (aStep->GetTrack()->GetVolume()->GetLogicalVolume()->GetName() =="He3_gas1")   //this is counter with Cd shielding

    {
        event->AddEnDep2(aStep->GetTotalEnergyDeposit());
    };

//    if
//            (aStep->GetTrack()->GetVolume()->GetLogicalVolume()->GetName() =="He3_gas2")
//
//    {
//        event->AddEnDep3(aStep->GetTotalEnergyDeposit());
//    };


}

