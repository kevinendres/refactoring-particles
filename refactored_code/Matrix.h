//---------------------------------------------------------------
// Assignment Copyright 2021, Ed Keenan, all rights reserved.
// Refactored by Kevin Endres
//---------------------------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Vect4D.h"
#include "Particle.h"

class Matrix : Align16
{
public:
	Matrix();	
	Matrix( const Matrix& t );	
	Matrix(const float m0, const float m1, const float m2, const float m3,
		const float m4, const float m5, const float m6, const float m7,
		const float m8, const float m9, const float m10, const float m11,
		const float m12, const float m13, const float m14, const float m15);
	Matrix(const Vect4D&, const Vect4D&, const Vect4D&, const Vect4D&);
	Matrix& operator = (const Matrix&);
	~Matrix();

	void setIdentMatrix();
	void setTransMatrix(const Vect4D &t );
	
	Matrix operator*( const Matrix &t ) const;

	float Determinant() const;
	
	Matrix GetAdjugate() const;
	Matrix& operator/=(const float t);
	Matrix& operator*=(const Matrix& t);
	
	void Inverse( Matrix &out ) const;
	
private:
	union {
		struct {
			Vect4D v0;
			Vect4D v1;
			Vect4D v2;
			Vect4D v3;
		};
		struct {
			// ROW 0
			float m0;
			float m1;
			float m2;
			float m3;

			// ROW 1
			float m4;
			float m5;
			float m6;
			float m7;

			// ROW 2
			float m8;
			float m9;
			float m10;
			float m11;

			// ROW 3
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};
};

#endif  

// --- End of File ---
