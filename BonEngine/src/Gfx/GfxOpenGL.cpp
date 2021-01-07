#include <Gfx/GfxOpenGL.h>
#include <fstream>
#include <streambuf>

#include <SDL2-2.0.12/include/SDL.h>
#include <SDL2_image-2.0.5/include/SDL_image.h>

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#include <OpenGL/OpenGL.h>

#if ESSENTIAL_GL_PRACTICES_SUPPORT_GL3
#include <OpenGL/gl3.h>
#else
#include <OpenGL/gl.h>
#endif //!ESSENTIAL_GL_PRACTICES_SUPPORT_GL3
#else
#include <SDL2-2.0.12/include/SDL_opengl.h>
#include <SDL2-2.0.12/include/SDL_opengl_glext.h>
#endif

#include <filesystem>
#include <Log/ILog.h>
#include <Framework/Exceptions.h>
#include <Assets/Defs.h>
#include <Assets/Types/Effect.h>
#include <Assets/Types/EffectHandle.h>
#include <Gfx/Defs.h>
#include <BonEngine.h>

using namespace bon::framework;
using namespace bon::assets;
namespace fs = std::filesystem;

// init gl extensions
#ifndef __APPLE__

PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLVALIDATEPROGRAMPROC glValidateProgram;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM2FPROC glUniform2f;
PFNGLUNIFORM3FPROC glUniform3f;
PFNGLUNIFORM4FPROC glUniform4f;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM2IPROC glUniform2i;
PFNGLUNIFORM3IPROC glUniform3i;
PFNGLUNIFORM4IPROC glUniform4i;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
PFNGLBLENDEQUATIONEXTPROC glBlendEquationEXT;
PFNGLBLENDEQUATIONSEPARATEEXTPROC glBlendEquationSeparateEXT;
//PFNGLCLEARTEXIMAGEPROC glClearTexImage;

// load GL extension methods
bool initGLExtensions()
{
	glCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)SDL_GL_GetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)SDL_GL_GetProcAddress("glGetShaderInfoLog");
	glDeleteShader = (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");
	glAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)SDL_GL_GetProcAddress("glValidateProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)SDL_GL_GetProcAddress("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog");
	glUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)SDL_GL_GetProcAddress("glGetUniformLocation");
	glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)SDL_GL_GetProcAddress("glBlendFuncSeparate");
	glUniform1f = (PFNGLUNIFORM1FPROC)SDL_GL_GetProcAddress("glUniform1f");
	glUniform2f = (PFNGLUNIFORM2FPROC)SDL_GL_GetProcAddress("glUniform2f");
	glUniform3f = (PFNGLUNIFORM3FPROC)SDL_GL_GetProcAddress("glUniform3f");
	glUniform4f = (PFNGLUNIFORM4FPROC)SDL_GL_GetProcAddress("glUniform4f");
	glUniform1i = (PFNGLUNIFORM1IPROC)SDL_GL_GetProcAddress("glUniform1i");
	glUniform2i = (PFNGLUNIFORM2IPROC)SDL_GL_GetProcAddress("glUniform2i");
	glUniform3i = (PFNGLUNIFORM3IPROC)SDL_GL_GetProcAddress("glUniform3i");
	glUniform4i = (PFNGLUNIFORM4IPROC)SDL_GL_GetProcAddress("glUniform4i");
	glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)SDL_GL_GetProcAddress("glUniformMatrix2fv");
	glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)SDL_GL_GetProcAddress("glUniformMatrix3fv");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)SDL_GL_GetProcAddress("glUniformMatrix4fv");
	glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)SDL_GL_GetProcAddress("glBlendEquationSeparate");
	glBlendEquationEXT = (PFNGLBLENDEQUATIONEXTPROC)SDL_GL_GetProcAddress("glBlendEquationEXT");
	glBlendEquationSeparateEXT = (PFNGLBLENDEQUATIONSEPARATEEXTPROC)SDL_GL_GetProcAddress("glBlendEquationSeparateEXT");

	return glCreateShader && glShaderSource && glCompileShader && glGetShaderiv &&
		glGetShaderInfoLog && glDeleteShader && glAttachShader && glCreateProgram &&
		glLinkProgram && glValidateProgram && glGetProgramiv && glGetProgramInfoLog &&
		glUseProgram;
}

#endif


namespace bon
{
	namespace gfx
	{
		/**
		 * Compile and return a glsl shader.
		 */
		GLuint compileShader(const char* source, GLuint shaderType)
		{
			BON_DLOG("Compile shader: %s", source);

			// create ID for shader
			GLuint result = glCreateShader(shaderType);

			// define shader text
			glShaderSource(result, 1, &source, NULL);

			// compile shader
			glCompileShader(result);

			// check shader for errors
			GLint shaderCompiled = GL_FALSE;
			glGetShaderiv(result, GL_COMPILE_STATUS, &shaderCompiled);
			if (shaderCompiled != GL_TRUE)
			{
				BON_ELOG("Error compiling shader: %d!", result);
				GLint logLength;
				glGetShaderiv(result, GL_INFO_LOG_LENGTH, &logLength);
				if (logLength > 0)
				{
					GLchar* log = (GLchar*)malloc(logLength);
					glGetShaderInfoLog(result, logLength, &logLength, log);
					BON_ELOG("Shader compile log: %s", log);
					free(log);
				}
				throw bon::framework::AssetLoadError("Failed to build shader!");
				glDeleteShader(result);
				result = 0;
			}
			return result;
		}

		/**
		 * Compile and return a GLSL program from file.
		 */
		GLuint GfxOpenGL::CompileProgramFromFiles(const char* vtxFile, const char* fragFile)
		{
			std::ifstream fvtx(vtxFile);
			std::string sourceVtx((std::istreambuf_iterator<char>(fvtx)), std::istreambuf_iterator<char>());
			std::ifstream ffrag(fragFile);
			std::string sourceFrag((std::istreambuf_iterator<char>(ffrag)), std::istreambuf_iterator<char>());
			return CompileProgram(sourceVtx.c_str(), sourceFrag.c_str());
		}

		/**
		 * Compile and return a GLSL program.
		 */
		GLuint GfxOpenGL::CompileProgram(const char* vtxShader, const char* fragShader)
		{
			GLuint programId = 0;
			GLuint vtxShaderId, fragShaderId;

			programId = glCreateProgram();

			vtxShaderId = compileShader(vtxShader, GL_VERTEX_SHADER);
			fragShaderId = compileShader(fragShader, GL_FRAGMENT_SHADER);

			if (vtxShaderId && fragShaderId)
			{
				// associate shader with program
				glAttachShader(programId, vtxShaderId);
				glAttachShader(programId, fragShaderId);
				glLinkProgram(programId);
				glValidateProgram(programId);

				// check the status of the compile/link
				GLint logLen;
				glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLen);
				if (logLen > 0) {
					char* log = (char*)malloc(logLen * sizeof(char));

					// show any errors as appropriate
					glGetProgramInfoLog(programId, logLen, &logLen, log);
					BON_DLOG("Compiling shaders prog info log:\n%s", log);
					free(log);
				}
			}
			if (vtxShaderId) {
				glDeleteShader(vtxShaderId);
			}
			if (fragShaderId) {
				glDeleteShader(fragShaderId);
			}
			return programId;
		}

		// was the opengl wrapper initialized
		bool _wasInit = false;
		bool GfxOpenGL::IsInit()
		{
			return _wasInit;
		}

		/**
		 * Init gl extensions.
		 */
		void GfxOpenGL::InitGLExtensions(SDL_Renderer* renderer)
		{
			// skip if init
			if (_wasInit) { return; }
			_wasInit = true;

			// get renderer info
			SDL_RendererInfo rendererInfo;
			SDL_GetRendererInfo((SDL_Renderer*)renderer, &rendererInfo);

			// init shaders
			if (!strncmp(rendererInfo.name, "opengl", 6)) {
				BON_DLOG("Initialize OpenGL extensions.");
#ifndef __APPLE__
				if (!initGLExtensions()) {
					BON_ELOG("Couldn't init GL extensions!");
					SDL_Quit();
					exit(-1);
				}
#endif
			}
		}

		/**
		 * Set current shader program.
		 */
		void GfxOpenGL::SetShaderProgram(GLint program)
		{
			if (glUseProgram)
			{
				glUseProgram(program);
			}
		}

		/**
		* Clears a texture completely to transparent black.
		*/
		void GfxOpenGL::ClearTexture(SDL_Texture* texture, int width, int height)
		{
			float w;
			float h;
			SDL_GL_BindTexture(texture, &w, &h);
			std::vector<GLubyte> emptyData((size_t)width * (size_t)height * 4, 0);
			SDL_UpdateTexture(texture, NULL, &emptyData[0], width * 4);
		}

		/**
		 * Draw a polygon.
		 */
		void GfxOpenGL::DrawPolygon(const PointI& a, const PointI& b, const PointI& c, const Color& color, BlendModes blend)
		{
			// remove texture
			SetTexture(nullptr);

			// set blend mode
			SetBlendMode(blend);

			// remove face culling
			glDisable(GL_CULL_FACE);

			// start drawing quad
			glBegin(GL_TRIANGLE_STRIP);

			glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f((GLfloat)a.X, (GLfloat)a.Y);

			glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f((GLfloat)b.X, (GLfloat)b.Y);

			glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f((GLfloat)c.X, (GLfloat)c.Y);

			// finish drawing quad
			glEnd();
		}

		/**
		 * Draw a polygon.
		 */
		void GfxOpenGL::DrawPolygon(const PointI& a, const PointI& b, const PointI& c)
		{
			// start drawing quad
			glBegin(GL_TRIANGLE_STRIP);

			glVertex2f((GLfloat)a.X, (GLfloat)a.Y);
			glVertex2f((GLfloat)b.X, (GLfloat)b.Y);
			glVertex2f((GLfloat)c.X, (GLfloat)c.Y);

			// finish drawing quad
			glEnd();
		}

		/**
		 * Get current shader program.
		 */
		GLint GfxOpenGL::GetCurrentProgram()
		{
			GLint ret;
			glGetIntegerv(GL_CURRENT_PROGRAM, &ret);
			return ret;
		}

		/**
		 * Set blending mode.
		 */
		void GfxOpenGL::SetBlendMode(BlendModes blend)
		{
			static BlendModes _lastBlend = BlendModes::_Count;
			if (_lastBlend == blend) { return; }
			_lastBlend = blend;

			// reset equation function
			if (glBlendEquationEXT) glBlendEquationEXT(GL_FUNC_ADD);
			glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_ALPHA_TEST);

			// set blend mode
			switch (blend)
			{
			case BlendModes::Opaque:
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				glDisable(GL_BLEND);
				break;

			case BlendModes::Darken:
				glBlendFunc(GL_ONE, GL_ONE);
				if (glBlendEquationEXT) glBlendEquationEXT(GL_MIN);
				glEnable(GL_BLEND);
				break;

			case BlendModes::Additive:
				glBlendFunc(GL_ONE, GL_ONE);
				glEnable(GL_BLEND);
				break;

			case BlendModes::AdditiveAlpha:
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				glEnable(GL_BLEND);
				break;

			case BlendModes::AlphaBlend:
				glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
				glEnable(GL_BLEND);
				break;

			case BlendModes::Subtract:
				glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE, GL_ONE, GL_ONE);
				glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD);
				glEnable(GL_BLEND);
				break;

			case BlendModes::Multiply:
				glBlendFunc(GL_DST_COLOR, GL_ZERO);
				glEnable(GL_BLEND);
				break;

			case BlendModes::Invert:
				glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
				glEnable(GL_BLEND);
				break;

			case BlendModes::Difference:
				glBlendFunc(GL_ONE, GL_ONE);
				if (glBlendEquationEXT) { glBlendEquationEXT(GL_FUNC_SUBTRACT); }
				glEnable(GL_BLEND);
				break;

			case BlendModes::Lighten:
				glBlendFunc(GL_ONE, GL_ONE);
				if (glBlendEquationEXT) { glBlendEquationEXT(GL_MAX); }
				glEnable(GL_BLEND);
				break;

			case BlendModes::Screen:
				glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
				glEnable(GL_BLEND);
				break;
			}
		}

		/**
		* Set current texture.
		*/
		void GfxOpenGL::SetTexture(SDL_Texture* texture)
		{
			SDL_Texture* _lastTexture = nullptr;
			if (_lastTexture == texture) { return; }
			_lastTexture = texture;
			SDL_GL_BindTexture(texture, NULL, NULL);
		}

		/**
		 * Draw a textured quad.
		 */
		void GfxOpenGL::DrawTexture(const PointF& position, const PointI& size, const framework::RectangleI* sourceRect, SDL_Texture* texture, const Color& color, int textW, int textH, BlendModes blend, bool useTexture, bool useVertexColor, bool flipTextureCoordsV, const framework::PointF& anchor, float rotate)
		{
			// bind texture
			if (useTexture)
			{
				SetTexture(texture);
			}

			// set blend mode
			SetBlendMode(blend);

			// set coords and uvs
			GLfloat minx, miny, maxx, maxy;
			GLfloat minu, maxu, minv, maxv;

			// calc coords
			minx = (GLfloat)position.X;
			miny = (GLfloat)position.Y;
			maxx = (GLfloat)(position.X + abs(size.X));
			maxy = (GLfloat)(position.Y + abs(size.Y));

			// uvs
			if (sourceRect != nullptr)
			{
				minu = (GLfloat)sourceRect->X / textW;
				maxu = (GLfloat)(sourceRect->X + sourceRect->Width) / textW;
				if (flipTextureCoordsV)
				{
					minv = (GLfloat)(sourceRect->Y + sourceRect->Height) / textH;
					maxv = (GLfloat)sourceRect->Y / textH;
				}
				else
				{
					minv = (GLfloat)sourceRect->Y / textH;
					maxv = (GLfloat)(sourceRect->Y + sourceRect->Height) / textH;
				}
			}
			else
			{
				minu = 0;
				maxu = 1;
				if (flipTextureCoordsV)
				{
					minv = 1;
					maxv = 0;
				}
				else
				{
					minv = 0;
					maxv = 1;
				}
			}

			// do flips
			if (size.X < 0)
			{
				float temp = minv;
				minv = maxv;
				maxv = temp;
			}
			if (size.Y < 0)
			{
				float temp = minu;
				minu = maxu;
				maxu = temp;
			}

			// do rotation
			if (rotate != 0)
			{
				glPushMatrix();
				glTranslatef(minx , miny , 0);
				glRotatef(rotate, 0, 0, 1);
				glTranslatef(-minx , -miny , 0);
			}

			// apply anchor
			if (anchor.X != 0 || anchor.Y != 0)
			{
				float anchorX = anchor.X * abs(size.X);
				float anchorY = anchor.Y * abs(size.Y);
				minx -= anchorX;
				miny -= anchorY;
				maxx -= anchorX;
				maxy -= anchorY;
			}

			// start drawing quad
			glBegin(GL_QUADS);

			// top-left
			if (useTexture) glTexCoord2f(minu, minv);
			if (useVertexColor) glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(minx, miny);

			// bottom-left
			if (useTexture) glTexCoord2f(minu, maxv);
			if (useVertexColor) glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(minx, maxy);

			// bottom-right
			if (useTexture) glTexCoord2f(maxu, maxv);
			if (useVertexColor) glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(maxx, maxy);
			
			// top-right
			if (useTexture) glTexCoord2f(maxu, minv);
			if (useVertexColor) glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(maxx, miny);

			// finish drawing quad
			glEnd();

			// pop rotation
			if (rotate != 0)
			{
				glPopMatrix();
			}
		}

		/**
		* Draw the vertices of a quad with rotation and anchor.
		*/
		void GfxOpenGL::DrawQuad(const framework::PointF& position, const framework::PointI& size, const framework::Color& color, const framework::PointF& anchor, float rotate, bool filled)
		{
			// set coords and uvs
			GLfloat minx, miny, maxx, maxy;

			// calc coords
			minx = (GLfloat)position.X;
			miny = (GLfloat)position.Y;
			maxx = (GLfloat)(position.X + abs(size.X));
			maxy = (GLfloat)(position.Y + abs(size.Y));

			// do rotation
			if (rotate != 0)
			{
				glPushMatrix();
				glTranslatef(minx, miny, 0);
				glRotatef(rotate, 0, 0, 1);
				glTranslatef(-minx, -miny, 0);
			}

			// apply anchor
			if (anchor.X != 0 || anchor.Y != 0)
			{
				float anchorX = anchor.X * abs(size.X);
				float anchorY = anchor.Y * abs(size.Y);
				minx -= anchorX;
				miny -= anchorY;
				maxx -= anchorX;
				maxy -= anchorY;
			}

			// start drawing quad
			glBegin(filled ? GL_QUADS : GL_LINE_STRIP);

			// top-left
			glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(minx, miny);

			// bottom-left
			glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(minx, maxy);

			// bottom-right
			glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(maxx, maxy);

			// top-right
			glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(maxx, miny);
			
			// push closing vertex for last line
			if (!filled)
			{
				glColor4f(color.R, color.G, color.B, color.A);
				glVertex2f(minx, miny);
			}

			// finish drawing quad
			glEnd();

			// pop rotation
			if (rotate != 0)
			{
				glPopMatrix();
			}
		}

		/**
		 * Get uniform location from program.
		 */
		GLint GfxOpenGL::GetUniformLocation(GLint programId, const char* name)
		{
			return glGetUniformLocation(programId, name);
		}

		/**
		 * Set float uniform.
		 */
		void GfxOpenGL::SetUniformFloat(GLint uniform, float value)
		{
			glUniform1f(uniform, value);
		}

		/**
		 * Set vector2 uniform.
		 */
		void GfxOpenGL::SetUniformVector2(GLint uniform, float x, float y)
		{
			glUniform2f(uniform, x, y);
		}

		/**
		 * Set vector3 uniform.
		 */
		void GfxOpenGL::SetUniformVector3(GLint uniform, float x, float y, float z)
		{
			glUniform3f(uniform, x, y, z);
		}

		/**
		 * Set vector4 uniform.
		 */
		void GfxOpenGL::SetUniformVector4(GLint uniform, float x, float y, float z, float w)
		{
			glUniform4f(uniform, x, y, z, w);
		}

		/**
		 * Set float uniform.
		 */
		void GfxOpenGL::SetUniformInt(GLint uniform, int value)
		{
			glUniform1i(uniform, value);
		}

		/**
		 * Set vector2 uniform.
		 */
		void GfxOpenGL::SetUniformVector2(GLint uniform, int x, int y)
		{
			glUniform2i(uniform, x, y);
		}

		/**
		 * Set vector3 uniform.
		 */
		void GfxOpenGL::SetUniformVector3(GLint uniform, int x, int y, int z)
		{
			glUniform3i(uniform, x, y, z);
		}

		/**
		 * Set vector4 uniform.
		 */
		void GfxOpenGL::SetUniformVector4(GLint uniform, int x, int y, int z, int w)
		{
			glUniform4i(uniform, x, y, z, w);
		}

		/**
		 * Set a matrix uniform.
		 */
		void GfxOpenGL::SetUniformMatrix2(GLint uniform, int count, bool transpose, const float* values)
		{
			glUniformMatrix2fv(uniform, count, transpose, values);
		}

		/**
		 * Set a matrix uniform.
		 */
		void GfxOpenGL::SetUniformMatrix3(GLint uniform, int count, bool transpose, const float* values)
		{
			glUniformMatrix3fv(uniform, count, transpose, values);
		}

		/**
		 * Set a matrix uniform.
		 */
		void GfxOpenGL::SetUniformMatrix4(GLint uniform, int count, bool transpose, const float* values)
		{
			glUniformMatrix4fv(uniform, count, transpose, values);
		}
	}
}