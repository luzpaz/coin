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

#ifndef __SOPATHLIST_H__
#define __SOPATHLIST_H__

#include <Inventor/lists/SoBaseList.h>

#if defined(COIN_EXCLUDE_SOPATH)
#error Configuration settings disrespected -- do not include this file!
#endif // COIN_EXCLUDE_SOPATH

class SoPath;

class SoPathList : public SoBaseList {
  typedef SoBaseList inherited;
public:
  SoPathList(void);
  SoPathList(const int size);
  SoPathList(const SoPathList & l);
  ~SoPathList(void);
  void append(SoPath * const path);
  SoPath * operator [](const int i) const;
  SoPathList & operator =(const SoPathList & l);
  int findPath(const SoPath & path);
  void sort(void);
  void uniquify(void);

private:
  SoPath * get(const int index) const;
  void set(const int index, SoPath * const path);
};

#endif // !__SOPATHLIST_H__
