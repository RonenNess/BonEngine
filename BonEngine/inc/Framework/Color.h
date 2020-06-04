/*****************************************************************//**
 * \file   Color.h
 * \brief  Define basic color struct.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include <cstdlib>
#include "../dllimport.h"

namespace bon
{
	namespace framework
	{
		/**
		 * Color class.
		 */
		struct BON_DLLEXPORT Color
		{
			/**
			 * Color red component.
			 */
			float R;

			/**
			 * Color green component.
			 */
			float G;

			/**
			 * Color blue component.
			 */
			float B;

			/**
			 * Color alpha component.
			 */
			float A;

			/**
			 * Create the color.
			 *
			 * \param r Color red component.
			 * \param g Color green component.
			 * \param b Color blue component.
			 * \param a Color alpha component.
			 */
			Color() : R(1), G(1), B(1), A(1)
			{
			}

			/**
			 * Create the color.
			 *
			 * \param r Color red component.
			 * \param g Color green component.
			 * \param b Color blue component.
			 * \param a Color alpha component.
			 */
			Color(float r, float g, float b, float a = 1) : R(r), G(g), B(b), A(a)
			{
			}

			/**
			 * Implement equality operator.
			 * 
			 * \param other Color to compare to.
			 * \return If colors are the same.
			 */
			bool operator==(const Color& other) const 
			{
				return R == other.R && G == other.G && B == other.B && A == other.A;
			}

			/**
			 * Implement inequality operator.
			 * 
			 * \param other Color to compare to.
			 * \return If colors are not the same.
			 */
			bool operator!=(const Color& other) const {
				return !(*this == other);
			}

			/**
			 * Get red component as byte.
			 */
			inline unsigned char RB() const { return (unsigned char)(R * 255.0); }

			/**
			 * Get green component as byte.
			 */
			inline unsigned char GB() const { return (unsigned char)(G * 255.0); }

			/**
			 * Get blue component as byte.
			 */
			inline unsigned char BB() const { return (unsigned char)(B * 255.0); }

			/**
			 * Get alpha component as byte.
			 */
			inline unsigned char AB() const { return (unsigned char)(A * 255.0); }

			/**
			 * Black color.
			 */
			static const Color& Black;

			/**
			 * Transparent color.
			 */
			static const Color& Transparent;
			
			/**
			 * Half transparent color.
			 */
			static const Color& HalfTransparent;

			/**
			 * Transparent black color.
			 */
			static const Color& TransparentBlack;

			/**
			 * White color.
			 */
			static const Color& White;

			/**
			 * Gray color.
			 */
			static const Color& Gray;

			/**
			 * Red color.
			 */
			static const Color& Red;

			/**
			 * Green color.
			 */
			static const Color& Green;

			/**
			 * Blue color.
			 */
			static const Color& Blue;

			/**
			 * Yellow color.
			 */
			static const Color& Yellow;

			/**
			 * Purple color.
			 */
			static const Color& Purple;

			/**
			 * Teal color.
			 */
			static const Color& Teal;
			
			/**
			 * Return a random color
			 *
			 * \return Random color.
			 */
			static Color Random()
			{
				return FromBytes(rand() % 255, rand() % 255, rand() % 255, 255);
			}

			/**
			 * Get color instance from byte values.
			 */
			static Color FromBytes(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
			{
				return Color((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f);
			}
		};
	}
}