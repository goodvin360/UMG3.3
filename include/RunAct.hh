

#ifndef CPROJECT_RUNACT_HH
#define CPROJECT_RUNACT_HH

#include <G4UserRunAction.hh>
#include <G4SystemOfUnits.hh>
#include "Run.hh"
#include "EventAct.hh"
#include <map>
#include "CommandMessenger.hh"

using namespace std;

class G4Run;
class RunActMessenger;



class RunAct : public G4UserRunAction {
public:

    RunAct();
    ~RunAct();
    void BeginOfRunAction(const G4Run *aRun);
    void EndOfRunAction(const G4Run *aRun);

    void AddEvent1(G4double energy1);

    void AddEvent2(G4double energy2);

    void AddEvent3(G4double energy3);

    int nStep = 5000;
    G4double Emax = 20.0*MeV;
//    double a = 0.00001;
//    double b = 0.000002;
    double w = 13.1;
    double F = 12;

    void SetNewResPath(G4String newPath);

    G4String foldername = "/mnt/hgfs/VMplayer/UMG3.3/Res_1.txt";


private:

    std::map <G4double, G4int> *result1;

    std::map <G4double, G4int> *result2;

    std::map <G4double, G4int> *result3;

    RunActMessenger*runactMessenger;

};

#endif //CPROJECT_RUNACT_HH
