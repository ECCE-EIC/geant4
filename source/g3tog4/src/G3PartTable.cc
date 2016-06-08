// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G3PartTable.cc,v 1.4 1999/05/28 21:09:02 lockman Exp $
// GEANT4 tag $Name: geant4-00-01 $
//

#include <strstream.h>
#include "globals.hh" 
#include "G3PartTable.hh"

G3PartTable::G3PartTable(){
  _PTD = new RWTPtrHashDictionary<G4String,G4ParticleDefinition>(G4String::hash);
}

G3PartTable::~G3PartTable(){
  _PTD->clearAndDestroy();
  delete _PTD;
  G4cout << "Deleted G3PartTable..." << endl;
};

G4ParticleDefinition*
G3PartTable::get(G4int partid){
  G4String _ShashID; // static
  HashID(partid, _ShashID);
  return _PTD->findValue(&_ShashID);
};

void 
G3PartTable::put(G4int partid, G4ParticleDefinition *partpt){
  G4String* _HashID = new G4String(); // Dynamic
  HashID(partid, _HashID);
  _PTD->insertKeyAndValue(_HashID, partpt);
};

void
G3PartTable::HashID(G4int partid, G4String& _HashID){
  char s[20];
  ostrstream ostr(s, sizeof s);
  ostr << "Part" << partid << ends;
  _HashID = s;
};

void 
G3PartTable::HashID(G4int partid, G4String* _HashID){
  HashID(partid, *_HashID);
};

