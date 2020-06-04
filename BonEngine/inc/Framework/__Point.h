/*****************************************************************//**
 * \file   _Point_.h
 * \brief  Define basic _Point_ structs.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include <cmath>
#include "../dllimport.h"


namespace bon
{
	namespace framework
	{
		// forward declare
		struct other__Point_;

		/**
		 * _Point_ class.
		 * Note: generated via python script to avoid template related / dllexport issues.
		 */
		struct BON_DLLEXPORT _Point_
		{
		public:
			/**
			 * _Point_ X component.
			 */
			__T__ X;

			/**
			 * _Point_ Y component.
			 */
			__T__ Y;

			/**
			 * Create the _Point_ as 0,0.
			 */
			_Point_() : X(0), Y(0) {}

			/**
			 * Create the _Point_.
			 * 
			 * \param x _Point_ X value.
			 * \param y _Point_ Y value.
			 */
			_Point_ (__T__ x, __T__ y) : X(x), Y(y) {}

			/**
			 * Set _Point_ values.
			 * 
			 * \param x X value to set.
			 * \param y Y value to set.
			 */
			void Set(__T__ x, __T__ y)
			{
				X = x;
				Y = y;
			}

			/**
			 * Copy values from another point.
			 * 
			 * \param other Point to copy values from.
			 */
			void Copy(const _Point_& other)
			{
				Set(other.X, other.Y);
			}

			/**
			 * Reset _Point_ values to 0,0.
			 */
			void Reset()
			{
				X = Y = (__T__)0;
			}

			/**
			 * Return if this _Point_ is 0,0.
			 * 
			 * \return True if _Point_ is 0,0.
			 */
			inline bool IsZero() const 
			{
				return X == 0 && Y == 0;
			}

			/**
			 * Implement equality operator.
			 *
			 * \param other _Point_ to compare to.
			 * \return If _Point_s are the same.
			 */
			bool operator==(const _Point_& other) const
			{
				return X == other.X && Y == other.Y;
			}

			/**
			 * Implement inequality operator.
			 *
			 * \param other _Point_ to compare to.
			 * \return If _Point_s are not the same.
			 */
			bool operator!=(const _Point_& other) const {
				return !(*this == other);
			}

			/**
			 * Set X and Y to be within range.
			 * 
			 * \param min Min value.
			 * \param max Max value.
			 */
			void Clamp(__T__ min, __T__ max)
			{
				if (X < min) X = min;
				if (X > max) X = max;
				if (Y < min) Y = min;
				if (Y > max) Y = max;
			}

			/**
			 * Set X and Y to be within range.
			 *
			 * \param minX Min value for X.
			 * \param maxX Max value for X.
			 * \param minY Min value for Y.
			 * \param maxY Max value for Y.
			 */
			void Clamp(__T__ minX, __T__ maxX, __T__ minY, __T__ maxY)
			{
				if (X < minX) X = minX;
				if (X > maxX) X = maxX;
				if (Y < minY) Y = minY;
				if (Y > maxY) Y = maxY;
			}

			// operators with another _Point_
			inline _Point_& operator+=(const _Point_& other) { X+= other.X; Y += other.Y; return *this; }
			inline _Point_& operator-=(const _Point_& other) { X-= other.X; Y -= other.Y; return *this; }
			inline _Point_& operator*=(const _Point_& other) { X*= other.X; Y *= other.Y; return *this; }
			inline _Point_& operator/=(const _Point_& other) { X/= other.X; Y /= other.Y; return *this; }
			inline _Point_& operator%=(const _Point_& other) { X= (__T__)((int)X% (int)other.X); Y = (__T__)((int)Y % (int)other.Y); return *this; }
			inline _Point_ operator*(const _Point_& other) const { return _Point_(X* other.X, Y * other.Y); }
			inline _Point_ operator/(const _Point_& other) const { return _Point_(X/ other.X, Y / other.Y); }
			inline _Point_ operator+(const _Point_& other) const { return _Point_(X+ other.X, Y + other.Y); }
			inline _Point_ operator-(const _Point_& other) const { return _Point_(X- other.X, Y - other.Y); }
			inline _Point_ operator%(const _Point_& other) const { return _Point_((__T__)((int)X% (int)other.X), (__T__)((int)Y % (int)other.Y)); }

			// operators with scalars
			inline _Point_ operator-() const { return _Point_(-X, -Y); }
			inline _Point_& operator+=(const __T__& scalar) { X+= scalar; Y += scalar; return *this; }
			inline _Point_& operator-=(const __T__& scalar) { X-= scalar; Y -= scalar; return *this; }
			inline _Point_& operator*=(const __T__& scalar) { X*= scalar; Y *= scalar; return *this; }
			inline _Point_& operator/=(const __T__& scalar) { X/= scalar; Y /= scalar; return *this; }
			inline _Point_& operator%=(const __T__& scalar) { X= (__T__)((int)X% (int)scalar); Y = (__T__)((int)Y % (int)scalar); return *this; }
			inline _Point_ operator*(const __T__& scalar) const { return _Point_(X* scalar, Y * scalar); }
			inline _Point_ operator/(const __T__& scalar) const { return _Point_(X/ scalar, Y / scalar); }
			inline _Point_ operator+(const __T__& scalar) const { return _Point_(X+ scalar, Y + scalar); }
			inline _Point_ operator-(const __T__& scalar) const { return _Point_(X- scalar, Y - scalar); }
			inline _Point_ operator%(const __T__& scalar) const { return _Point_((__T__)((int)X% (int)scalar), (__T__)((int)Y % (int)scalar)); }

			// casting between point types
			operator other__Point_();
			operator other__Point_() const;

			/**
			 * _Point_ with 0,0 values.
			 */
			static const _Point_& Zero;

			/**
			 * _Point_ with 1,1 values.
			 */
			static const _Point_& One;

			/**
			 * _Point_ with 0.5,0.5 values.
			 */
			static const _Point_& Half;

			/**
			 * Get distance to another _Point_.
			 * 
			 * \param other _Point_ to get distance to.
			 * \return 
			 */
			float DistanceTo(const _Point_& other)
			{
				return (float)sqrt(pow(X - other.X, 2) + pow(Y - other.Y, 2));
			}
		};
	}
}