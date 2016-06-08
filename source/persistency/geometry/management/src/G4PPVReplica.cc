// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4PPVReplica.cc,v 1.1 1999/01/07 16:10:49 gunter Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
//
//

#include "G4PPVReplica.hh"

#include "HepODBMS/clustering/HepClustering.h"

#include "globals.hh"

#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"

#include "G4PVReplica.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PLogicalVolume.hh"

G4PPVReplica::G4PPVReplica( G4VPhysicalVolume* PhysVol,
		                    HepRef(G4PLogicalVolume) persLogVol)
 :  G4PVPhysicalVolume(PhysVol, persLogVol)
{
  EAxis axis;
  G4int nReplicas;
  G4double width;
  G4double offset;
  G4bool consuming;

  PhysVol->GetReplicationData(axis, nReplicas, width, offset, consuming);
  faxis      = axis;
  fnReplicas = nReplicas;
  fwidth     = width;
  foffset    = offset;
  fcopyNo    = PhysVol->GetCopyNo();
}

G4PPVReplica::~G4PPVReplica()
{
}

G4VPhysicalVolume* G4PPVReplica::MakeTransientObject(
                             G4LogicalVolume* aLogical,
                             G4VPhysicalVolume* aMother)
{
  const G4String pName = (const char *) GetName();
  EAxis pAxis = faxis;
  G4int nReplicas = fnReplicas;
  G4double width = fwidth;
  G4double offset = foffset;

  G4VPhysicalVolume* aPhysVol = new G4PVReplica(
        pName, aLogical, aMother, pAxis, nReplicas, width, offset);

  return aPhysVol;
}

G4bool G4PPVReplica::IsMany() const
{
  return false; 
}

G4int G4PPVReplica::GetCopyNo() const
{
  return fcopyNo;
}

void  G4PPVReplica::SetCopyNo(G4int newCopyNo)
{
  fcopyNo= newCopyNo;
}
