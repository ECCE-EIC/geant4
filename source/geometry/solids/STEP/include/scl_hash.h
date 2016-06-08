

//



//
// $Id: scl_hash.h,v 1.2 1999/05/21 20:20:43 japost Exp $
// GEANT4 tag $Name: geant4-00-01 $
//

#ifndef SCL_HASH_H
#define SCL_HASH_H

/*
* NIST Utils Class Library
* clutils/scl_hash.h
* May 1995
* David Sauder
* K. C. Morris

* Development of this software was funded by the United States Government,
* and is not subject to copyright.
*/

/*  */

/************************************************************************
** Hash_Table:	Hash_Table
** Description:	
**	
** Largely based on code written by ejp@ausmelb.oz
**
** Constants:
**	HASH_TABLE_NULL	- the null Hash_Table
**
************************************************************************/

/*
 * This work was supported by the United States Government, and is
 * not subject to copyright.
 *
 * $Log: scl_hash.h,v $
 * Revision 1.2  1999/05/21 20:20:43  japost
 * Deleted incorrect RD44/Geant4 copyright statement
 *
 * Revision 1.1  1999/01/07 16:08:09  gunter
 * Files from release of geant4.0.0- tag geant4-00
 *
 * Revision 2.0  1998/07/02 17:03:57  gunter
 * Set version 2.0
 *
 * Revision 1.1  1998/07/02 15:41:11  gunter
 * Import for geant4beta
 *
 * Revision 1.4  1997/08/06 15:51:01  jsulkimo
 *   Going back to Gabrielle's changes - kept only the newly modified
 * SdaiCONFIG_CONTROL_DESIGN.h.
 *
 * Revision 1.2  1997/06/28 00:15:30  gcosmo
 * Porting on DEC-OSF1
 *
 * Revision 1.1.1.1  1997/02/12 10:52:33  tsasaki
 * GEANT4 alpha
 *
 * Revision 1.1  1996/08/20 15:32:59  jsulkimo
 * created
 *
 * Revision 2.1.0.1  1995/05/16  14:35:29  lubell
 * setting state to dp21
 *
 * Revision 2.1.0.0  1995/05/12  14:13:33  lubell
 * setting branch
 *
 * Revision 2.1  1995/05/12  14:13:32  lubell
 * changing version to 2.1
 *
 * Revision 2.0.1.2  1995/05/09  20:04:42  lubell
 * Changed the date from 2/94 to 5/95
 *
 * Revision 2.0.1.1  1994/04/05  16:44:11  sauderd
 * Changed the date from 1993 to 1994
 *
 * Revision 2.0.1.0  1994/02/04  21:32:20  sauderd
 * Setting the first branch
 *
 * Revision 2.0  1994/02/04  21:32:18  sauderd
 * STEP Class Library Release 2.0
 *
 * Revision 1.3  1994/09/30  20:58:22  sauderd
 * Administrative stuff for the release.  Added the name of the file, library,
 * the date, contact people, and $id $ for RCS.  Did general cleaning, etc.
 *
 * Revision 1.2  1992/12/15  14:07:52  kc
 * made parameters to HASHfind and HASHinsert const
 *
 * Revision 1.1  1992/10/07  18:37:20  kc
 * Initial revision
 *
 * Revision 1.1  1992/10/06  22:06:30  kc
 * Initial revision
 *
 * Revision 1.1  1992/09/29  15:44:19  libes
 * Initial revision
 *
 * Revision 1.1  1992/08/19  18:49:59  libes
 * Initial revision
 *
 * Revision 1.2  1992/05/31  08:36:48  libes
 * multiple files
 * 
 */

typedef enum { HASH_FIND, HASH_INSERT, HASH_DELETE } Action;

struct Symbol { }; /* empty if not used */

struct Element {
	char		*key;
	void		*data;
	struct Element	*next;
	struct Symbol	*symbol;/* for debugging hash conflicts */
	char		type;	/* user-supplied type */
};

struct Hash_Table {
	short	p;		/* Next bucket to be split	*/
	short	maxp;		/* upper bound on p during expansion	*/
	long	KeyCount;	/* current # keys	*/
	short	SegmentCount;	/* current # segments	*/
	short	MinLoadFactor;
	short	MaxLoadFactor;
#define DIRECTORY_SIZE		256
#define DIRECTORY_SIZE_SHIFT	8	/* log2(DIRECTORY_SIZE)	*/
	struct Element **Directory[DIRECTORY_SIZE];
};

typedef struct {
	int i;	/* segment index (i think) */
	int j;	/* key index in segment (ditto) */
	struct Element *p;	/* usually the next element to be returned */
	struct Hash_Table *table;
	char type;
	struct Element *e;	/* originally thought of as a place for */
/* the caller of HASHlist to temporarily stash the return value */
/* to allow the caller (i.e., DICTdo) to be macroized, but now */
/* conveniently used by HASHlist, which both stores the ultimate */
/* value here as well as returns it via the return value of HASHlist */
} HashEntry;

#ifdef __cplusplus
extern "C" {
#endif

struct Hash_Table	*HASHcreate(unsigned);
void		*HASHfind(struct Hash_Table *,  char *);
void		HASHinsert(struct Hash_Table *, char *,void *);
void		HASHdestroy(struct Hash_Table *);
struct Element	*HASHsearch(struct Hash_Table *,struct Element *, Action);
void		HASHlistinit(struct Hash_Table *,HashEntry *);
void		HASHlistinit_by_type(struct Hash_Table *,HashEntry *,char);
struct Element	*HASHlist(HashEntry *);

#ifdef __cplusplus
}
#endif

#endif /* SCL_HASH_H */
