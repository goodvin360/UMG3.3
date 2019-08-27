
#include "RunAct.hh"
#include "EventAct.hh"
#include "StepAct.hh"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <map>
#include "CommandMessenger.hh"

using namespace std;

RunAct::RunAct()
{
    result1 = new std::map<G4double, G4int>;

    result2 = new std::map<G4double, G4int>;

    result3 = new std::map<G4double, G4int>;

    runactMessenger = new RunActMessenger(this);

}

RunAct::~RunAct()
{
    delete result1;

    delete result2;

    delete result3;

    delete runactMessenger;



}

void RunAct::BeginOfRunAction(const G4Run *aRun)
{


    result1->clear();
    for (int i=0; i <nStep; i++)
        result1->insert(std::pair<G4double, G4int> (i *Emax / nStep, 0));

    result2->clear();
    for (int i=0; i <nStep; i++)
        result2->insert(std::pair<G4double, G4int> (i *Emax / nStep, 0));

    result3->clear();
    for (int i=0; i <nStep; i++)
        result3->insert(std::pair<G4double, G4int> (i *Emax / nStep, 0));

}


void RunAct::EndOfRunAction(const G4Run *aRun)
{
    fstream fout1("/mnt/hgfs/VMplayer/UMG3.3/Source.txt", ios::out);
    for (auto it1: *result1)
        fout1 << it1.first << " " << it1.second << '\n';
    fout1.close();

    fstream fout2("/mnt/hgfs/VMplayer/UMG3.3/Detector_No_1.txt", ios::out);
    for (auto it2: *result2)
        fout2 << it2.first << " " << it2.second << '\n';
    fout2.close();

//    fstream fout3("/mnt/hgfs/VMplayer/UMG3.3/Detector_No_2.txt", ios::out);
//    for (auto it3: *result3)
//        fout3 << it3.first << " " << it3.second << '\n';
//    fout3.close();

    auto P1 = new double *[nStep];
    for (int i = 0; i < nStep; i++) {
        P1[i] = new double[nStep];
    }

    auto Sigma = new double[nStep];
    auto Energy = new double[nStep];
    auto Counts = new double[nStep];
    auto NormCounts = new double[nStep];
    auto NormCounts_1 = new double[nStep];

    double E, Cnt;

    double PI = 3.1415;

    ifstream infile1;

    infile1.open("/mnt/hgfs/VMplayer/UMG3.3/Detector_No_1.txt");

    for (int i = 0; i < nStep; i++) {
        infile1 >> E >> Cnt;
        Energy[i] = E;
        Counts[i] = Cnt;
        Counts[0] = 0.001;
        Energy[0] = 0.001;
    }

    infile1.close();

    double delta = Energy[10]-Energy[9];

    for (int i=0; i<nStep; i++)
    {
//        Sigma[i] = a+b/sqrt(Energy[i]);
//        Sigma[i] = 0.01;
        Sigma[i] = 2.55*(sqrt(1000000*Energy[i]*w*F))/1000000;
    }

    for (int i = 0; i < nStep; i++)
    {
        for (int j = 0; j < nStep; j++)
        {

            P1[i][j] = (delta*Counts[j] / (sqrt(2 * PI * Sigma[i]*Sigma[i]))) *
                       exp(-1*(((Energy[i] - Energy[j]) * (Energy[i] - Energy[j])) /
                               (2 * Sigma[i]*Sigma[i])));

        }

    }

    double sum1 = 0;

    for (int i = 0; i < nStep; i++)
    {
        for (int j = 0; j < nStep; j++)
        {
            sum1 += P1[i][j];
        }

        NormCounts_1[i] = sum1;
        sum1 = 0;

    }

    double sum2 =0;

    for (int i=0; i<nStep; i++)
    {
        sum2+=delta*Counts[i];
    }

    double sum3 =0;

    for (int i=0; i<nStep; i++)
    {
        sum3+=delta*NormCounts_1[i];
    }

    for (int i=0; i<nStep; i++)
    {
        NormCounts[i]=(sum2/sum3)*NormCounts_1[i];
    }



        fstream fout3 ("/mnt/hgfs/VMplayer/UMG3.3/Detector #1 Norm.txt", ios::out);


        for (int i = 0; i < nStep; i++) {

        fout3 << Energy[i] << '\t'<< NormCounts[i] << '\n';

        }
        fout3.close();


    fstream fout4(foldername, ios::out);
    for (int i = 0; i < nStep; i++) {

        fout4 << NormCounts[i] << '\n';
    }
    fout4.close();



    for (int i = 0; i < nStep; i++) { delete[] P1[i]; }


    delete [] Counts;
    delete [] NormCounts;
    delete [] NormCounts_1;
    delete [] Sigma;

    int Nchan = nStep;


    auto Sum = new double *[nStep];
    for (int i = 0; i < nStep; i++) {
        Sum[i] = new double[102];
    }

    for (int i = 0; i<nStep; i++)
    {
        Sum[i][0] = Energy[i];
    }



    char label1 [ ] = "/mnt/hgfs/VMplayer/UMG3.3/Res_";



    char OutPath[256];
    sprintf (OutPath, "%s%i%s", label1, 1, "_Sum_Output.txt");

    fstream fout5 (OutPath, ios::out);

    char SpectraPath [256];

    for (int j=1; j<=101; j++)
    {
        sprintf (SpectraPath, "%s%i%s", label1, j, ".txt");

        ifstream readFile;
        readFile.open(SpectraPath);

        double count =0;

        for (int i=0; i<Nchan; i++)
        {
            readFile >> count;
            Sum[i][j] = count;
            count =0;
        }
        readFile.close();

    }

    fstream fout6("/mnt/hgfs/VMplayer/UMG3.3/Summ.txt", ios::out);

    for (int i=0; i<Nchan; i++)
    {
        for (int j=0; j <=101; j++)
        {fout6 << Sum[i][j] << " ";}

        fout6 << endl;
    }



    fout6.close();

    delete [] Energy;

    for (int i = 0; i < nStep; i++) { delete[] Sum[i]; }


}

void RunAct::AddEvent1(G4double energy1)
{
    auto it1 = result1->lower_bound(energy1);
    it1->second++;
}

void RunAct::AddEvent2(G4double energy2)
{
    auto it2 = result2->lower_bound(energy2);
    it2->second++;

}


void RunAct::AddEvent3(G4double energy3)
{
    auto it2 = result3->lower_bound(energy3);
    it2->second++;

}

void RunAct::SetNewResPath(G4String newPath) {

    foldername = newPath;

}


