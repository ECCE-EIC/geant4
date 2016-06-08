// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: ExN05EventAction.cc,v 1.2 1999/04/16 12:05:02 kurasige Exp $
// GEANT4 tag $Name: geant4-00-01 $
//

#include "ExN05EventAction.hh"
#include "ExN05EventActionMessenger.hh"
#include "ExN05CalorimeterHit.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include <rw/tvordvec.h>
#include "G4ios.hh"

ExN05EventAction::ExN05EventAction()
  :drawFlag(false)
{
  new ExN05EventActionMessenger(this);
}

ExN05EventAction::~ExN05EventAction()
{;}

void ExN05EventAction::BeginOfEventAction(const G4Event*)
{
  if(drawFlag)
    {
      G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
      if(pVVisManager)
	{
	  G4UImanager::GetUIpointer()->ApplyCommand("/vis~/draw/current");
	}
    }
}

void ExN05EventAction::EndOfEventAction(const G4Event* evt )
{
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  G4String colNam;
  calorimeterCollID    = SDman->GetCollectionID(colNam="CalCollection");
  hadCalorimeterCollID = SDman->GetCollectionID(colNam="HadCollection");
  
   G4cout << ">>> Event " << evt->GetEventID() << endl;
  
  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
  ExN05CalorimeterHitsCollection* CaloHC    = NULL;
  ExN05CalorimeterHitsCollection* HadCaloHC = NULL;
  if(HCE)
    {
      CaloHC    = (ExN05CalorimeterHitsCollection*)(HCE->GetHC(calorimeterCollID));
      HadCaloHC = (ExN05CalorimeterHitsCollection*)(HCE->GetHC(hadCalorimeterCollID));
    }
  
  if(CaloHC)
    {
      int n_hit = CaloHC->entries();
      G4cout << "     " << n_hit
	   << " hits are stored in EM ExN05CalorimeterHitsCollection." << endl;
      G4double totE = 0;
      for(int i=0;i<n_hit;i++)
	{ totE += (*CaloHC)[i]->GetEdep(); }
      G4cout << "     Total energy deposition in EM calorimeter crytals : "
	   << totE / GeV << " (GeV)" << endl;
    }

  if(HadCaloHC)
    {
      int n_hit = HadCaloHC->entries();
      G4cout << "     " << n_hit
	   << " hits are stored in HAD ExN05CalorimeterHitsCollection." << endl;
      G4double totE = 0;
      for(int i=0;i<n_hit;i++)
	{ totE += (*HadCaloHC)[i]->GetEdep(); }
      G4cout << "     Total energy deposition in HAD calorimeter towers : "
	   << totE / GeV << " (GeV)" << endl;
    }
  
  if(drawFlag)
    {
      G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
      if(pVVisManager)
	{
	  if(CaloHC)    CaloHC->DrawAllHits();
	  if(HadCaloHC) HadCaloHC->DrawAllHits();
	  G4UImanager::GetUIpointer()->ApplyCommand("/vis~/show/view");
	}
    }
}



