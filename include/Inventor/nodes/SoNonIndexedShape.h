/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

#ifndef __SONONINDEXEDSHAPE_H__
#define __SONONINDEXEDSHAPE_H__

#include <Inventor/nodes/SoVertexShape.h>
#include <Inventor/fields/SoSFInt32.h>

#if defined(COIN_EXCLUDE_SONONINDEXEDSHAPE)
#error Configuration settings disrespected -- do not include this file!
#endif // COIN_EXCLUDE_SONONINDEXEDSHAPE


class SoNonIndexedShape : public SoVertexShape {
  typedef SoVertexShape inherited;

//$ BEGIN TEMPLATE NodeAbstractHeader( SoNonIndexedShape )
private:
  static SoType classTypeId;

public:
  static SoType getClassTypeId(void);
  virtual SoType getTypeId(void) const;
public:
  static void initClass(void);
  static void cleanClass(void);

protected:
  SoNonIndexedShape(void);
  virtual ~SoNonIndexedShape();
//$ END TEMPLATE NodeAbstractHeader

public:
  SoSFInt32 startIndex;

protected:
#if !defined(COIN_EXCLUDE_SOGETBOUNDINGBOXACTION)
  void computeCoordBBox(SoAction * action, int numVertices,
			SbBox3f & box, SbVec3f & center);
#endif // !COIN_EXCLUDE_SOGETBOUNDINGBOXACTION
};


#endif // !__SONONINDEXEDSHAPE_H__
