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

#ifndef __SOEXTSELECTION_H__
#define __SOEXTSELECTION_H__

#include <Inventor/nodes/SoSelection.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/SbColor.h>

#if defined(COIN_EXCLUDE_SOEXTSELECTION)
#error Configuration settings disrespected -- do not include this file!
#endif // COIN_EXCLUDE_SOEXTSELECTION

// *************************************************************************

class SoExtSelection : public SoSelection {
  typedef SoSelection inherited;

//$ BEGIN TEMPLATE NodeHeader( SoExtSelection )
private:
  static SoType classTypeId;

public:
  static SoType getClassTypeId(void);
  virtual SoType getTypeId(void) const;
  static void * createInstance(void);
public:
  static void initClass(void);
  static void cleanClass(void);

  SoExtSelection(void);
protected:
  virtual ~SoExtSelection();
//$ END TEMPLATE NodeHeader

public:
  enum LassoType {
    NOLASSO, LASSO, RECTANGLE
  };

  enum LassoPolicy {
    FULL_BBOX, PART_BBOX, FULL, PART
  };

  SoSFEnum lassoType;
  SoSFEnum lassoPolicy;

  void useOverlay(SbBool flg = TRUE);
  SbBool isUsingOverlay(void);
  SoSeparator * getOverlaySceneGraph(void);
  void setOverlayLassoColorIndex(int index);
  int getOverlayLassoColorIndex(void);
  void setLassoColor(SbColor c);
  SbColor getLassoColor(void);
  void setLassoWidth(float width);
  float getLassoWidth(void);
  void setOverlayLassoPattern(unsigned short pattern);
  unsigned short getOverlayLassoPattern(void);
  void animateOverlayLasso(SbBool flg = TRUE);
  SbBool isOverlayLassoAnimated(void);
};

#endif // !__SOEXTSELECTION_H__
