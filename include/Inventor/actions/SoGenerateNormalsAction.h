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

#ifndef _SO_GENERATE_NORMALS_ACTION_H_
#define _SO_GENERATE_NORMALS_ACTION_H_

#include <Inventor/SbBasic.h>

class SoNode;
class SoState;
class SoNormal;
class SoIndexedFaceSet;

class SoGenerateNormalsAction /* : public SoAction */ {
  typedef SoAction inherited;

// $ INSERT TEMPLATE ActionHeader( SoGenerateNormalsAction )
//^- remove space when this action is fixed... - larsa

public:
  SoGenerateNormalsAction();
  virtual ~SoGenerateNormalsAction();
  
  virtual void apply(SoNode * const node);
  
  void setCreaseAngle(const float crease_angle = -1.0f);
  void setFlipNormals(const SbBool yesno = FALSE);

private:
  static void traversegraph(SoNode *node, SoState *state, void *);
  SoNormal *createNormalNode(SoIndexedFaceSet * const fs, 
			     SoState * const state);
  
  float creaseAngle;
  SbBool flipNormals;
}; // class SoGenerateNormalsAction

#endif // ! _SO_GENERATE_NORMALS_ACTION_H_
