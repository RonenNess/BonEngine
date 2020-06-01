/*****************************************************************//**
 * \file   RectangleI.h
 * \brief  Define basic RectangleI structs.
 * 
 * \author Ronen Ness
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
		struct RectangleI
		{
			/**
			 * RectangleI X component.
			 */
			int X;

			/**
			 * RectangleI Y component.
			 */
			int Y;

			/**
			 * RectangleI Width component.
			 */
			int Width;

			/**
			 * RectangleI Height component.
			 */
			int Height;

			/**
			 * Create the RectangleI as 0,0,0,0.
			 */
			RectangleI() : X(0), Y(0), Width(0), Height(0) {}

			/**
			 * Create the RectangleI.
			 * 
			 * \param x RectangleI left.
			 * \param y RectangleI top.
			 * \param width RectangleI width.
			 * \param height RectangleI height.
			 */
			RectangleI(int x, int y, int width, int height) : X(x), Y(y), Width(width), Height(height) {}

			/**
			 * Get RectangleI left value.
			 * 
			 * \return RectangleI left value.
			 */
			inline int Left() const { return X; }

			/**
			 * Get RectangleI right value.
			 *
			 * \return RectangleI right value.
			 */
			inline int Right() const { return X + Width; }

			/**
			 * Get RectangleI top value.
			 *
			 * \return RectangleI top value.
			 */
			inline int Top() const { return Y; }

			/**
			 * Get RectangleI bottom value.
			 *
			 * \return RectangleI bottom value.
			 */
			inline int Bottom() const { return Y + Height; }

			/**
			 * Set RectangleI values.
			 */
			inline void Set(int x, int y, int w, int h)
			{
				X = x;
				Y = y;
				Width = w;
				Height = h;
			}

			/**
			 * Reset RectangleI to 0,0,0,0.
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
			 * Check if containing a RectangleI.
			 *
			 * \param RectangleI RectangleI to test.
			 * \return True if containing the RectangleI.
			 */
			inline bool Contains(const RectangleI other)
			{
				return other.Left() >= Left() && other.Right() <= Right() && other.Top() >= Top() && other.Bottom() <= Bottom();
			}

			/**
			 * Check if intersects or containing a RectangleI.
			 *
			 * \param RectangleI RectangleI to test.
			 * \return True if intersects with or containing the RectangleI.
			 */
			inline bool Overlaps(const RectangleI other)
			{
				// if one RectangleI is on left side of other 
				if (Left() > other.Right() || other.Left() > Right())
					return false;

				// if one RectangleI is above other 
				if (Top() > other.Bottom() || other.Top() > Bottom())
					return false;

				// RectangleIs overlaps
				return true;
			}

			/**
			 * Implement equality operator.
			 *
			 * \param other RectangleI to compare to.
			 * \return If RectangleIs are the same.
			 */
			bool operator==(const RectangleI& other) const
			{
				return X == other.X && Y == other.Y && Width == other.Width && Height == other.Height;
			}

			/**
			 * Implement inequality operator.
			 *
			 * \param other RectangleI to compare to.
			 * \return If RectangleIs are not the same.
			 */
			bool operator!=(const RectangleI& other) const {
				return !(*this == other);
			}

			/**
			 * Get if this RectangleI is empty.
			 * 
			 * \return True if RectangleI is empty (either width or height equals 0 is enough).
			 */
			bool Empty() const 
			{
				return (Width == 0) || (Height == 0);
			}

			/**
			 * Get RectangleI with 0,0,0,0 values.
			 * 
			 * \return RectangleI(0, 0, 0, 0).
			 */
			static const RectangleI & Zero()
			{
				static RectangleI zero(0, 0, 0, 0);
				return zero;
			}
		};
	}
}