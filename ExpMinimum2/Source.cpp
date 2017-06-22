#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 1
#define STRING(var) #var

#include "Common.h"

#include "ADCInfo.h"
#include "Const.h"




using namespace Constants;



int main(int argc, char *argv[])
{
    // Open ROOT window
    TApplication app("Root Window", &argc, argv);

    vector<ADCInfo> dataSet;




    // file input (Files in same location as Source.cpp)
    ifstream ifs("fileList.csv");
    if (!ifs) {
        cout << "File input error" << endl;
        return 1;
    }

    string str;
    int nFiles = 0;
    int nElements = 0;
    while (getline(ifs, str)) {
        string token;
        istringstream stream(str);
        enum Element type;
        TFile *file;
        while (getline(stream, token, ',')) {
            if (token == "Co60")
            {
                type = Element::Co60;
                nElements++;
            }
            else if (token == "Cs137")
            {
                type = Element::Cs137;
                nElements++;
            }
            else if (token == "Ba133")
            {
                type = Element::Ba133;
                nElements++;
            }
            else if (token == "LYSO")
            {
                type = Element::LYSO;
                nElements++;
            }
            else if (token == "BG") type = Element::BG;
            else if (token == "Pedestal") type = Element::Pedestal;
            else
            {
                const char* fileName = token.c_str();
                file = new TFile(fileName, "read");
                dataSet.push_back(ADCInfo(file, type));
                file->Close();
                delete file;
                nFiles++;
            }
        }
    }

    Int_t nCanvas = nFiles + nElements;

    TCanvas *canvases[NCANVAS];

    vector<TH1D> hists;
    ADCInfo *infoBG;
    TH1D *histBG;
    Int_t BGNum;

    for (Int_t i = 0; i < nFiles; i++)
    {
        switch (dataSet[i].type)
        {
        case Element::Ba133:
            hists.push_back(TH1D("Ba133", AXIS_NAME, BIN, HISTMIN, HISTMAX)); break;
        case Element::Cs137:
            hists.push_back(TH1D("Cs137", AXIS_NAME, BIN, HISTMIN, HISTMAX)); break;
        case Element::Co60:
            hists.push_back(TH1D("Co60", AXIS_NAME, BIN, HISTMIN, HISTMAX)); break;
        case Element::LYSO:
            hists.push_back(TH1D("LYSO", AXIS_NAME, BIN, HISTMIN, HISTMAX)); break;
        case Element::Pedestal:
            hists.push_back(TH1D("Pedestal", AXIS_NAME, BIN, HISTMIN, HISTMAX)); break;
        case Element::BG:
            hists.push_back(TH1D("BG", AXIS_NAME, BIN, HISTMIN, HISTMAX)); break;
        }

        for (Int_t j = 0; j < dataSet[i].nEntries; j++)
        {
            hists.back().Fill((Double_t)dataSet[i].ADCChannel[j]);
        }
        canvases[i] = new TCanvas();
        hists.back().Draw();
        if (dataSet[i].type == Element::BG)
        {
            //infoBG = &dataSet[i];
            //histBG = &hists[i];
            BGNum = i;
        }
    }

    Int_t k = 0;
    for (Int_t i = 0; i < nFiles; i++)
    {
        switch (dataSet[i].type)
        {
        case Element::Ba133:
            hists.push_back(TH1D("Ba133 - BG", AXIS_NAME, BIN, HISTMIN, HISTMAX));
            break;
        case Element::Cs137:
            hists.push_back(TH1D("Cs137 - BG", AXIS_NAME, BIN, HISTMIN, HISTMAX));
            break;
        case Element::Co60:
            hists.push_back(TH1D("Co60 - BG", AXIS_NAME, BIN, HISTMIN, HISTMAX));
            break;
        case Element::LYSO:
            hists.push_back(TH1D("LYSO - BG", AXIS_NAME, BIN, HISTMIN, HISTMAX));
            break;
        default:
            continue;
        }
        
        //hists.back().Add(&hists[i], histBG, 1.0, -(Double_t)dataSet[i].measurementTime / (Double_t)infoBG->measurementTime);
        hists.back().Add(&hists[i], &hists[BGNum], 1.0, -(Double_t)dataSet[i].measurementTime / (Double_t)dataSet[BGNum].measurementTime);
        canvases[k++ + nFiles] = new TCanvas();
        hists.back().Draw();

    }

    for (Int_t i = 0; i < NCANVAS; i++)
    {
        //canvases[i]->Update();
    }

    canvases[0]->Print("hist.pdf(");
    for (Int_t i = 1; i < nCanvas - 1; i++)
    {
        canvases[i]->Print("hist.pdf");
    }
    canvases[nCanvas - 1]->Print("hist.pdf)");


    TFile histsFile("histograms.root", "RECREATE");
    for (Int_t i = 0; i < nCanvas; i++)
    {
        hists[i].Write();
        
    }
    histsFile.Close();

    //app.Run();

    return 0;

}