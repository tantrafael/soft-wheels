#ifndef __SPACE_H__
#define __SPACE_H__

#include "definitions.h"


class Space
{
	public:
		Space();
		virtual ~Space();

		VECTOR I();
		VECTOR J();
		VECTOR K();

		VECTOR* pI();
		VECTOR* pJ();
		VECTOR* pK();

		void setI( VECTOR &V );
		void setJ( VECTOR &V );
		void setK( VECTOR &V );

		void rotate( VECTOR &W );
		void normalize();

	private:
		VECTOR m_I;
		VECTOR m_J;
		VECTOR m_K;

		int m_n;
};

#endif