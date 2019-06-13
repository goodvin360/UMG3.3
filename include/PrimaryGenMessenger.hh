#ifndef DIAMOND_PRIMARYGENMESSENGER_HH
#define DIAMOND_PRIMARYGENMESSENGER_HH

#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADouble.hh>

#
#include "PrimaryGen.hh"
#include "G4UImessenger.hh"

class PrimaryGen;

class PrimaryGenMessenger1 : public G4UImessenger
{
public:
    PrimaryGenMessenger1(PrimaryGen * primaryGen);
    ~PrimaryGenMessenger1();
    void SetNewValue(G4UIcommand*command, G4String newValue);

private:
    PrimaryGen *primaryGen;
    G4UIdirectory *my_dir1;
    G4UIcmdWithADouble *ParticleCounts;
};

class PrimaryGenMessenger2 : public G4UImessenger
{
public:
    PrimaryGenMessenger2(PrimaryGen * primaryGen);
    ~PrimaryGenMessenger2();
    void SetNewValue(G4UIcommand*command, G4String newValue);

private:
    PrimaryGen *primaryGen;
    G4UIdirectory *my_dir2;
    G4UIcmdWithADouble *StepSize;
};





#endif //DIAMOND_PRIMARYGENMESSENGER_HH
