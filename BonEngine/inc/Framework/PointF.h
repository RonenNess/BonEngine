/*****************************************************************//**
 * \file   PointF.h
 * \brief  Define basic PointF structs.
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
		struct PointI;

		/**
		 * PointF class.
		 */
		struct BON_DLLEXPORT PointF
		{
		public:
			/**
			 * PointF X component.
			 */
			float X;

			/**
			 * PointF Y component.
			 */
			float Y;

			/**
			 * Create the PointF as 0,0.
			 */
			PointF() : X(0), Y(0) {}

			/**
			 * Create the PointF.
			 * 
			 * \param x PointF X value.
			 * \param y PointF Y value.
			 */
			PointF (float x, float y) : X(x), Y(y) {}

			/**
			 * Set PointF values.
			 * 
			 * \param x X value to set.
			 * \param y Y value to set.
			 */
			void Set(float x, float y)
			{
				X = x;
				Y = y;
			}

			/**
			 * Copy values from another point.
			 * 
			 * \param other Point to copy values from.
			 */
			void Copy(const PointF& other)
			{
				Set(other.X, other.Y);
			}

			/**
			 * Reset PointF values to 0,0.
			 */
			void Reset()
			{
				X = Y = (float)0;
			}

			/**
			 * Return if this PointF is 0,0.
			 * 
			 * \return True if PointF is 0,0.
			 */
			inline bool IsZero() const 
			{
				return X == 0 && Y == 0;
			}

			/**
			 * Implement equality operator.
			 *
			 * \param other PointF to compare to.
			 * \return If PointFs are the same.
			 */
			bool operator==(const PointF& other) const
			{
				return X == other.X && Y == other.Y;
			}

			/**
			 * Implement inequality operator.
			 *
			 * \param other PointF to compare to.
			 * \return If PointFs are not the same.
			 */
			bool operator!=(const PointF& other) const {
				return !(*this == other);
			}

			/**
			 * Set X and Y to be within range.
			 * 
			 * \param min Min value.
			 * \param max Max value.
			 */
			void Clamp(float min, float max)
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
			void Clamp(float minX, float maxX, float minY, float maxY)
			{
				if (X < minX) X = minX;
				if (X > maxX) X = maxX;
				if (Y < minY) Y = minY;
				if (Y > maxY) Y = maxY;
			}

			// operators with another PointF
			inline PointF& operator+=(const PointF& other) { X+= other.X; Y += other.Y; return *this; }
			inline PointF& operator-=(const PointF& other) { X-= other.X; Y -= other.Y; return *this; }
			inline PointF& operator*=(const PointF& other) { X*= other.X; Y *= other.Y; return *this; }
			inline PointF& operator/=(const PointF& other) { X/= other.X; Y /= other.Y; return *this; }
			inline PointF& operator%=(const PointF& other) { X= (float)((int)X% (int)other.X); Y = (float)((int)Y % (int)other.Y); return *this; }
			inline PointF operator*(const PointF& other) const { return PointF(X* other.X, Y * other.Y); }
			inline PointF operator/(const PointF& other) const { return PointF(X/ other.X, Y / other.Y); }
			inline PointF operator+(const PointF& other) const { return PointF(X+ other.X, Y + other.Y); }
			inline PointF operator-(const PointF& other) const { return PointF(X- other.X, Y - other.Y); }
			inline PointF operator%(const PointF& other) const { return PointF((float)((int)X% (int)other.X), (float)((int)Y % (int)other.Y)); }

			// operators with scalars
			inline PointF operator-() const { return PointF(-X, -Y); }
			inline PointF& operator+=(const float& scalar) { X+= scalar; Y += scalar; return *this; }
			inline PointF& operator-=(const float& scalar) { X-= scalar; Y -= scalar; return *this; }
			inline PointF& operator*=(const float& scalar) { X*= scalar; Y *= scalar; return *this; }
			inline PointF& operator/=(const float& scalar) { X/= scalar; Y /= scalar; return *this; }
			inline PointF& operator%=(const float& scalar) { X= (float)((int)X% (int)scalar); Y = (float)((int)Y % (int)scalar); return *this; }
			inline PointF operator*(const float& scalar) const { return PointF(X* scalar, Y * scalar); }
			inline PointF operator/(const float& scalar) const { return PointF(X/ scalar, Y / scalar); }
			inline PointF operator+(const float& scalar) const { return PointF(X+ scalar, Y + scalar); }
			inline PointF operator-(const float& scalar) const { return PointF(X- scalar, Y - scalar); }
			inline PointF operator%(const float& scalar) const { return PointF((float)((int)X% (int)scalar), (float)((int)Y % (int)scalar)); }

			// casting between point types
			operator PointI();
			operator PointI() const;

			/**
			 * PointF with 0,0 values.
			 */
			static const PointF& Zero;

			/**
			 * PointF with 1,1 values.
			 */
			static const PointF& One;

			/**
			 * PointF with 0.5,0.5 values.
			 */
			static const PointF& Half;

			/**
			 * Lerp between two points.
			 *
			 * \param a From point.
			 * \param b To point.
			 * \param delta Lerp factor.
			 * \return Lerped point between the two given points.
			 */
			static PointF Lerp(const PointF& a, const PointF& b, float delta)
			{
				return PointF((a.X * (1 - delta) + b.X * delta), (a.Y * (1 - delta) + b.Y * delta));
			}

			/**
			 * Get distance to another PointF.
			 * 
			 * \param other PointF to get distance to.
			 * \return 
			 */
			float DistanceTo(const PointF& other)
			{
				return (float)sqrt(pow(X - other.X, 2) + pow(Y - other.Y, 2));
			}
		};
	}
}