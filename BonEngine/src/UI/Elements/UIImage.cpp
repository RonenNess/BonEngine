#include <UI/Elements/UIImage.h>
#include <Framework/Exceptions.h>
#include <Framework/Point.h>
#include <Framework/Color.h>
#include <Framework/Rectangle.h>
#include <BonEngine.h>
#include <Gfx/Defs.h>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// get source rect by current state
		const framework::RectangleI& _UIImage::GetCurrentStateSourceRect() const
		{
			switch (_state)
			{
			case UIElementState::Idle:
				return SourceRect;
			case UIElementState::PointedOn:
				return SourceRectHighlight;
			case UIElementState::PressedDown:
				return SourceRectPressed;
			case UIElementState::AltPressedDown:
				return SourceRectPressed;
			default:
				return SourceRect;
			}
		}

		// initialize element style from config file.
		void _UIImage::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// load basic stylesheet
			_UIElement::LoadStyleFrom(config);

			// load source image
			const char* img = config->GetStr("image", "image_path", nullptr);
			if (img) { Image = bon::_GetEngine().Assets().LoadImage(ToRelativePath(img).c_str()); }

			// load sliced sides
			RectangleF slicedSides = config->GetRectangleF("image", "sliced_sides", RectangleF::Zero);
			SlicedImageSides.FromRect(slicedSides);

			// load colors
			Color = config->GetColor("image", "color", Color::White);
			ColorHighlight = config->GetColor("image", "color_highlight", Color);
			ColorPressed = config->GetColor("image", "color_pressed", Color);

			// load source rects
			SourceRect = config->GetRectangleF("image", "source_rect", RectangleF::Zero);
			SourceRectHighlight = config->GetRectangleF("image", "source_rect_highlight", SourceRect);
			SourceRectPressed = config->GetRectangleF("image", "source_rect_pressed", SourceRect);

			// load blend modes
			static const char* blendOptions[] = { "opaque", "alpha", "additive", "mod", "multiply" };
			BlendMode = (BlendModes)config->GetOption("image", "blend", blendOptions, (int)BlendModes::AlphaBlend);
			
			// load drawing modes
			static const char* drawModeOptions[] = { "stretch", "tiled", "sliced" };
			ImageType = (UIImageTypes)config->GetOption("image", "type", drawModeOptions, (int)UIImageTypes::Stretch);

			// texture scale and slice sides
			TextureScale = config->GetFloat("image", "texture_scale", 1.0f);
		}

		// implement just the drawing of this element.
		void _UIImage::DrawSelf()
		{
			_UIElement::DrawSelf();

			// skip if no image is set
			if (Image == nullptr) { return; }

			// get color and source rect
			const bon::Color& color = GetCurrentStateColor();
			RectangleI sourceRect = GetCurrentStateSourceRect();

			// resolve source rect actual size since we need to for calculations
			if (sourceRect.Width == 0) { sourceRect.Width = Image->Width(); }
			if (sourceRect.Height == 0) { sourceRect.Height = Image->Height(); }

			// draw in plain stretched mode
			if (ImageType == UIImageTypes::Stretch)
			{
				bon::_GetEngine().Gfx().DrawImage(Image,
					PointF((float)_destRect.X, (float)_destRect.Y),
					&PointI(_destRect.Width, _destRect.Height),
					BlendMode,
					&sourceRect,
					&PointF::Zero, 0.0f, &color);
			}
			// draw in tiled mode
			else if (ImageType == UIImageTypes::Tiled)
			{
				DrawTiled(_destRect, color, sourceRect);
			}
			// draw in sliced mode
			else if (ImageType == UIImageTypes::Sliced)
			{
				// draw corners
				{
					// top left
					bon::_GetEngine().Gfx().DrawImage(Image,
						PointF((float)_destRect.X, (float)_destRect.Y),
						&PointI((int)(SlicedImageSides.Left * TextureScale), (int)(SlicedImageSides.Top * TextureScale)),
						BlendMode,
						&framework::RectangleI(sourceRect.X, sourceRect.Y, SlicedImageSides.Left, SlicedImageSides.Top),
						&PointF::Zero, 0.0f, &color);

					// top right
					bon::_GetEngine().Gfx().DrawImage(Image,
						PointF((float)_destRect.Right(), (float)_destRect.Y),
						&PointI((int)(SlicedImageSides.Right * TextureScale), (int)(SlicedImageSides.Top * TextureScale)),
						BlendMode,
						&framework::RectangleI(sourceRect.Right() - SlicedImageSides.Right, sourceRect.Y, SlicedImageSides.Right, SlicedImageSides.Top),
						&PointF(1.0f, 0.0f), 0.0f, &color);
					
					// bottom left
					bon::_GetEngine().Gfx().DrawImage(Image,
						PointF((float)_destRect.X, (float)_destRect.Bottom()),
						&PointI((int)(SlicedImageSides.Left * TextureScale), (int)(SlicedImageSides.Bottom * TextureScale)),
						BlendMode,
						&framework::RectangleI(sourceRect.X, sourceRect.Bottom() - SlicedImageSides.Bottom, SlicedImageSides.Left, SlicedImageSides.Bottom),
						&PointF(0.0f, 1.0f), 0.0f, &color);

					// top right
					bon::_GetEngine().Gfx().DrawImage(Image,
						PointF((float)_destRect.Right(), (float)_destRect.Bottom()),
						&PointI((int)(SlicedImageSides.Right * TextureScale), (int)(SlicedImageSides.Bottom * TextureScale)),
						BlendMode,
						&framework::RectangleI(sourceRect.Right() - SlicedImageSides.Right, sourceRect.Bottom() - SlicedImageSides.Bottom, SlicedImageSides.Right, SlicedImageSides.Bottom),
						&PointF(1.0f, 1.0f), 0.0f, &color);
				}
				// draw top side
				{
					// calc source rect
					RectangleI sideSource = sourceRect;
					sideSource.X += SlicedImageSides.Left;
					sideSource.Width -= (SlicedImageSides.Left + SlicedImageSides.Right);
					sideSource.Height -= SlicedImageSides.Top;

					// calc dest rect
					RectangleI topDest = _destRect;
					topDest.X += (int)(SlicedImageSides.Left * TextureScale);
					topDest.Width -= (int)(SlicedImageSides.Left * TextureScale + SlicedImageSides.Right * TextureScale);
					topDest.Height = (int)(SlicedImageSides.Top * TextureScale);

					// draw top parts
					DrawTiled(topDest, color, sideSource);
				}
				// draw bottom side
				{
					// calc source rect
					RectangleI sideSource = sourceRect;
					sideSource.X += SlicedImageSides.Left;
					sideSource.Width -= (SlicedImageSides.Left + SlicedImageSides.Right);
					sideSource.Y = sideSource.Bottom() - SlicedImageSides.Bottom;
					sideSource.Height = SlicedImageSides.Bottom;

					// calc dest rect
					RectangleI topDest = _destRect;
					topDest.X += (int)(SlicedImageSides.Left * TextureScale);
					topDest.Width -= (int)(SlicedImageSides.Left * TextureScale + SlicedImageSides.Right * TextureScale);
					topDest.Y = (int)(topDest.Bottom() - SlicedImageSides.Bottom * TextureScale);
					topDest.Height = (int)(SlicedImageSides.Bottom * TextureScale);

					// draw bottom side parts
					DrawTiled(topDest, color, sideSource);
				}
				// draw left side
				{
					// calc source rect
					RectangleI sideSource = sourceRect;
					sideSource.Y += SlicedImageSides.Top;
					sideSource.Width = (int)(SlicedImageSides.Left);
					sideSource.Height -= SlicedImageSides.Top;

					// calc dest rect
					RectangleI topDest = _destRect;
					topDest.Y += (int)(SlicedImageSides.Top * TextureScale);
					topDest.Height -= (int)(SlicedImageSides.Bottom * TextureScale + SlicedImageSides.Top * TextureScale);
					topDest.Width = (int)(SlicedImageSides.Left * TextureScale);

					// draw left side parts
					DrawTiled(topDest, color, sideSource);
				}
				// draw right side
				{
					// calc source rect
					RectangleI sideSource = sourceRect;
					sideSource.Y += SlicedImageSides.Top;
					sideSource.X = sideSource.Right() - SlicedImageSides.Right;
					sideSource.Width = (int)(SlicedImageSides.Right);
					sideSource.Height -= SlicedImageSides.Top;

					// calc dest rect
					RectangleI topDest = _destRect;
					topDest.Y += (int)(SlicedImageSides.Top * TextureScale);
					topDest.Height -= (int)(SlicedImageSides.Bottom * TextureScale + SlicedImageSides.Top * TextureScale);
					topDest.X = topDest.Right() - (int)(SlicedImageSides.Right * TextureScale);
					topDest.Width = (int)(SlicedImageSides.Right * TextureScale);

					// draw left side parts
					DrawTiled(topDest, color, sideSource);
				}
				// draw center part
				{
					// calc source rect
					RectangleI centerSource = sourceRect;
					centerSource.X += SlicedImageSides.Left;
					centerSource.Width -= (SlicedImageSides.Left + SlicedImageSides.Right);
					centerSource.Y += SlicedImageSides.Top;
					centerSource.Height -= (SlicedImageSides.Top + SlicedImageSides.Bottom);

					// calc dest rect
					RectangleI centerDest = _destRect;
					centerDest.X += (int)(SlicedImageSides.Left * TextureScale);
					centerDest.Width -= (int)(SlicedImageSides.Left * TextureScale + SlicedImageSides.Right * TextureScale);
					centerDest.Y += (int)(SlicedImageSides.Top * TextureScale);
					centerDest.Height -= (int)(SlicedImageSides.Top * TextureScale + SlicedImageSides.Bottom * TextureScale);

					// draw center parts
					DrawTiled(centerDest, color, centerSource);
				}
			}
		}

		// draw tiled image
		void _UIImage::DrawTiled(const RectangleI& dest, const framework::Color& color, const RectangleI& source)
		{
			// get source rect actual values
			RectangleI sourceRect(source.X, source.Y, source.Width, source.Height);
			if (sourceRect.Width <= 0) { sourceRect.Width += Image->Width(); }
			if (sourceRect.Height <= 0) { sourceRect.Height += Image->Height(); }

			// calc the size of a single tile
			PointI tileSize((int)((sourceRect.Width) * TextureScale), (int)((sourceRect.Height) * TextureScale));

			// current position
			PointI position(dest.X, dest.Y);

			// draw tiles
			while (position.X < dest.Right())
			{
				position.Y = dest.Y;
				while (position.Y < dest.Bottom())
				{
					// get current tile size and source
					PointI currTileSize = tileSize;
					RectangleI currSourceRect = sourceRect;

					// check if need to trim on x axis
					int trimX = (position.X + currTileSize.X) - dest.Right();
					if (trimX > 0) {
						currSourceRect.Width -= (int)std::ceil((float)currSourceRect.Width * ((float)trimX / currTileSize.X));
						currTileSize.X -= trimX;
					}

					// check if need to trim on y axis
					int trimY = (position.Y + currTileSize.Y) - dest.Bottom();
					if (trimY > 0) {
						currSourceRect.Height -= (int)std::ceil((float)currSourceRect.Height * ((float)trimY / currTileSize.Y));
						currTileSize.Y -= trimY;
					}

					// draw tile
					bon::_GetEngine().Gfx().DrawImage(Image,
						position,
						&currTileSize,
						BlendMode,
						&currSourceRect,
						&PointF::Zero, 0.0f, &color);
					position.Y += tileSize.Y;
				}
				position.X += tileSize.X;
			}
		}
	}
}