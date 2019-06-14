//
// Created by user on 6/14/19.
//

#ifndef UMG3_3_COMMANDMESSENGER_HH
#define UMG3_3_COMMANDMESSENGER_HH

#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADouble.hh>
#include "G4UImessenger.hh"
#include "RunAct.hh"
#include "PrimaryGen.hh"





class RunAct;
class PrimaryGen;



class RunActMessenger : public G4UImessenger
{

public:
    RunActMessenger(RunAct *run1);
    ~RunActMessenger();
    void SetNewValue(G4UIcommand*command, G4String newValue);


private:

    RunAct *run1;
    G4UIdirectory *my_dir1;
    G4UIcmdWithAString *newresPath;
};



class PrimaryGenMessenger3 : public G4UImessenger
{
public:
    PrimaryGenMessenger3(PrimaryGen *primarygen);
    ~PrimaryGenMessenger3();
    void SetNewValue(G4UIcommand*command, G4String newValue);

private:
    PrimaryGen *primarygen;
    G4UIdirectory *my_dir3;
    G4UIcmdWithADouble *newpatEn;
};

#endif //UMG3_3_COMMANDMESSENGER_HH
