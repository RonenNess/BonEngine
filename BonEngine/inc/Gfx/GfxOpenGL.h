/*****************************************************************//**
 * \file   GfxOpenGL.h
 * \brief  Wrap OpenGL calls.
 *
 * \author Ronen Ness
 * \date   January 2021
 *********************************************************************/
#pragma once
#include <string>
#include <Assets/Defs.h>
#include <Framework/RectangleF.h>
#include <Framework/Color.h>
#include <Gfx/Defs.h>

typedef unsigned int GLuint;
typedef int GLint;

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

namespace bon
{
	namespace gfx
	{
		/**
		 * The gfx effects implementor class.
		 */
		class GfxOpenGL
		{
		public:

			/**
			* Compile and return a GLSL program.
			*/
			static GLuint CompileProgramFromFiles(const char* vtxFile, const char* fragFile);

			/**
			* Compile and return a GLSL program.
			*/
			static GLuint CompileProgram(const char* vtxShader, const char* fragShader);

			/**
			 * Init gl extensions.
			 */
			static void InitGLExtensions(SDL_Renderer* renderer);

			/**
			 * Check if was initialized.
			 */
			static bool IsInit();

			/**
			 * Get current shader program.
			 */
			static GLint GetCurrentProgram();

			/**
			 * Draw a polygon.
			 */
			static void DrawPolygon(const framework::PointI& a, const framework::PointI& b, const framework::PointI& c, const framework::Color& color, BlendModes blend);

			/**
			 * Draw a polygon - just vertices, no params.
			 */
			static void DrawPolygon(const framework::PointI& a, const framework::PointI& b, const framework::PointI& c);

			/**
			 * Draw a textured quad.
			 */
			static void DrawTexture(const framework::PointF& position, const framework::PointI& size, const framework::RectangleI* sourceRect, SDL_Texture* texture, const framework::Color& color, int textW, int textH, BlendModes blend, bool useTexture, bool useVertexColor, bool flipTextureCoordsV, const framework::PointF& anchor, float rotate);
			
			/**
			 * Draw the vertices of a quad with rotation and anchor.
			 */
			static void DrawQuad(const framework::PointF& position, const framework::PointI& size, const framework::Color& color, const framework::PointF& anchor, float rotate, bool filled);

			/**
			 * Set current shader program.
			 */
			static void SetShaderProgram(GLint program);
			
			/**
			 * Set blending mode.
			 */
			static void SetBlendMode(BlendModes blend);

			/**
			 * Set current texture.
			 */
			static void SetTexture(SDL_Texture* texture);

			/**
			 * Clears a texture completely to transparent black.
			 */
			static void ClearTexture(SDL_Texture* texture, int width, int height);

			/**
			 * Get uniform location from program.
			 */
			static GLint GetUniformLocation(GLint programId, const char* name);

			/**
			 * Set float uniform.
			 */
			static void SetUniformFloat(GLint uniform, float value);

			/**
			 * Set vector2 uniform.
			 */
			static void SetUniformVector2(GLint uniform, float x, float y);

			/**
			 * Set vector3 uniform.
			 */
			static void SetUniformVector3(GLint uniform, float x, float y, float z);

			/**
			 * Set vector4 uniform.
			 */
			static void SetUniformVector4(GLint uniform, float x, float y, float z, float w);

			/**
			 * Set float uniform.
			 */
			static void SetUniformInt(GLint uniform, int value);

			/**
			 * Set vector2 uniform.
			 */
			static void SetUniformVector2(GLint uniform, int x, int y);

			/**
			 * Set vector3 uniform.
			 */
			static void SetUniformVector3(GLint uniform, int x, int y, int z);

			/**
			 * Set vector4 uniform.
			 */
			static void SetUniformVector4(GLint uniform, int x, int y, int z, int w);

			/**
			 * Set a matrix uniform.
			 */
			static void SetUniformMatrix2(GLint uniform, int count, bool transpose, const float* values);

			/**
			 * Set a matrix uniform.
			 */
			static void SetUniformMatrix3(GLint uniform, int count, bool transpose, const float* values);

			/**
			 * Set a matrix uniform.
			 */
			static void SetUniformMatrix4(GLint uniform, int count, bool transpose, const float* values);
		};
	}
}