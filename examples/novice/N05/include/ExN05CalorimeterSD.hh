// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: ExN05CalorimeterSD.hh,v 1.1 1999/01/07 16:06:11 gunter Exp $
// GEANT4 tag $Name: geant4-00-01 $
//

#ifndef ExN05CalorimeterSD_h
#define ExN05CalorimeterSD_h 1

#include "ExN05CalorimeterHit.hh"

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"

class ExN05CalorimeterSD : public G4VSensitiveDetector
{

  public:
      ExN05CalorimeterSD(G4String name, G4int nCells, G4String colName);
      ~ExN05CalorimeterSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
      void EndOfEvent(G4HCofThisEvent*HCE);
      void clear();
      void DrawAll();
      void PrintAll();

  private:
      ExN05CalorimeterHitsCollection *CalCollection;

      int* CellID;
      int numberOfCells;
      int HCID;
};




#endif

