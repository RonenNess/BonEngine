/*****************************************************************//**
 * \file   Color.h
 * \brief  Define basic color struct.
 * 
 * \author Ronen
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"

namespace bon
{
	namespace framework
	{
		/**
		 * Color class.
		 */
		struct DLLEXPORT Color
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
			 * Return black color.
			 *
			 * \return Color(0,0,0,1).
			 */
			static const Color& Black()
			{
				static Color black(0, 0, 0, 1);
				return black;
			}

			/**
			 * Return transparent color.
			 *
			 * \return Color(0,0,0,0).
			 */
			static const Color& Transparent()
			{
				static Color transparent(0, 0, 0, 0);
				return transparent;
			}

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
			 * Return white color.
			 *
			 * \return Color(1,1,1,1).
			 */
			static const Color& White()
			{
				static Color white(1, 1, 1, 1);
				return white;
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