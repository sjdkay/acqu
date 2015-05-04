#ifndef CANVASTOOL_H
#define CANVASTOOL_H

#include "TCanvas.h"
#include <string>

class CanvasTool: public TCanvas {
    ClassDef(CanvasTool, 1);
private:
    Double_t fillvalue;

public:
    CanvasTool( const std::string& name="", const std::string& title=""):
        fillvalue(1.0),
        TCanvas(name.c_str(), title.c_str()) {}

    virtual ~CanvasTool() {}

    virtual void HandleInput(EEventType event, Int_t px, Int_t py);

    virtual void SetFillValue( const Double_t value); //*MENU*
};

#endif
