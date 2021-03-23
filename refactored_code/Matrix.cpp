//---------------------------------------------------------------
// Assignment Copyright 2021, Ed Keenan, all rights reserved.
// Refactored by Kevin Endres
//---------------------------------------------------------------

#include <Math.h>
#include <immintrin.h>
#include "Matrix.h"

Matrix::Matrix()
{	
}

Matrix::Matrix(const float m0, const float m1, const float m2, const float m3,
				const float m4, const float m5, const float m6, const float m7,
				const float m8, const float m9, const float m10, const float m11,
				const float m12, const float m13, const float m14, const float m15)
	: m0(m0), m1(m1), m2(m2), m3(m3), m4(m4), m5(m5), m6(m6), m7(m7), 
	m8(m8), m9(m9), m10(m10), m11(m11), m12(m12), m13(m13), m14(m14), m15(m15)
{	
}

Matrix::Matrix(const Matrix& t)
	: v0(t.v0), v1(t.v1), v2(t.v2), v3(t.v3)
{
}

Matrix::Matrix(const Vect4D& t0, const Vect4D &t1, const Vect4D &t2, const Vect4D &t3)
	: v0(t0), v1(t1), v2(t2), v3(t3)
{
}

Matrix& Matrix::operator= (const Matrix& t)
{
	this->v0 = t.v0;
	this->v1 = t.v1;
	this->v2 = t.v2;
	this->v3 = t.v3;
	return *this;
}

Matrix::~Matrix()
{
}

void Matrix::setIdentMatrix()
{ 
	this->m0 = 1.0f;
	this->m1 = 0.0f;
	this->m2 = 0.0f;
	this->m3 = 0.0f;

	this->m4 = 0.0f;
	this->m5 = 1.0f;
	this->m6 = 0.0f;
	this->m7 = 0.0f;

	this->m8 = 0.0f;
	this->m9 = 0.0f;
	this->m10 = 1.0f;
	this->m11 = 0.0f;
	
	this->m12 = 0.0f;
	this->m13 = 0.0f;
	this->m14 = 0.0f;
	this->m15 = 1.0f;
}

Matrix Matrix::operator*( const Matrix& ma) const
{ 
	Vect4D A, B, C, D, BrdcstVal;
	Vect4D T1, T2, T3, T4;

	//create temps
	BrdcstVal._m = _mm_set_ps1(this->v0.x);
	A._m = _mm_mul_ps(BrdcstVal._m, ma.v0._m);

	BrdcstVal._m = _mm_set_ps1(this->v0.y);
	B._m = _mm_mul_ps(BrdcstVal._m, ma.v1._m);

	BrdcstVal._m = _mm_set_ps1(this->v0.z);
	C._m = _mm_mul_ps(BrdcstVal._m, ma.v2._m);

	BrdcstVal._m = _mm_set_ps1(this->v0.w);
	D._m = _mm_mul_ps(BrdcstVal._m, ma.v3._m);

	BrdcstVal._m = _mm_add_ps(A._m, B._m);
	A._m = _mm_add_ps(C._m, D._m);
	T1._m = _mm_add_ps(BrdcstVal._m, A._m);
	
	//second row
	BrdcstVal._m = _mm_set_ps1(this->v1.x);
	A._m = _mm_mul_ps(BrdcstVal._m, ma.v0._m);

	BrdcstVal._m = _mm_set_ps1(this->v1.y);
	B._m = _mm_mul_ps(BrdcstVal._m, ma.v1._m);

	BrdcstVal._m = _mm_set_ps1(this->v1.z);
	C._m = _mm_mul_ps(BrdcstVal._m, ma.v2._m);

	BrdcstVal._m = _mm_set_ps1(this->v1.w);
	D._m = _mm_mul_ps(BrdcstVal._m, ma.v3._m);

	BrdcstVal._m = _mm_add_ps(A._m, B._m);
	A._m = _mm_add_ps(C._m, D._m);
	T2._m = _mm_add_ps(BrdcstVal._m, A._m);
	
	//third row
	BrdcstVal._m = _mm_set_ps1(this->v2.x);
	A._m = _mm_mul_ps(BrdcstVal._m, ma.v0._m);

	BrdcstVal._m = _mm_set_ps1(this->v2.y);
	B._m = _mm_mul_ps(BrdcstVal._m, ma.v1._m);

	BrdcstVal._m = _mm_set_ps1(this->v2.z);
	C._m = _mm_mul_ps(BrdcstVal._m, ma.v2._m);

	BrdcstVal._m = _mm_set_ps1(this->v2.w);
	D._m = _mm_mul_ps(BrdcstVal._m, ma.v3._m);

	BrdcstVal._m = _mm_add_ps(A._m, B._m);
	A._m = _mm_add_ps(C._m, D._m);
	T3._m = _mm_add_ps(BrdcstVal._m, A._m);

	//fourth row
	BrdcstVal._m = _mm_set_ps1(this->v3.x);
	A._m = _mm_mul_ps(BrdcstVal._m, ma.v0._m);

	BrdcstVal._m = _mm_set_ps1(this->v3.y);
	B._m = _mm_mul_ps(BrdcstVal._m, ma.v1._m);

	BrdcstVal._m = _mm_set_ps1(this->v3.z);
	C._m = _mm_mul_ps(BrdcstVal._m, ma.v2._m);

	BrdcstVal._m = _mm_set_ps1(this->v3.w);
	D._m = _mm_mul_ps(BrdcstVal._m, ma.v3._m);

	BrdcstVal._m = _mm_add_ps(A._m, B._m);
	A._m = _mm_add_ps(C._m, D._m);
	T4._m = _mm_add_ps(BrdcstVal._m, A._m);

	return Matrix(T1, T2, T3, T4);
}

Matrix& Matrix::operator*=(const Matrix& ma)
{ 
	Vect4D A, B, C, D, BrdcstVal;

	//create temps
	BrdcstVal._m = _mm_set_ps1(this->v0.x);
	A._m = _mm_mul_ps(BrdcstVal._m, ma.v0._m);

	BrdcstVal._m = _mm_set_ps1(this->v0.y);
	B._m = _mm_mul_ps(BrdcstVal._m, ma.v1._m);

	BrdcstVal._m = _mm_set_ps1(this->v0.z);
	C._m = _mm_mul_ps(BrdcstVal._m, ma.v2._m);

	BrdcstVal._m = _mm_set_ps1(this->v0.w);
	D._m = _mm_mul_ps(BrdcstVal._m, ma.v3._m);

	BrdcstVal._m = _mm_add_ps(A._m, B._m);
	A._m = _mm_add_ps(C._m, D._m);
	this->v0._m = _mm_add_ps(BrdcstVal._m, A._m);
	
	//second row
	BrdcstVal._m = _mm_set_ps1(this->v1.x);
	A._m = _mm_mul_ps(BrdcstVal._m, ma.v0._m);

	BrdcstVal._m = _mm_set_ps1(this->v1.y);
	B._m = _mm_mul_ps(BrdcstVal._m, ma.v1._m);

	BrdcstVal._m = _mm_set_ps1(this->v1.z);
	C._m = _mm_mul_ps(BrdcstVal._m, ma.v2._m);

	BrdcstVal._m = _mm_set_ps1(this->v1.w);
	D._m = _mm_mul_ps(BrdcstVal._m, ma.v3._m);

	BrdcstVal._m = _mm_add_ps(A._m, B._m);
	A._m = _mm_add_ps(C._m, D._m);
	this->v1._m = _mm_add_ps(BrdcstVal._m, A._m);
	
	//third row
	BrdcstVal._m = _mm_set_ps1(this->v2.x);
	A._m = _mm_mul_ps(BrdcstVal._m, ma.v0._m);

	BrdcstVal._m = _mm_set_ps1(this->v2.y);
	B._m = _mm_mul_ps(BrdcstVal._m, ma.v1._m);

	BrdcstVal._m = _mm_set_ps1(this->v2.z);
	C._m = _mm_mul_ps(BrdcstVal._m, ma.v2._m);

	BrdcstVal._m = _mm_set_ps1(this->v2.w);
	D._m = _mm_mul_ps(BrdcstVal._m, ma.v3._m);

	BrdcstVal._m = _mm_add_ps(A._m, B._m);
	A._m = _mm_add_ps(C._m, D._m);
	this->v2._m = _mm_add_ps(BrdcstVal._m, A._m);

	//fourth row
	BrdcstVal._m = _mm_set_ps1(this->v3.x);
	A._m = _mm_mul_ps(BrdcstVal._m, ma.v0._m);

	BrdcstVal._m = _mm_set_ps1(this->v3.y);
	B._m = _mm_mul_ps(BrdcstVal._m, ma.v1._m);

	BrdcstVal._m = _mm_set_ps1(this->v3.z);
	C._m = _mm_mul_ps(BrdcstVal._m, ma.v2._m);

	BrdcstVal._m = _mm_set_ps1(this->v3.w);
	D._m = _mm_mul_ps(BrdcstVal._m, ma.v3._m);

	BrdcstVal._m = _mm_add_ps(A._m, B._m);
	A._m = _mm_add_ps(C._m, D._m);
	this->v3._m = _mm_add_ps(BrdcstVal._m, A._m);

	return *this;
}

Matrix& Matrix::operator/=(const float rhs)
{ 
	// divide each element by a value
	// using inverse multiply 

	__m128 div = _mm_set_ps1(1.0f / rhs);
	this->v0._m = _mm_mul_ps(v0._m, div);
	this->v1._m = _mm_mul_ps(v1._m, div);
	this->v2._m = _mm_mul_ps(v2._m, div);
	this->v3._m = _mm_mul_ps(v3._m, div);

	return *this;
}

float Matrix::Determinant() const
{
	/***** No need to optimize, gets called once outside of main timing loop ******/

	float ta = (m10 * m15) - (m11 * m14);
	// tb = (kq - mo)
	float tb = (m9 * m15) - (m11 * m13);
	// tc = (kp - lo)
	float tc = (m9 * m14) - (m10 * m13);
	// td = (jq - mn)
	float td = (m8 * m15) - (m11 * m12);
	// te = (jo - kn)
	float te = (m8 * m13) - (m9 * m12);
	// tf = (jp - ln)
	float tf = (m8 * m14) - (m10 * m12);

	return   ((m0 * ((m5 * ta) - (m6 * tb) + (m7 * tc)))
		- (m1 * ((m4 * ta) - (m6 * td) + (m7 * tf)))
		+ (m2 * ((m4 * tb) - (m5 * td) + (m7 * te)))
		- (m3 * ((m4 * tc) - (m5 * tf) + (m6 * te))));
}

Matrix Matrix::GetAdjugate() const
{
	/***** No need to optimize, gets called once outside of main timing loop ******/
	Matrix tmp;
	
	// load		ABC		(3)		ABC--
	float t1 = (m10*m15) - (m11*m14);
	float t2 = (m9*m15) - (m11*m13);
	float t3 = (m9*m14) - (m10*m13);
	
	// a = f(ta) - g(tb) + h(tc)
	tmp.m0 = (m5*t1) - (m6*t2) + (m7*t3);
	// b = -( b(ta) - c(tb) + d(tc))
	tmp.m1 = -((m1*t1) - (m2*t2) + (m3*t3));
	
	// load		JK		(5)		ABCJK
	float t4 = (m8*m15) - (m11*m12);
	float t5 = (m8*m14) - (m10*m12);
	// e = - ( e(ta) - g(tj) + h(tk))
	tmp.m4 = -( (m4*t1) - (m6*t4) + (m7*t5));
	// f = a(ta) - c(tj) + d(tk)
	tmp.m5 = (m0*t1) - (m2*t4) + (m3*t5);
	
	// unload	AJ		(3)		-BC-K
	// load		P		(4)		PBC-K
	t1 = (m8*m13) - (m9*m12);
	// n = -( e(tc) - f(tk) + g(tp))
	tmp.m12 = -((m4*t3) - (m5*t5) + (m6*t1));
	// o = a(tc) - b(tk) + c(tp)
	tmp.m13 = (m0*t3) - (m1*t5) + (m2*t1);
	
	// unload	KC		(2)		PB---
	// load		J		(3)		PBJ--
	t3 = (m8*m15) - (m11*m12);
	
	// j = e(tb) - f(tj) + h(tp)
	tmp.m8 = (m4*t2) - (m5*t3) + (m7*t1);
	// k = - ( a(tb) - b(tj) + d(tp))
	tmp.m9 = -((m0*t2) - (m1*t3) + (m3*t1));
	
	// unload	BPJ		(0)		-----
	// load		DLM		(3)		DLM--
	t1 = (m6*m15) - (m7*m14);
	t2 = (m4*m15) - (m7*m12);
	t3 = (m4*m14) - (m6*m12);
	
	// g = - ( a(td) - c(tl) + d(tm))
	tmp.m6 = -((m0*t1) - (m2*t2) + (m3*t3));
	
	// load		FR		(5)		DLMFR
	t4 = (m5*m14) - (m6*m13);
	t5 = (m4*m13) - (m5*m12);
	
	// p = - ( a(tf) - b(tm) + c(tr))
	tmp.m14 = -( (m0*t4) - (m1*t3) + (m3*t5));
	
	// unload	M		(4)		DL-FR
	// load		E		(5)		DLEFR
	t3 = (m5*m15) - (m7*m13);
	
	// l = a(te) - b(tl) + d(tr)
	tmp.m10 = (m0*t3) - (m1*t2) + (m3*t5);
	
	// unload	LR		(3)		D-EF-
	// c = b(td) - c(te) + d(tf)
	tmp.m2 = (m1*t1) - (m2*t3) + (m3*t4);
	
	// unload	DEF		(0)		-----
	// load		GHI		(3)		GHI--
	t1 = (m6*m11) - (m7*m10);
	t2 = (m5*m11) - (m7*m9);
	t3 = (m5*m10) - (m6*m9);
	
	// d = -( b(tg) - c(th) + d(ti) )
	tmp.m3 = -( (m1*t1) - (m2*t2) + (m3*t3));
	
	// load		NO		(5)		GHINO
	t4 = (m4*m11) - (m7*m8);
	t5 = (m4*m10) - (m6*m8);
	
	// h = a(tg) - c(tn) + d(to)
	tmp.m7 = (m0*t1) - (m2*t4) + (m3*t5);
	
	// unload	G		(4)		-HINO
	// load		Q		(5)		QHINO
	t1 = (m4*m9) - (m5*m8);
	
	// m = -( a(th) - b(tn) + d(tq))
	tmp.m11 = -((m0*t2) - (m1*t4) + (m3*t1));
	
	// unload	HN		(3)		Q-I-O
	// q = a(ti) - b(to) + c(tq)
	tmp.m15 = (m0*t3) - (m1*t5) + (m2*t1);
	
	return tmp;
}

void Matrix::Inverse( Matrix &out ) const
{
	/***** No need to optimize, gets called once outside of main timing loop ******/
	float det = Determinant();
	if(fabs(det) < 0.0001f)
	{
		// do nothing, Matrix is not invertable
	}
	else
	{
		out = GetAdjugate();
		out /= det;
	}
}

void Matrix::setTransMatrix(const Vect4D &t)
{ 
	this->m0 = 1.0f;
	this->m1 = 0.0f;
	this->m2 = 0.0f;
	this->m3 = 0.0f;

	this->m4 = 0.0f;
	this->m5 = 1.0f;
	this->m6 = 0.0f;
	this->m7 = 0.0f;

	this->m8 = 0.0f;
	this->m9 = 0.0f;
	this->m10 = 1.0f;
	this->m11 = 0.0f;
	
	this->m12 = t.x;
	this->m13 = t.y;
	this->m14 = t.z;
	this->m15 = 1.0f;
}

// --- End of File ---
