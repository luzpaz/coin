#ifndef COIN_SOACTIONP_H
#define COIN_SOACTIONP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2008 by Kongsberg SIM.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg SIM about acquiring
 *  a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg SIM, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#ifndef COIN_INTERNAL
#error this is a private header file
#endif /* !COIN_INTERNAL */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "misc/SoCompactPathList.h"

#ifdef HAVE_SCENE_PROFILING
#include <Inventor/annex/Profiler/nodekits/SoProfilerOverlayKit.h>
#endif // HAVE_SCENE_PROFILING

class SoActionP {
public:
  SoAction::AppliedCode appliedcode;
  int returnindex;
  union AppliedData {
    SoNode * node;
    SoPath * path;
    struct {
      const SoPathList * pathlist;
      const SoPathList * origpathlist;
      SoCompactPathList * compactlist;
    } pathlistdata;
  } applieddata;
  SbBool terminated;
  SbList <SbList<int> *> pathcodearray;
  int prevenabledelementscounter;

#ifdef HAVE_SCENE_PROFILING
  static SoProfilerOverlayKit * getProfilerOverlay(void);
  static SoProfilerStats * getProfilerStatsNode(void);
#endif // HAVE_SCENE_PROFILING
}; // SoActionP

#endif // !COIN_SOACTIONP_H