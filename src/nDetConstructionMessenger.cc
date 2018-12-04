//
// Created by David Pérez Loureiro on 1/31/17.
//

#include "nDetConstructionMessenger.hh"

#include "nDetConstruction.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4SystemOfUnits.hh"

nDetConstructionMessenger::nDetConstructionMessenger(nDetConstruction* detector) : messengerHandler(), fDetector(detector) {
    addDirectory("/nDet/detector/", "Detector geometry control");

    addCommand(new G4UIcmdWithAString("/nDet/detector/setGeometry", this));
    addGuidance("Defines the Geometry of the detector");
    addGuidance("Default is the disk");
    addCandidates("disk hexagon ellipse rectangle array");

    addCommand(new G4UIcmdWithAString("/nDet/detector/setSpectralResponse", this));
    addGuidance("Load PMT spectral response from a root file");
    addGuidance("Input file MUST contain a TGraph named \"spec\"");

	addCommand(new G4UIcmdWithAString("/nDet/detector/setGainMatrix", this));
    addGuidance("Load segmented PMT anode gain matrix file");

    addCommand(new G4UIcmdWithADouble("/nDet/detector/setSiPMdimensions", this));
    addGuidance("Defines the size of the SiPMs in mm");

    addCommand(new G4UIcmdWithADouble("/nDet/detector/setDetectorLength", this));
    addGuidance("Defines the size of the plastic in cm");

    addCommand(new G4UIcmdWithADouble("/nDet/detector/setDetectorWidth", this));
    addGuidance("Defines the width of the plastic in cm");

    addCommand(new G4UIcmdWithADouble("/nDet/detector/setDetectorThickness", this));
    addGuidance("Defines the thickness of the plastic in mm");

    addCommand(new G4UIcmdWithADouble("/nDet/detector/setMylarThickness", this));
    addGuidance("Defines the thickness of the plastic the mylar in mm (0 for no mylar)");

    addCommand(new G4UIcmdWithADouble("/nDet/detector/setTrapezoidLength", this));
    addGuidance("Defines the length of the trapezoidal part of ellipse in cm");

    addCommand(new G4UIcommand("/nDet/detector/update", this));
    addGuidance("Updates the detector Geometry");

    addCommand(new G4UIcmdWithAnInteger("/nDet/detector/setNumColumns", this));
    addGuidance("Set the number of columns in a segmented scintillator.");
    
    addCommand(new G4UIcmdWithAnInteger("/nDet/detector/setNumRows", this));
    addGuidance("Set the number of rows in a segmented scintillator.");
    
    addCommand(new G4UIcmdWithAnInteger("/nDet/detector/setPmtColumns", this));
    addGuidance("Set the number of anode columns in a segmented PSPMT.");
    
    addCommand(new G4UIcmdWithAnInteger("/nDet/detector/setPmtRows", this));
    addGuidance("Set the number of anode rows in a segmented PSPMT.");
}

void nDetConstructionMessenger::SetNewValue(G4UIcommand* command, G4String newValue){
	size_t index;
	if(!findCommand(command, index)) return;

    if(index == 0){
        fDetector->SetGeometry(newValue);
    }
	else if(index == 1){
		fDetector->setPmtSpectralResponse(newValue.c_str());
	}
	else if(index == 2){
		fDetector->setPmtGainMatrix(newValue.c_str());
	}
    else if(index == 3) {
        G4double dimensions = command->ConvertToDouble(newValue);
        fDetector->SetSiPM_dimension(dimensions/2.*mm);
    }
    else if(index == 4) {
        G4double length = command->ConvertToDouble(newValue);
        fDetector->SetDetectorLength(length*cm);
    }
    else if(index == 5) {
        G4double length = command->ConvertToDouble(newValue);
        fDetector->SetDetectorWidth(length*cm);
    }
    else if(index == 6) {
        G4double thickness = command->ConvertToDouble(newValue);
        fDetector->SetDetectorThickness(thickness*mm);
    }
    else if(index == 7) {
        G4double val = command->ConvertToDouble(newValue);
        fDetector->SetMylarThickness(val*mm);
    }    
    else if(index == 8) {
        G4double length = command->ConvertToDouble(newValue);
        fDetector->SetTrapezoidLength(length*cm);
    }
    else if(index == 9){
       fDetector->UpdateGeometry();
    }
    else if(index == 10){
        G4int val = command->ConvertToInt(newValue);
        fDetector->SetNumColumns(val);
    }
    else if(index == 11){
        G4int val = command->ConvertToInt(newValue);
        fDetector->SetNumRows(val);
    }
    else if(index == 12){
        G4int val = command->ConvertToInt(newValue);
        fDetector->SetNumPmtColumns(val);
    }
    else if(index == 13){
        G4int val = command->ConvertToInt(newValue);
        fDetector->SetNumPmtRows(val);
    }
}
