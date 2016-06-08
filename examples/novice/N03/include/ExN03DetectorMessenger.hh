// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: ExN03DetectorMessenger.hh,v 1.1 1999/01/07 16:05:54 gunter Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef ExN03DetectorMessenger_h
#define ExN03DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class ExN03DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class ExN03DetectorMessenger: public G4UImessenger
{
  public:
    ExN03DetectorMessenger(ExN03DetectorConstruction* );
   ~ExN03DetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    ExN03DetectorConstruction* ExN03Detector;
    
    G4UIdirectory*             ExN03detDir;
    G4UIcmdWithAString*        AbsMaterCmd;
    G4UIcmdWithAString*        GapMaterCmd;
    G4UIcmdWithADoubleAndUnit* AbsThickCmd;
    G4UIcmdWithADoubleAndUnit* GapThickCmd;
    G4UIcmdWithADoubleAndUnit* SizeYZCmd;
    G4UIcmdWithAnInteger*      NbLayersCmd;    
    G4UIcmdWithADoubleAndUnit* MagFieldCmd;
    G4UIcmdWithoutParameter*   UpdateCmd;
};

#endif

