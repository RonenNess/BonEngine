/*****************************************************************//**
 * \file   Sprite.h
 * \brief  Define a basic sprite struct to hold rendering properties.
 * 
 * \author Ronen
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "Defs.h"
#include "../Assets/Types/Image.h"
#include "../Framework/Point.h"
#include "../Framework/Rectangle.h"
#include "../Framework/Color.h"

namespace bon
{
	namespace gfx
	{

#pragma warning( push )
#pragma warning( disable : 4251 ) // needs to have dll-interface to be used by clients of class - happens due to ImageAsset but its ok there's no problem with shared_ptr

		/**
		 * A structure to hold all the properties of a rendered sprite.
		 */
		struct DLLEXPORT Sprite
		{
		public:
			// Image to draw.
			assets::ImageAsset Image;

			// Drawing position.
			framework::PointF Position;

			// Drawing size (0,0 will use source rect or image full size).
			framework::PointI Size;

			// Blend mode.
			BlendModes Blend = BlendModes::AlphaBlend;

			// Source Rect from image.
			framework::RectangleI SourceRect;

			// Drawing origin (0.0 - 1.0 relative to sprite size.
			framework::PointF Origin;

			// sprite rotation.
			float Rotation = 0.0f;

			// tint color.
			framework::Color Color;

			/**
			 * Create sprite with default arguments.
			 */
			Sprite()
			{
			}

			/**
			 * Create sprite with all arguments provided.
			 * */
			Sprite(assets::ImageAsset sourceImage,
				const framework::PointF& position,
				const framework::PointI& size = framework::PointI(0, 0),
				BlendModes blend = BlendModes::AlphaBlend,
				const framework::RectangleI& sourceRect = framework::RectangleI(0, 0, 0, 0),
				const framework::PointF& origin = framework::PointF(0, 0),
				float rotation = 0.f,
				framework::Color color = framework::Color()) :

				Image (sourceImage),
				Position (position),
				Size (size),
				Blend (blend),
				SourceRect (sourceRect),
				Origin (origin),
				Rotation (rotation),
				Color (color)
			{
			}
		};

#pragma warning( pop )
	}
}