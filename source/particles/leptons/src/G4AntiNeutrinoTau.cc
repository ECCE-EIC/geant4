// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4AntiNeutrinoTau.cc,v 1.1 1999/01/07 16:10:24 gunter Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// 
// ----------------------------------------------------------------------
//      GEANT 4 class implementation file
//
//      For information related to this code contact:
//      CERN, CN Division, ASD Group
//      History: first implementation, based on object model of
//      4th April 1996, G.Cosmo 
//      by             H.Kurashige,7  July 1996
// **********************************************************************

#include <fstream.h>
#include <iomanip.h>

#include "G4AntiNeutrinoTau.hh"

// ######################################################################
// ###                   ANTI TAU NEUTRINO                            ###
// ######################################################################

G4AntiNeutrinoTau::G4AntiNeutrinoTau(
       const G4String&     aName,        G4double            mass,
       G4double            width,        G4double            charge,   
       G4int               iSpin,        G4int               iParity,    
       G4int               iConjugation, G4int               iIsospin,   
       G4int               iIsospin3,    G4int               gParity,
       const G4String&     pType,        G4int               lepton,      
       G4int               baryon,       G4int               encoding,
       G4bool              stable,       G4double            lifetime,
       G4DecayTable        *decaytable )
 : G4VLepton( aName,mass,width,charge,iSpin,iParity,
              iConjugation,iIsospin,iIsospin3,gParity,pType,
              lepton,baryon,encoding,stable,lifetime,decaytable )
{
}

// ......................................................................
// ...                 static member definitions                      ...
// ......................................................................
//     
//    Arguments for constructor are as follows
//               name             mass          width         charge
//             2*spin           parity  C-conjugation
//          2*Isospin       2*Isospin3       G-parity
//               type    lepton number  baryon number   PDG encoding
//             stable         lifetime    decay table 
//
G4AntiNeutrinoTau G4AntiNeutrinoTau::theAntiNeutrinoTau(
	"anti_nu_tau",          0.0*MeV,       0.0*MeV,         0.0, 
		    1,               0,             0,          
		    0,               0,             0,             
	     "lepton",              -1,             0,          -16,
		 true,             0.0,          NULL
);

G4AntiNeutrinoTau* G4AntiNeutrinoTau::AntiNeutrinoTauDefinition()
{
  return &theAntiNeutrinoTau;
}
// initialization for static cut values
G4double   G4AntiNeutrinoTau::theAntiNeutrinoTauLengthCut = -1.0;
G4double*  G4AntiNeutrinoTau::theAntiNeutrinoTauKineticEnergyCuts = NULL;

// **********************************************************************
// **************************** SetCuts *********************************
// **********************************************************************

void G4AntiNeutrinoTau::SetCuts(G4double aCut)
{
  theCutInMaxInteractionLength = aCut;

  const G4MaterialTable* materialTable = G4Material::GetMaterialTable();
  // Create the vector of cuts in energy
  // corresponding to the stopping range cut
  if(theKineticEnergyCuts) delete [] theKineticEnergyCuts;
  theKineticEnergyCuts = new G4double [materialTable->length()];

  // Build range vector for every material, convert cut into energy-cut,
  // fill theKineticEnergyCuts and delete the range vector
  for (G4int J=0; J<materialTable->length(); J++)
  {
    G4Material* aMaterial = (*materialTable)[J];
    theKineticEnergyCuts[J] = 0.0*keV;
  }
  theAntiNeutrinoTauLengthCut = theCutInMaxInteractionLength;  
  theAntiNeutrinoTauKineticEnergyCuts = theKineticEnergyCuts;
  // Rebuild the physics tables for every process for this particle type
  
}
