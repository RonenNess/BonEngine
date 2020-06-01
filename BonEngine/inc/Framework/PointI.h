/*****************************************************************//**
 * \file   PointI.h
 * \brief  Define basic PointI structs.
 * 
 * \author Ronen
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
		struct PointF;

		/**
		 * PointI class.
		 * Note: generated via python script to avoid template related / dllexport issues.
		 */
		struct DLLEXPORT PointI
		{
		public:
			/**
			 * PointI X component.
			 */
			int X;

			/**
			 * PointI Y component.
			 */
			int Y;

			/**
			 * Create the PointI as 0,0.
			 */
			PointI() : X(0), Y(0) {}

			/**
			 * Create the PointI.
			 * 
			 * \param x PointI X value.
			 * \param y PointI Y value.
			 */
			PointI (int x, int y) : X(x), Y(y) {}

			/**
			 * Set PointI values.
			 * 
			 * \param x X value to set.
			 * \param y Y value to set.
			 */
			void Set(int x, int y)
			{
				X = x;
				Y = y;
			}

			/**
			 * Copy values from another point.
			 * 
			 * \param other Point to copy values from.
			 */
			void Copy(const PointI& other)
			{
				Set(other.X, other.Y);
			}

			/**
			 * Reset PointI values to 0,0.
			 */
			void Reset()
			{
				X = Y = (int)0;
			}

			/**
			 * Return if this PointI is 0,0.
			 * 
			 * \return True if PointI is 0,0.
			 */
			inline bool IsZero() const 
			{
				return X == 0 && Y == 0;
			}

			/**
			 * Implement equality operator.
			 *
			 * \param other PointI to compare to.
			 * \return If PointIs are the same.
			 */
			bool operator==(const PointI& other) const
			{
				return X == other.X && Y == other.Y;
			}

			/**
			 * Implement inequality operator.
			 *
			 * \param other PointI to compare to.
			 * \return If PointIs are not the same.
			 */
			bool operator!=(const PointI& other) const {
				return !(*this == other);
			}

			/**
			 * Set X and Y to be within range.
			 * 
			 * \param min Min value.
			 * \param max Max value.
			 */
			void Clamp(int min, int max)
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
			void Clamp(int minX, int maxX, int minY, int maxY)
			{
				if (X < minX) X = minX;
				if (X > maxX) X = maxX;
				if (Y < minY) Y = minY;
				if (Y > maxY) Y = maxY;
			}

			// operators with another PointI
			inline PointI& operator+=(const PointI& other) { X+= other.X; Y += other.Y; return *this; }
			inline PointI& operator-=(const PointI& other) { X-= other.X; Y -= other.Y; return *this; }
			inline PointI& operator*=(const PointI& other) { X*= other.X; Y *= other.Y; return *this; }
			inline PointI& operator/=(const PointI& other) { X/= other.X; Y /= other.Y; return *this; }
			inline PointI& operator%=(const PointI& other) { X= (int)((int)X% (int)other.X); Y = (int)((int)Y % (int)other.Y); return *this; }
			inline PointI operator*(const PointI& other) const { return PointI(X* other.X, Y * other.Y); }
			inline PointI operator/(const PointI& other) const { return PointI(X/ other.X, Y / other.Y); }
			inline PointI operator+(const PointI& other) const { return PointI(X+ other.X, Y + other.Y); }
			inline PointI operator-(const PointI& other) const { return PointI(X- other.X, Y - other.Y); }
			inline PointI operator%(const PointI& other) const { return PointI((int)((int)X% (int)other.X), (int)((int)Y % (int)other.Y)); }

			// operators with scalars
			inline PointI operator-() const { return PointI(-X, -Y); }
			inline PointI& operator+=(const int& scalar) { X+= scalar; Y += scalar; return *this; }
			inline PointI& operator-=(const int& scalar) { X-= scalar; Y -= scalar; return *this; }
			inline PointI& operator*=(const int& scalar) { X*= scalar; Y *= scalar; return *this; }
			inline PointI& operator/=(const int& scalar) { X/= scalar; Y /= scalar; return *this; }
			inline PointI& operator%=(const int& scalar) { X= (int)((int)X% (int)scalar); Y = (int)((int)Y % (int)scalar); return *this; }
			inline PointI operator*(const int& scalar) const { return PointI(X* scalar, Y * scalar); }
			inline PointI operator/(const int& scalar) const { return PointI(X/ scalar, Y / scalar); }
			inline PointI operator+(const int& scalar) const { return PointI(X+ scalar, Y + scalar); }
			inline PointI operator-(const int& scalar) const { return PointI(X- scalar, Y - scalar); }
			inline PointI operator%(const int& scalar) const { return PointI((int)((int)X% (int)scalar), (int)((int)Y % (int)scalar)); }

			// casting between point types
			operator PointF();
			operator PointF() const;

			/**
			 * Get PointI with 0,0 values.
			 * 
			 * \return PointI(0, 0).
			 */
			static const PointI & Zero()
			{
				static PointI zero(0, 0);
				return zero;
			}

			/**
			 * Get PointI with 1,1 values.
			 * 
			 * \return PointI(1, 1).
			 */
			static const PointI& One()
			{
				static PointI one(1, 1);
				return one;
			}

			/**
			 * Get distance to another PointI.
			 * 
			 * \param other PointI to get distance to.
			 * \return 
			 */
			float DistanceTo(const PointI& other)
			{
				return (float)sqrt(pow(X - other.X, 2) + pow(Y - other.Y, 2));
			}
		};
	}
}