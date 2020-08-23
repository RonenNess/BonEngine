#include <Gfx/GfxSdlEffects.h>
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
		 * Compile and return a GLSL program.
		 */
		GLuint compileProgram(const char* vtxFile, const char* fragFile) 
		{
			GLuint programId = 0;
			GLuint vtxShaderId, fragShaderId;

			programId = glCreateProgram();

			std::ifstream f(vtxFile);
			std::string source((std::istreambuf_iterator<char>(f)),
				std::istreambuf_iterator<char>());
			vtxShaderId = compileShader(source.c_str(), GL_VERTEX_SHADER);

			f = std::ifstream(fragFile);
			source = std::string((std::istreambuf_iterator<char>(f)),
				std::istreambuf_iterator<char>());
			fragShaderId = compileShader(source.c_str(), GL_FRAGMENT_SHADER);

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

		// effect handle for SDL
		class SDL_EffectHandle : public _EffectHandle
		{
		private:
			bool _useTextures;
			bool _useVertexColor;
			bool _isValid;
			GLuint _programId;
			std::string _fragmentPath;
			std::string _vertexPath;

		public:
			
			/**
			 * Constructor.
			 */
			SDL_EffectHandle(const ConfigAsset& config) : _isValid(false)
			{
				// read basic properties
				_useTextures = config->GetBool("general", "texture", true);
				_useVertexColor = config->GetBool("general", "vertex_color", true);

				// get shader paths
				auto effectFolder = fs::path(config->Path()).parent_path().u8string();
				_vertexPath = fs::path(effectFolder).append(config->GetStr("shaders", "vertex", "shader.vertex")).u8string();
				_fragmentPath = fs::path(effectFolder).append(config->GetStr("shaders", "fragment", "shader.fragment")).u8string();
				BON_DLOG("Load effect '%s' shaders. Fragment: %s, Vertex: %s.", config->Path(), _fragmentPath.c_str(), _vertexPath.c_str());
				_programId = compileProgram(_vertexPath.c_str(), _fragmentPath.c_str());
				BON_DLOG("Created effect program with id: %d", _programId);

				// set as valid!
				_isValid = true;
			}

			/**
			 * Get effect program id.
			 */
			inline GLuint _GetProgram() const { return _programId; }

			/**
			 * Get the path of the fragment shader file.
			 * 
			 * \return Fragment shader file path.
			 */
			virtual const char* FragmentShaderPath() const override { return _fragmentPath.c_str(); }

			/**
			 * Get the path of the vertex shader file.
			 *
			 * \return Vertex shader file path.
			 */
			virtual const char* VertexShaderPath() const override { return _vertexPath.c_str(); }


			/**
			 * Get if this handle is valid.
			 *
			 * \return If image is valid.
			 */
			virtual bool IsValid() const override { return _isValid; }

			/**
			 * Get if this effect use textures.
			 *
			 * \return If this effect uses textures
			 */
			virtual bool UseTexture() const override { return _useTextures; }

			/**
			 * Get if this effect use vertex color.
			 *
			 * \return If this effect uses vertex color
			 */
			virtual bool UseVertexColor() const override { return _useVertexColor; }
		};


		// effects loader we set in the assets manager during initialize
		void EffectsLoader(bon::assets::IAsset* asset, void* context, void* extraData = nullptr)
		{
			// get effect ini file
			ConfigAsset effectIni = bon::_GetEngine().Assets().LoadConfig(asset->Path());

			// set asset handle
			SDL_EffectHandle* handle = new SDL_EffectHandle(effectIni);
			asset->_SetHandle(handle);
		}

		// effects disposer we set in the assets manager during asset disposal
		void EffectDisposer(bon::assets::IAsset* asset, void* context)
		{
			asset->_DestroyHandle<SDL_EffectHandle>();
		}

		// initialize the sdl effects manager.
		void GfxSdlEffects::Initialize(SDL_Renderer* renderer)
		{
			// do stuff on first init only
			static bool firstInit = true;
			if (firstInit)
			{
				// no longer first init
				firstInit = false;

				// set the effects assets loader
				bon::_GetEngine().Assets()._SetAssetsInitializer(bon::assets::AssetTypes::Effect, EffectsLoader, EffectDisposer, this);

				// get renderer info
				SDL_RendererInfo rendererInfo;
				SDL_GetRendererInfo(renderer, &rendererInfo);

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

			// update renderer
			UpdateRenderer(renderer);
		}

		// update after renderer change
		void GfxSdlEffects::UpdateRenderer(SDL_Renderer* renderer)
		{
			// store renderer and reset default program id
			_defaultProgram = 0;
			_renderer = renderer;
		}
		
		// set active effect
		void GfxSdlEffects::UseEffect(const assets::EffectAsset& effect)
		{
			// just in case - try to get default program
			if (_defaultProgram == 0)
			{
				glGetIntegerv(GL_CURRENT_PROGRAM, &_defaultProgram);
			}

			// remove effect
			if (effect == nullptr)
			{
				RestoreDefaultEffect();
				return;
			}

			// set effect
			glUseProgram(((SDL_EffectHandle*)effect->Handle())->_GetProgram());
			_effect = effect;
		}

		// restore default SDL shaders
		void GfxSdlEffects::RestoreDefaultEffect()
		{
			// set default program
			if (glUseProgram)
			{
				glUseProgram(_defaultProgram);
				_effect = nullptr;
			}
		}

		// called on drawing frame end
		void GfxSdlEffects::OnFrameStart()
		{
			glGetIntegerv(GL_CURRENT_PROGRAM, &_defaultProgram);
			RestoreDefaultEffect();
		}

		// draw texture with effect on screen
		void GfxSdlEffects::DrawTexture(const SDL_Rect* destRect, const SDL_Rect* sourceRect, SDL_Texture* texture, const Color& color, int textW, int textH)
		{
			// bind texture
			bool useTexture = _effect->UseTextures();
			if (useTexture)
			{
				SDL_GL_BindTexture(texture, NULL, NULL);
			}

			// use vertex color
			bool useVertexColor = _effect->UseVertexColor();

			// set coords and uvs
			GLfloat minx, miny, maxx, maxy;
			GLfloat minu, maxu, minv, maxv;
			
			// coords
			const framework::PointI& rnderableSize = bon::_GetEngine().Gfx().RenderableSize();
			minx = (GLfloat)destRect->x;
			miny = (GLfloat)destRect->y;
			maxx = (GLfloat)(destRect->x + destRect->w);
			maxy = (GLfloat)(destRect->y + destRect->h);

			// uvs
			if (sourceRect != nullptr)
			{
				minu = (GLfloat)sourceRect->x / textW;
				maxu = (GLfloat)(sourceRect->x + sourceRect->w) / textW;
				minv = (GLfloat)(sourceRect->y + sourceRect->h) / textH;
				maxv = (GLfloat)sourceRect->y / textH;
			}
			else
			{
				minu = 0;
				maxu = 1;
				minv = 0;
				maxv = 1;
			}

			// start drawing quad
			glBegin(GL_TRIANGLE_STRIP);

			// top-left
			if (useTexture) glTexCoord2f(minu, minv);
			if (useVertexColor) glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(minx, miny);

			// top-right
			if (useTexture) glTexCoord2f(maxu, minv);
			if (useVertexColor) glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(maxx, miny);

			// bottom-left
			if (useTexture) glTexCoord2f(minu, maxv);
			if (useVertexColor) glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(minx, maxy);

			// bottom-right
			if (useTexture) glTexCoord2f(maxu, maxv);
			if (useVertexColor) glColor4f(color.R, color.G, color.B, color.A);
			glVertex2f(maxx, maxy);

			// finish drawing quad
			glEnd();
		}
	}
}