//---------------------------------------------------------------
// Assignment Copyright 2021, Ed Keenan, all rights reserved.
// Refactored by Kevin Endres
//---------------------------------------------------------------

#include "Vect4D.h"

Vect4D::Vect4D()
{
}

Vect4D::Vect4D( float tx, float ty, float tz, float tw )
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect4D::Vect4D(__m128 SIMD)
	: _m(SIMD)
{
}

Vect4D::Vect4D(const Vect4D& R)
	: x(R.x), y(R.y), z(R.z), w(R.w)
{
}

Vect4D& Vect4D::operator= (const Vect4D& R)
{
	this->x = R.x;
	this->y = R.y;
	this->z = R.z;
	this->w = R.w;
	return *this;
}

Vect4D::~Vect4D()
{
	// nothing to delete
}

Vect4D Vect4D::operator + (const Vect4D &t) const
{
	return Vect4D(this->x + t.x, this->y + t.y, this->z + t.z, 1.0f);
}

Vect4D Vect4D::operator - (const Vect4D &t) const
{
	return Vect4D(this->x - t.x, this->y - t.y, this->z - t.z, 1.0f);
}

Vect4D Vect4D::operator *(const float scale) const
{
	return Vect4D(this->x * scale, this->y * scale, this->z * scale, 1.0f);
}

Vect4D& Vect4D::operator+= (const Vect4D& R)
{
	this->_m = _mm_add_ps(this->_m, R._m);
	return *this;
}

Vect4D& Vect4D::operator*= (const float scale)
{
	this->x *= scale;
	this->y *= scale;
	this->z *= scale;
	return *this;
}

float Vect4D::getX() const
{
	return this->x;
}

float Vect4D::getY() const
{
	return this->y;
}

float Vect4D::getZ() const
{
	return this->z;
}

void Vect4D::Cross(const Vect4D& vin, Vect4D& vout) const
{
	Vect4D A, B, C, D;
	D._m = this->_m;
	A._m = _mm_shuffle_ps(D._m, D._m, _MM_SHUFFLE(3, 0, 2, 1));
	B._m = _mm_shuffle_ps(vin._m, vin._m, _MM_SHUFFLE(3, 1, 0, 2));
	A._m = _mm_mul_ps(A._m, B._m);


	C._m = _mm_shuffle_ps(vin._m, vin._m, _MM_SHUFFLE(3, 0, 2, 1));
	B._m = _mm_shuffle_ps(D._m, D._m, _MM_SHUFFLE(3, 1, 0, 2));
	B._m = _mm_mul_ps(B._m, C._m);

	vout._m = _mm_sub_ps(A._m, B._m);
}

void Vect4D::norm(Vect4D& out) const
{
	Vect4D temp;
	temp._m = _mm_mul_ps(this->_m, this->_m);
	temp._m = _mm_hadd_ps(temp._m, temp._m);
	temp._m = _mm_hadd_ps(temp._m, temp._m);
	temp._m = _mm_sqrt_ss(temp._m);
	if (temp.x != 0) {
		temp._m = _mm_set_ps1(temp.x);
		out._m = _mm_div_ps(this->_m, temp._m);
		temp._m = _mm_set_ps1(0.05f);
		out._m = _mm_mul_ps(out._m, temp._m);
		out.w = 1.0f;
	}
}

void Vect4D::set(const float tx, const float ty, const float tz, const float tw)
{
	this->x = tx;
	this->y = ty;
	this->z = tz;
	this->w = tw;
}

void Vect4D::setM(const __m128 SIMD)
{
	this->_m = SIMD;
}
// --- End of File ---
