/*****************************************************************//**
 * \file   RectangleF.h
 * \brief  Define basic RectangleF structs.
 * 
 * \author Ronen
 * \date   May 2020
 *********************************************************************/
#pragma once
#include <cmath>
#include "../dllimport.h"
#include "Point.h"


namespace bon
{
	namespace framework
	{
		/**
		 * _Point_ class.
		 * Note: generated via python script to avoid template related / dllexport issues.
		 */
		struct RectangleF
		{
			/**
			 * RectangleF X component.
			 */
			float X;

			/**
			 * RectangleF Y component.
			 */
			float Y;

			/**
			 * RectangleF Width component.
			 */
			float Width;

			/**
			 * RectangleF Height component.
			 */
			float Height;

			/**
			 * Create the RectangleF as 0,0,0,0.
			 */
			RectangleF() : X(0), Y(0), Width(0), Height(0) {}

			/**
			 * Create the RectangleF.
			 * 
			 * \param x RectangleF left.
			 * \param y RectangleF top.
			 * \param width RectangleF width.
			 * \param height RectangleF height.
			 */
			RectangleF(float x, float y, float width, float height) : X(x), Y(y), Width(width), Height(height) {}

			/**
			 * Get RectangleF left value.
			 * 
			 * \return RectangleF left value.
			 */
			inline float Left() const { return X; }

			/**
			 * Get RectangleF right value.
			 *
			 * \return RectangleF right value.
			 */
			inline float Right() const { return X + Width; }

			/**
			 * Get RectangleF top value.
			 *
			 * \return RectangleF top value.
			 */
			inline float Top() const { return Y; }

			/**
			 * Get RectangleF bottom value.
			 *
			 * \return RectangleF bottom value.
			 */
			inline float Bottom() const { return Y + Height; }

			/**
			 * Set RectangleF values.
			 */
			inline void Set(float x, float y, float w, float h)
			{
				X = x;
				Y = y;
				Width = w;
				Height = h;
			}

			/**
			 * Reset RectangleF to 0,0,0,0.
			 */
			inline void Set()
			{
				X = 0;
				Y = 0;
				Width = 0;
				Height = 0;
			}

			/**
			 * Check if containing a point.
			 * 
			 * \param point Point to test.
			 * \return True if containing the point.
			 */
			inline bool Contains(const PointI& point)
			{
				return point.X >= Left() && point.X <= Right() && point.Y >= Top() && point.Y <= Bottom();
			}

			/**
			 * Check if containing a point.
			 *
			 * \param point Point to test.
			 * \return True if containing the point.
			 */
			inline bool Contains(const PointF& point)
			{
				return point.X >= Left() && point.X <= Right() && point.Y >= Top() && point.Y <= Bottom();
			}

			/**
			 * Check if containing a RectangleF.
			 *
			 * \param RectangleF RectangleF to test.
			 * \return True if containing the RectangleF.
			 */
			inline bool Contains(const RectangleF other)
			{
				return other.Left() >= Left() && other.Right() <= Right() && other.Top() >= Top() && other.Bottom() <= Bottom();
			}

			/**
			 * Check if intersects or containing a RectangleF.
			 *
			 * \param RectangleF RectangleF to test.
			 * \return True if intersects with or containing the RectangleF.
			 */
			inline bool Overlaps(const RectangleF other)
			{
				// if one RectangleF is on left side of other 
				if (Left() > other.Right() || other.Left() > Right())
					return false;

				// if one RectangleF is above other 
				if (Top() > other.Bottom() || other.Top() > Bottom())
					return false;

				// RectangleFs overlaps
				return true;
			}

			/**
			 * Implement equality operator.
			 *
			 * \param other RectangleF to compare to.
			 * \return If RectangleFs are the same.
			 */
			bool operator==(const RectangleF& other) const
			{
				return X == other.X && Y == other.Y && Width == other.Width && Height == other.Height;
			}

			/**
			 * Implement inequality operator.
			 *
			 * \param other RectangleF to compare to.
			 * \return If RectangleFs are not the same.
			 */
			bool operator!=(const RectangleF& other) const {
				return !(*this == other);
			}

			/**
			 * Get if this RectangleF is empty.
			 * 
			 * \return True if RectangleF is empty (either width or height equals 0 is enough).
			 */
			bool Empty() const 
			{
				return (Width == 0) || (Height == 0);
			}

			/**
			 * Get RectangleF with 0,0,0,0 values.
			 * 
			 * \return RectangleF(0, 0, 0, 0).
			 */
			static const RectangleF & Zero()
			{
				static RectangleF zero(0, 0, 0, 0);
				return zero;
			}
		};
	}
}