#ifndef COIN_SBVEC4I32_H
#define COIN_SBVEC4I32_H

/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#include <Inventor/SbBasic.h>
#include <Inventor/system/inttypes.h>
#ifndef NDEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // !NDEBUG

class SbVec4ui32;
class SbVec4b;
class SbVec4s;
class SbVec4f;
class SbVec4d;

class COIN_DLL_API SbVec4i32 {
public:
  SbVec4i32(void) { }
  SbVec4i32(const int32_t v[4]) { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; vec[3] = v[3]; }
  SbVec4i32(int32_t x, int32_t y, int32_t z, int32_t w) { vec[0] = x; vec[1] = y; vec[2] = z; vec[3] = w; }
  explicit SbVec4i32(const SbVec4ui32 & v) { setValue(v); }
  explicit SbVec4i32(const SbVec4b & v) { setValue(v); }
  explicit SbVec4i32(const SbVec4s & v) { setValue(v); }
  explicit SbVec4i32(const SbVec4f & v) { setValue(v); }
  explicit SbVec4i32(const SbVec4d & v) { setValue(v); }

  SbVec4i32 & setValue(const int32_t v[4]) { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; vec[3] = v[3]; return *this; }
  SbVec4i32 & setValue(int32_t x, int32_t y, int32_t z, int32_t w) { vec[0] = x; vec[1] = y; vec[2] = z; vec[3] = w; return *this; }
  SbVec4i32 & setValue(const SbVec4ui32 & v);
  SbVec4i32 & setValue(const SbVec4b & v);
  SbVec4i32 & setValue(const SbVec4s & v);
  SbVec4i32 & setValue(const SbVec4f & v);
  SbVec4i32 & setValue(const SbVec4d & v);

  const int32_t * getValue(void) const { return vec; }
  void getValue(int32_t & x, int32_t & y, int32_t & z, int32_t & w) const { x = vec[0]; y = vec[1]; z = vec[2]; w = vec[3]; }

  int32_t & operator [] (int i) { return vec[i]; }
  const int32_t & operator [] (int i) const { return vec[i]; }

  int32_t dot(const SbVec4i32 & v) const { return vec[0] * v[0] + vec[1] * v[1] + vec[2] * v[2] + vec[3] * v[3]; }
  void negate(void) { vec[0] = -vec[0]; vec[1] = -vec[1]; vec[2] = -vec[2]; vec[3] = -vec[3]; }

  SbVec4i32 & operator *= (int d) { vec[0] *= d; vec[1] *= d; vec[2] *= d; vec[3] *= d; return *this; }
  SbVec4i32 & operator *= (double d);
  SbVec4i32 & operator /= (int d) { SbDividerChk("SbVec4i32::operator/=(int)", d); vec[0] /= d; vec[1] /= d; vec[2] /= d; vec[3] /= d; return *this; }
  SbVec4i32 & operator /= (double d) { SbDividerChk("SbVec4i32::operator/=(double)", d); return operator *= (1.0 / d); }
  SbVec4i32 & operator += (const SbVec4i32 & v) { vec[0] += v[0]; vec[1] += v[1]; vec[2] += v[2]; vec[3] += v[3]; return *this; }
  SbVec4i32 & operator -= (const SbVec4i32 & v) { vec[0] -= v[0]; vec[1] -= v[1]; vec[2] -= v[2]; vec[3] -= v[3]; return *this; }
  SbVec4i32 operator - (void) const { return SbVec4i32(-vec[0], -vec[1], -vec[2], -vec[3]); }

protected:
  int32_t vec[4];

}; // SbVec4i32

COIN_DLL_API inline SbVec4i32 operator * (const SbVec4i32 & v, int d) {
  SbVec4i32 val(v); val *= d; return val;
}

COIN_DLL_API inline SbVec4i32 operator * (const SbVec4i32 & v, double d) {
  SbVec4i32 val(v); val *= d; return val;
}

COIN_DLL_API inline SbVec4i32 operator * (int d, const SbVec4i32 & v) {
  SbVec4i32 val(v); val *= d; return val;
}

COIN_DLL_API inline SbVec4i32 operator * (double d, const SbVec4i32 & v) {
  SbVec4i32 val(v); val *= d; return val;
}

COIN_DLL_API inline SbVec4i32 operator / (const SbVec4i32 & v, int d) {
  SbDividerChk("operator/(SbVec4i32,int)", d);
  SbVec4i32 val(v); val /= d; return val;
}

COIN_DLL_API inline SbVec4i32 operator / (const SbVec4i32 & v, double d) {
  SbDividerChk("operator/(SbVec4i32,double)", d);
  SbVec4i32 val(v); val /= d; return val;
}

COIN_DLL_API inline SbVec4i32 operator + (const SbVec4i32 & v1, const SbVec4i32 & v2) {
  SbVec4i32 v(v1); v += v2; return v;
}

COIN_DLL_API inline SbVec4i32 operator - (const SbVec4i32 & v1, const SbVec4i32 & v2) {
  SbVec4i32 v(v1); v -= v2; return v;
}

COIN_DLL_API inline int operator == (const SbVec4i32 & v1, const SbVec4i32 & v2) {
  return ((v1[0] == v2[0]) && (v1[1] == v2[1]) && (v1[2] == v2[2]) && (v1[3] == v2[3]));
}

COIN_DLL_API inline int operator != (const SbVec4i32 & v1, const SbVec4i32 & v2) {
  return !(v1 == v2);
}

#endif // !COIN_SBVEC4I32_H
