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

#ifndef _SO_RAY_PICK_ACTION_H_
#define _SO_RAY_PICK_ACTION_H_

#include <Inventor/confdep.h>
#if defined(COIN_EXCLUDE_SORAYPICKACTION)
#error "This file is excluded from Coin through the configuration system!"
#endif // COIN_EXCLUDE_SORAYPICKACTION

#include <Inventor/actions/SoPickAction.h>

class SbVec2s;
class SbVec2f;
class SbVec3f;
class SbViewportRegion;
class SoPickedPoint;
class SoPickedPointList;

class SoRayPickAction : public SoPickAction {
  typedef SoPickAction inherited;

//$ BEGIN TEMPLATE ActionHeader( SoRayPickAction )
private:
  static SoType classTypeId;

public:
  virtual SoType getTypeId(void) const;
  static SoType getClassTypeId(void);

protected:
  virtual const SoEnabledElementsList & getEnabledElements(void) const;
  static SoEnabledElementsList * enabledElements;
  static SoActionMethodList * methods;

public:
  static void addMethod(const SoType type, SoActionMethod method);
  static void enableElement(const SoType type, const int stackIndex);

  static void initClass(void);
  static void cleanClass(void);

  virtual ~SoRayPickAction();
//$ END TEMPLATE ActionHeader

public:
  SoRayPickAction(const SbViewportRegion & viewportRegion);

  void setPoint(const SbVec2s & viewportPoint);
  void setNormalizedPoint(const SbVec2f & normPoint);
  void setRadius(float radiusInPixels);
  void setRay(const SbVec3f & start, const SbVec3f & direction,
	      float nearDistance = -1.0,
	      float farDistance = -1.0);
  void setPickAll(SbBool flag);
  SbBool isPickAll(void) const;
  const SoPickedPointList & getPickedPointList(void) const;
  SoPickedPoint * getPickedPoint(int index = 0) const;

}; // class SoRayPickAction

#endif // ! _SO_RAY_PICK_ACTION_H_
