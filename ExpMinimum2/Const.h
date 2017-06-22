#pragma once
#include "Common.h"

namespace Constants
{
    const Int_t BIN = 4090;
    const Int_t HISTMIN = 0;
    const Int_t HISTMAX = 4089;

    const Int_t YEAR = 2017;
    const Int_t MONTH = 6;
    const Int_t DAY = 7;
    const Int_t DATE = 20170607;    //Following the format of TDatime

    const Int_t NCANVAS = 10;

    const UInt_t INHIBIT_TIME = 9999 * 0.1;   // second

    const TString AXIS_NAME = ";ADC Channel;Frequency";
    const TString TREE_NAME = "tree";
    const TString LEAF_NAME_ADC = "adc";
    const TString LEAF_NAME_TIME = "hms";


};

enum Element { Co60, Cs137, Ba133, BG, LYSO, Pedestal };

