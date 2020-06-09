/*****************************************************************//**
 * \file   FontsCache.h
 * \brief  A cache of font textures to render when drawing text.
 *
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include <unordered_map>
#include <string>

#pragma warning(push, 0)
#include <SDL2-2.0.12/include/SDL.h>
#include <SDL2_ttf-2.0.15/include/SDL_ttf.h>
#pragma warning(pop)


namespace bon
{
	namespace gfx
	{
		// A hash function used to hash a pair of any kind 
		struct hash_pair {
			template <class T1, class T2>
			size_t operator()(const std::pair<T1, T2>& p) const
			{
				auto hash1 = std::hash<T1>{}(p.first);
				auto hash2 = std::hash<T2>{}(p.second);
				return hash1 ^ hash2;
			}
		};

		// a texture stored in cache
		struct CachedTexture
		{
		public:
			// the cached texture
			SDL_Texture* Texture = nullptr;

			// frames left for this cache to live
			int TTL = 0;

			// texture width
			int Width = 0;

			// texture height
			int Height = 0;
		};

		/**
		 * Store a cache of fonts and texts converted to textures, so we can render them.
		 */
		class FontsTextureCache
		{
		private:

			// textures cache
			std::unordered_map<std::pair<TTF_Font*, std::string>, CachedTexture, hash_pair> _cache;

			// count updates until next time we test cache
			int _timeForNextCheck = 100;

		public:

			/**
			 * Call every frame to update cache and clean old stuff.
			 */
			void Update();

			/**
			 * Add texture to cache.
			 * 
			 * \param font Texture font.
			 * \param text Text to render.
			 * \param texture Texture to cache.
			 * \param width Texture width.
			 * \param height Texture height.
			 */
			CachedTexture& AddToCache(TTF_Font* font, const std::string& text, SDL_Texture* texture, int width, int height)
			{
				CachedTexture cache;
				cache.TTL = 1000;
				cache.Texture = texture;
				cache.Width = width;
				cache.Height = height;
				return _cache[std::pair<TTF_Font*, std::string>(font, text)] = cache;
			}

			/**
			 * Get texture from cache and update its TTL.
			 * 
			 * \param font Texture font.
			 * \param text Text to render.
			 * \return Texture instance or null if not in cache.
			 */
			CachedTexture& GetFromCache(TTF_Font* font, const std::string& text);
		};
	}
}