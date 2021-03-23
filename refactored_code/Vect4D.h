//---------------------------------------------------------------
// Assignment Copyright 2021, Ed Keenan, all rights reserved.
// Refactored by Kevin Endres
//---------------------------------------------------------------

#ifndef Vect4D_H
#define Vect4D_H

// includes
#include "Enum.h"
#include <immintrin.h>

// class
class Vect4D : Align16
{
public:
	friend class Matrix;

	Vect4D();	
	Vect4D( float tx, float ty, float tz, float tw = 1.0f );
	Vect4D( __m128 SIMD );
	Vect4D(const Vect4D&);
	Vect4D& operator= (const Vect4D&);
	~Vect4D();

	void norm( Vect4D &out ) const;
	void set(const float tx, const float ty, const float tz, const float tw = 1.0f);
	
	Vect4D operator + (const Vect4D &t) const;
	Vect4D operator - (const Vect4D &t) const;
	Vect4D operator * (const float scale) const;
	Vect4D& operator += (const Vect4D&);
	Vect4D& operator *= (const float);

	void Cross(const Vect4D &vin, Vect4D &vout) const;
	float getX() const;
	float getY() const;
	float getZ() const;
	void setM(const __m128);

private:
	union {
		__m128 _m;
		
		struct {
			float x;
			float y;
			float z;
			float w;
		};
	};
};

#endif

// --- End of File ---
