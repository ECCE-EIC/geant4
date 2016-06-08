// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4oCommon.hh,v 1.2 1999/04/16 10:03:23 barrand Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
/*
   Included by G4o.h.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*G4*/
#include <G4UImanager.hh>
#include <G4UIcommand.hh>
#include <G4UIparameter.hh>
#include <G4UIcommandTree.hh>

/*Co*/
#include <CMemory.h>
#include <CPrinter.h>
#include <CText.h>
#include <CFile.h>
#include <OType.h>
#include <OShell.h>
#include <OProcess.h>


static void         SetTypes                      ();
static void         ExecuteScript                 (char*);
static int          Execute_G4                    (int,char**,OProcess);
static int          DoMethod                      (OIdentifier,char*,void*,int,char**,void*,int*);
static G4UIcommand* GetCommandIdentifier          (char*);
static void         GetCommands                   (G4UIcommandTree*,int*,char***);
static int          ProduceODB                    (G4UIcommand*,char*);

