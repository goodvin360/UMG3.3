

#ifndef CPROJECT_EVENTACT_HH
#define CPROJECT_EVENTACT_HH

#include "G4UserEventAction.hh"
#include "G4RunManager.hh"
#include "RunAct.hh"
#include "Run.hh"

class RunAct;

class EventAct : public G4UserEventAction
{
public:
    EventAct(RunAct* runAct);
   // ~EventAct();
   // virtual void BeginOfEventAction(const G4Event* event);
   // virtual void EndOfEventAction(const G4Event* event);
      void BeginOfEventAction(const G4Event* anEvent);
      void EndOfEventAction(const G4Event* anEvent);
      void AddEnDep1 (G4double en1);
      void AddEnDep2 (G4double en2);
      void AddEnDep3 (G4double en3);



private:
      RunAct *run;
      G4double EnergyDep1;
      G4double EnergyDep2;
      G4double EnergyDep3;

};

#endif //CPROJECT_EVENTACT_HH
