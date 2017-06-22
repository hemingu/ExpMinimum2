#pragma once
#include "Common.h"
#include "Const.h"

using namespace std;

class ADCInfo
{
private:
    TFile *dataFile;
public:
    Element type;

    //TString histName;

    //TH1I *hist;
    Int_t nEntries;
    vector<Int_t> ADCChannel;
    vector<TDatime> measuredTime;
    UInt_t measurementTime;


    ADCInfo(TFile *rootFile, Element type)
    {
        dataFile = rootFile;
        this->type = type;
        TTree *tree = (TTree*)dataFile->Get(Constants::TREE_NAME);
        nEntries = tree->GetEntriesFast();


        // Get ADC Channel
        TLeaf *leaf = tree->GetLeaf(Constants::LEAF_NAME_ADC);

        for (Int_t i = 0; i < nEntries; i++)
        {
            tree->GetEntry(i);
            //cout << leaf->GetValue() << endl;
            ADCChannel.push_back(leaf->GetValue());
        }

        // Get Time
        leaf = tree->GetLeaf(Constants::LEAF_NAME_TIME);

        for (Int_t i = 0; i < nEntries; i++)
        {
            tree->GetEntry(i);
            //cout << leaf->GetValue() << endl;
            measuredTime.push_back(TDatime(Constants::DATE, leaf->GetValue()));
        }
        measurementTime = measuredTime[nEntries - 1].Convert() - measuredTime[0].Convert() - Constants::INHIBIT_TIME;

    }

    //ADCInfo(const ADCInfo &obj)
    //{
    //    this->dataFile = obj.dataFile;
    //    this->type = obj.type;
    //    this->nEntries = obj.nEntries;
    //    this->ADCChannel = obj.ADCChannel;
    //    this->measuredTime = obj.measuredTime;



    //}

    //~ADCInfo()
    //{

    //}



};