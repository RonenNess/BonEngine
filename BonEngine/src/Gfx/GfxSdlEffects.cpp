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

#pragma warning(push, 0)
#include <SDL2-2.0.12/include/SDL.h>
#include <SDL2_image-2.0.5/include/SDL_image.h>
#include <SDL2_ttf-2.0.15/include/SDL_ttf.h>
#pragma warning(pop)

// default vertex shader
const char* _defaultVertexShader = "								\
varying vec4 v_color;												\n\
varying vec2 v_texCoord;											\n\
																	\n\
void main()															\n\
{																	\n\
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;			\n\
	v_color = gl_Color;												\n\
	v_texCoord = vec2(gl_MultiTexCoord0);							\n\
}																	\n\
";

// default fragment shader
const char* _defaultFragmentShader = "								\
varying vec4 v_color;												\n\
varying vec2 v_texCoord;											\n\
																	\n\
uniform sampler2D tex0;												\n\
																	\n\
void main()															\n\
{																	\n\
	gl_FragColor = v_color * texture2D(tex0, v_texCoord.xy).rgba;	\n\
}																	\n\
";

// default vertex shader for shapes
const char* _defaultVertexShaderShapes = "							\
																	\n\
void main()															\n\
{																	\n\
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;			\n\
}																	\n\
";

// default fragment shader for shapes
const char* _defaultFragmentShaderShapes = "						\
uniform vec4 shape_color;											\n\
																	\n\
void main()															\n\
{																	\n\
	gl_FragColor = shape_color.rgba;								\n\
}																	\n\
";

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
			std::unordered_map<std::string, GLint> _uniformAddress;

		public:

			/**
			 * Get this effect's program handle.
			 */
			virtual void* GetProgramHandle() const override { return (void*)&_programId; }

			/**
			 * Constructor.
			 */
			SDL_EffectHandle(const bon::assets::ConfigAsset& config) : _isValid(false)
			{
				// read basic properties
				_useTextures = config->GetBool("general", "texture", true);
				_useVertexColor = config->GetBool("general", "vertex_color", true);

				// get shader paths
				auto effectFolder = std::filesystem::path(config->Path()).parent_path().u8string();
				_vertexPath = std::filesystem::path(effectFolder).append(config->GetStr("shaders", "vertex", "shader.vertex")).u8string();
				_fragmentPath = std::filesystem::path(effectFolder).append(config->GetStr("shaders", "fragment", "shader.fragment")).u8string();
				BON_DLOG("Load effect '%s' shaders. Fragment: %s, Vertex: %s.", config->Path(), _fragmentPath.c_str(), _vertexPath.c_str());
				_programId = GfxOpenGL::CompileProgramFromFiles(_vertexPath.c_str(), _fragmentPath.c_str());
				BON_DLOG("Created effect program with id: %d", _programId);

				// load general params
				_flipCoordsV = config->GetBool("general", "flip_texture_v", true);

				// set as valid!
				_isValid = true;
			}

			/**
			 * Constructor with params.
			 */
			SDL_EffectHandle(bool useTexture, bool useVertexColor, bool flipTextureY, const char* vertex, const char* frag) : _isValid(false)
			{
				// store basic params
				_useTextures = useTexture;
				_useVertexColor = useVertexColor;
				_flipCoordsV = flipTextureY;

				// build program
				BON_DLOG("Create effect program from given params.");
				_programId = GfxOpenGL::CompileProgram(vertex, frag);
				BON_DLOG("Created effect program with id: %d", _programId);

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
		}

		// Load and return default shader.
		EffectAsset GfxSdlEffects::LoadDefaultProgram()
		{
			return bon::_GetEngine().Assets().CreateEffectFromHandle(new SDL_EffectHandle(true, true, false, _defaultVertexShader, _defaultFragmentShader));
		}

		// Load and return default shader for drawing shapes.
		EffectAsset GfxSdlEffects::LoadDefaultShapesProgram()
		{
			return bon::_GetEngine().Assets().CreateEffectFromHandle(new SDL_EffectHandle(false, false, false, _defaultVertexShaderShapes, _defaultFragmentShaderShapes));
		}
	}
}