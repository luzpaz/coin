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

#ifndef __SODECOMPOSEVEC2F_H__
#define __SODECOMPOSEVEC2F_H__

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/engines/SoEngineOutput.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFVec2f.h>

#if defined(COIN_EXCLUDE_SODECOMPOSEVEC2F)
#error "Configuration settings disrespected -- do not include this file!"
#endif // COIN_EXCLUDE_SODECOMPOSEVEC2F

class SoDecomposeVec2f : public SoEngine {
  typedef SoEngine inherited;
  SO_ENGINE_HEADER(SoDecomposeVec2f);

public:
  SoMFVec2f vector;

  SoEngineOutput x; //SoMFFloat
  SoEngineOutput y; //SoMFFloat

  SoDecomposeVec2f();

  static void initClass();

private:
  virtual ~SoDecomposeVec2f();
  virtual void evaluate();
};

#endif // !__SODECOMPOSEVEC2F_H__
