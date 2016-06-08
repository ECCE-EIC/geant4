// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4THitsCollection.cc,v 1.1 1999/01/07 16:06:31 gunter Exp $
// GEANT4 tag $Name: geant4-00-01 $
//

#include "G4THitsCollection.hh"

G4Allocator<G4HitsCollection> anHCAllocator;

G4HitsCollection::G4HitsCollection()
{;}

G4HitsCollection::G4HitsCollection(G4String detName,G4String colNam)
: G4VHitsCollection(detName,colNam)
{;}

G4HitsCollection::~G4HitsCollection()
{;}

int G4HitsCollection::operator==(const G4HitsCollection &right) const
{ return (collectionName==right.collectionName); }

