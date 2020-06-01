/*****************************************************************//**
 * \file   _Rectangle_.h
 * \brief  Define basic _Rectangle_ structs.
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
		struct _Rectangle_
		{
			/**
			 * _Rectangle_ X component.
			 */
			__T__ X;

			/**
			 * _Rectangle_ Y component.
			 */
			__T__ Y;

			/**
			 * _Rectangle_ Width component.
			 */
			__T__ Width;

			/**
			 * _Rectangle_ Height component.
			 */
			__T__ Height;

			/**
			 * Create the _Rectangle_ as 0,0,0,0.
			 */
			_Rectangle_() : X(0), Y(0), Width(0), Height(0) {}

			/**
			 * Create the _Rectangle_.
			 * 
			 * \param x _Rectangle_ left.
			 * \param y _Rectangle_ top.
			 * \param width _Rectangle_ width.
			 * \param height _Rectangle_ height.
			 */
			_Rectangle_(__T__ x, __T__ y, __T__ width, __T__ height) : X(x), Y(y), Width(width), Height(height) {}

			/**
			 * Get _Rectangle_ left value.
			 * 
			 * \return _Rectangle_ left value.
			 */
			inline __T__ Left() const { return X; }

			/**
			 * Get _Rectangle_ right value.
			 *
			 * \return _Rectangle_ right value.
			 */
			inline __T__ Right() const { return X + Width; }

			/**
			 * Get _Rectangle_ top value.
			 *
			 * \return _Rectangle_ top value.
			 */
			inline __T__ Top() const { return Y; }

			/**
			 * Get _Rectangle_ bottom value.
			 *
			 * \return _Rectangle_ bottom value.
			 */
			inline __T__ Bottom() const { return Y + Height; }

			/**
			 * Set _Rectangle_ values.
			 */
			inline void Set(__T__ x, __T__ y, __T__ w, __T__ h)
			{
				X = x;
				Y = y;
				Width = w;
				Height = h;
			}

			/**
			 * Reset _Rectangle_ to 0,0,0,0.
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
			 * Check if containing a _Rectangle_.
			 *
			 * \param _Rectangle_ _Rectangle_ to test.
			 * \return True if containing the _Rectangle_.
			 */
			inline bool Contains(const _Rectangle_ other)
			{
				return other.Left() >= Left() && other.Right() <= Right() && other.Top() >= Top() && other.Bottom() <= Bottom();
			}

			/**
			 * Check if intersects or containing a _Rectangle_.
			 *
			 * \param _Rectangle_ _Rectangle_ to test.
			 * \return True if intersects with or containing the _Rectangle_.
			 */
			inline bool Overlaps(const _Rectangle_ other)
			{
				// if one _Rectangle_ is on left side of other 
				if (Left() > other.Right() || other.Left() > Right())
					return false;

				// if one _Rectangle_ is above other 
				if (Top() > other.Bottom() || other.Top() > Bottom())
					return false;

				// _Rectangle_s overlaps
				return true;
			}

			/**
			 * Implement equality operator.
			 *
			 * \param other _Rectangle_ to compare to.
			 * \return If _Rectangle_s are the same.
			 */
			bool operator==(const _Rectangle_& other) const
			{
				return X == other.X && Y == other.Y && Width == other.Width && Height == other.Height;
			}

			/**
			 * Implement inequality operator.
			 *
			 * \param other _Rectangle_ to compare to.
			 * \return If _Rectangle_s are not the same.
			 */
			bool operator!=(const _Rectangle_& other) const {
				return !(*this == other);
			}

			/**
			 * Get if this _Rectangle_ is empty.
			 * 
			 * \return True if _Rectangle_ is empty (either width or height equals 0 is enough).
			 */
			bool Empty() const 
			{
				return (Width == 0) || (Height == 0);
			}

			/**
			 * Get _Rectangle_ with 0,0,0,0 values.
			 * 
			 * \return _Rectangle_(0, 0, 0, 0).
			 */
			static const _Rectangle_ & Zero()
			{
				static _Rectangle_ zero(0, 0, 0, 0);
				return zero;
			}
		};
	}
}