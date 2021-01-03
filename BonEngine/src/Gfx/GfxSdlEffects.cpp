#include <Gfx/GfxSdlEffects.h>
#include <Log/ILog.h>
#include <Framework/Exceptions.h>
#include <Assets/Defs.h>
#include <Assets/Types/Effect.h>
#include <Assets/Types/EffectHandle.h>
#include <Gfx/Defs.h>
#include <BonEngine.h>
#include <Gfx/GfxOpenGL.h>
#include <filesystem>
#include <fstream>
#include <streambuf>

namespace fs = std::filesystem;

namespace bon
{
	namespace gfx
	{
		// effect handle for SDL
		class SDL_EffectHandle : public _EffectHandle
		{
		private:

			// loaded program id
			GLuint _programId;

			// fragment / vertex shaders full path
			std::string _fragmentPath;
			std::string _vertexPath;
			
			// effect params
			bool _isValid;
			bool _useTextures;
			bool _useVertexColor;
			bool _flipCoordsV;

			// cache uniforms
			unordered_map<std::string, GLint> _uniformAddress;

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
				_programId = GfxOpenGL::CompileProgram(_vertexPath.c_str(), _fragmentPath.c_str());
				BON_DLOG("Created effect program with id: %d", _programId);

				// load general params
				_flipCoordsV = config->GetBool("general", "flip_texture_v", true);

				// set as valid!
				_isValid = true;
			}

			/**
			 * Get uniform location from program.
			 */
			GLint GetUniform(const char* name)
			{
				// get from cache
				if (_uniformAddress.find(name) != _uniformAddress.end())
				{
					return _uniformAddress[name];
				}
				GLint ret = GfxOpenGL::GetUniformLocation(_programId, name);
				_uniformAddress[name] = ret;
				return ret;
			}

			/**
			 * Set float uniform.
			 */
			virtual void SetUniformFloat(const char* name, float value) override
			{
				GLint uni = GetUniform(name);
				GfxOpenGL::SetUniformFloat(uni, value);
			}

			/**
			 * Set vector2 uniform.
			 */
			virtual void SetUniformVector2(const char* name, float x, float y) override
			{
				GLint uni = GetUniform(name);
				GfxOpenGL::SetUniformVector2(uni, x, y);
			}

			/**
			 * Set vector3 uniform.
			 */
			virtual void SetUniformVector3(const char* name, float x, float y, float z) override
			{
				GLint uni = GetUniform(name);
				GfxOpenGL::SetUniformVector3(uni, x, y, z);
			}

			/**
			 * Set vector4 uniform.
			 */
			virtual void SetUniformVector4(const char* name, float x, float y, float z, float w) override
			{
				GLint uni = GetUniform(name);
				GfxOpenGL::SetUniformVector4(uni, x, y, z, w);
			}

			/**
			 * Set float uniform.
			 */
			virtual void SetUniformInt(const char* name, int value) override
			{
				GLint uni = GetUniform(name);
				GfxOpenGL::SetUniformInt(uni, value);
			}

			/**
			 * Set vector2 uniform.
			 */
			virtual void SetUniformVector2(const char* name, int x, int y) override
			{
				GLint uni = GetUniform(name);
				GfxOpenGL::SetUniformVector2(uni, x, y);
			}

			/**
			 * Set vector3 uniform.
			 */
			virtual void SetUniformVector3(const char* name, int x, int y, int z) override
			{
				GLint uni = GetUniform(name);
				GfxOpenGL::SetUniformVector3(uni, x, y, z);
			}

			/**
			 * Set vector4 uniform.
			 */
			virtual void SetUniformVector4(const char* name, int x, int y, int z, int w) override
			{
				GLint uni = GetUniform(name);
				GfxOpenGL::SetUniformVector4(uni, x, y, z, w);
			}

			/**
			 * Set a matrix uniform.
			 */
			virtual void SetUniformMatrix2(const char* name, int count, bool transpose, const float* values) override
			{
				GLint uni = GetUniform(name);
				GfxOpenGL::SetUniformMatrix2(uni, count, transpose, values);
			}

			/**
			 * Set a matrix uniform.
			 */
			virtual void SetUniformMatrix3(const char* name, int count, bool transpose, const float* values) override
			{
				GLint uni = GetUniform(name);
				GfxOpenGL::SetUniformMatrix3(uni, count, transpose, values);
			}

			/**
			 * Set a matrix uniform.
			 */
			virtual void SetUniformMatrix4(const char* name, int count, bool transpose, const float* values) override
			{
				GLint uni = GetUniform(name);
				GfxOpenGL::SetUniformMatrix4(uni, count, transpose, values);
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
			 * Get if should flip texture coords on Y axis.
			 *
			 * \return If should flip texture coords v.
			 */
			virtual bool FlipTextureCoordsV() const override { return _flipCoordsV; }

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

				// init extensions
				GfxOpenGL::InitGLExtensions(renderer);
			}

			// update renderer
			UpdateRenderer(renderer);
		}

		// update after renderer change
		void GfxSdlEffects::UpdateRenderer(SDL_Renderer* renderer)
		{
			// store renderer and reset default program id
			_renderer = renderer;
		}
		
		// set active effect
		void GfxSdlEffects::UseEffect(const assets::EffectAsset& effect)
		{
			// if we're about to replace the default effect, get its handle first
			if (_currentEffect == nullptr && effect != nullptr)
			{
				_defaultProgram = GfxOpenGL::GetCurrentProgram();
			}

			// remove effect
			if (effect == nullptr)
			{
				RestoreDefaultEffect();
				return;
			}

			// set effect
			GfxOpenGL::SetShaderProgram(((SDL_EffectHandle*)effect->Handle())->_GetProgram());
			_currentEffect = effect;
		}

		// restore default SDL shaders
		void GfxSdlEffects::RestoreDefaultEffect()
		{
			// set default program
			GfxOpenGL::SetShaderProgram(_defaultProgram);
			_currentEffect = nullptr;
		}

		// called on drawing frame end
		void GfxSdlEffects::OnFrameStart()
		{
			_defaultProgram = GfxOpenGL::GetCurrentProgram();
			RestoreDefaultEffect();
		}

		// set opengl blend mode
		void GfxSdlEffects::SetBlendMode(BlendModes blend)
		{
			GfxOpenGL::SetBlendMode(blend);
		}

		// draw a polygon
		void GfxSdlEffects::DrawPolygon(const PointI& a, const PointI& b, const PointI& c, const Color& color, BlendModes blend)
		{
			GfxOpenGL::DrawPolygon(a, b, c, color, blend);
		}

		// draw texture with effect on screen
		void GfxSdlEffects::DrawTexture(const SDL_Rect* destRect, const SDL_Rect* sourceRect, SDL_Texture* texture, const Color& color, int textW, int textH, BlendModes blend, int flip)
		{
			GfxOpenGL::DrawTexture(destRect, sourceRect, texture, color, textW, textH, blend, flip, _currentEffect->UseTextures(), _currentEffect->UseVertexColor(), _currentEffect->Handle()->FlipTextureCoordsV());
		}
	}
}