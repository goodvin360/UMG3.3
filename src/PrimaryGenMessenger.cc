
#include "PrimaryGenMessenger.hh"
#include "PrimaryGen.hh"

PrimaryGenMessenger1::PrimaryGenMessenger1(PrimaryGen *primaryGen1) {

    primaryGen = primaryGen1;

    my_dir1 =new G4UIdirectory("/my_dir1/");
    my_dir1 ->SetGuidance("UI command for changing number of particle");

    ParticleCounts = new G4UIcmdWithADouble("/my_dir1/SetParticleCounts", this);
    ParticleCounts->SetGuidance("Change the number of counts");
    ParticleCounts->SetParameterName("counts", false);

}

PrimaryGenMessenger2::PrimaryGenMessenger2(PrimaryGen *primaryGen1) {

    primaryGen = primaryGen1;

    my_dir2 =new G4UIdirectory("/my_dir2/");
    my_dir2 ->SetGuidance("UI command for changing counts step size");

    StepSize = new G4UIcmdWithADouble("/my_dir2/SetCountsStep", this);
    StepSize->SetGuidance("Change size of step");
    StepSize->SetParameterName("stepsize", false);

}

PrimaryGenMessenger1::~PrimaryGenMessenger1() {

}

PrimaryGenMessenger2::~PrimaryGenMessenger2() {

}

void PrimaryGenMessenger1::SetNewValue(G4UIcommand *command, G4String newValue) {
    if(command == ParticleCounts)
    {primaryGen->SetParticleCounts(ParticleCounts->GetNewDoubleValue(newValue));}
    }

void PrimaryGenMessenger2::SetNewValue(G4UIcommand *command, G4String newValue) {
    if(command == StepSize)
    {primaryGen->SetCountsStep(StepSize->GetNewDoubleValue(newValue));}
}
