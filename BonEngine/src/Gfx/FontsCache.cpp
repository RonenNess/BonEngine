#include <Gfx/FontsCache.h>


namespace bon
{
	namespace gfx
	{
		// Call every frame to update cache and clean old stuff.
		void FontsTextureCache::Update()
		{
			// check if time to check cache
			if (_timeForNextCheck-- > 0)
			{
				return;
			}
			_timeForNextCheck = 100;

			// iterate cache to check what can we release
			for (auto i = _cache.begin(), last = _cache.end(); i != last; ) 
			{
				// decrease ttl and check if expired
				CachedTexture& cached = (i)->second;
				cached.TTL -= 100;
				if (cached.TTL < 0 && cached.Texture) {
					SDL_DestroyTexture(cached.Texture);
					cached.Texture = nullptr;
				}

				// remove null textures
				if (cached.Texture == nullptr) {
					i = _cache.erase(i);
				}
				else {
					++i;
				}
			}
		}

		// Get texture from cache and update its TTL.
		CachedTexture& FontsTextureCache::GetFromCache(TTF_Font* font, const std::string& text)
		{
			CachedTexture& cached = (_cache[std::pair<TTF_Font*, std::string>(font, text)]);
			if (cached.Texture) {
				cached.TTL = 1500;
			}
			return cached;
		}
	}
}