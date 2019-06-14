//
// Created by user on 6/14/19.
//

#include "CommandMessenger.hh"
#include "RunAct.hh"
#include "PrimaryGen.hh"

RunActMessenger::RunActMessenger(RunAct *run2) {
    run1 = run2;

    my_dir1 = new G4UIdirectory("/my_dir1/");
    my_dir1 ->SetGuidance("UI command for changing result file path");

    newresPath = new G4UIcmdWithAString("/my_dir1/SetNewResPath", this);
    newresPath->SetGuidance("Write new path");
    newresPath->SetParameterName("path", false);
}



PrimaryGenMessenger3::PrimaryGenMessenger3(PrimaryGen *primarygen3) {

    primarygen = primarygen3;

    my_dir3 = new G4UIdirectory("/my_dir3/");
    my_dir3->SetGuidance("UI command for changing particle energy");

    newpatEn = new G4UIcmdWithADouble("/my_dir3/SetNewPatEn", this);
    newpatEn->SetGuidance("Write new pat energy");
    newpatEn->SetParameterName("energy", false);

}



RunActMessenger::~RunActMessenger() {

}


PrimaryGenMessenger3::~PrimaryGenMessenger3() {

}



void RunActMessenger::SetNewValue(G4UIcommand *command, G4String newValue) {
    if(command == newresPath)
    {
        run1 ->SetNewResPath(newValue);
    }
}


void PrimaryGenMessenger3::SetNewValue(G4UIcommand *command, G4String newValue) {
    if(command == newpatEn)
    {
        primarygen ->SetNewPatEn(newpatEn->GetNewDoubleValue(newValue));
    }
}

