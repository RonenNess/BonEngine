#include <Assets/Types/Effect.h>
#include <BonEngine.h>

namespace bon
{
	namespace assets
	{
		_Effect::_Effect(const char* path) : IAsset(path)
		{
			if (!bon::Features().EffectsEnabled)
			{
				throw framework::AssetLoadError("Can't load Effect asset because Effects are disabled! To use effects, please call bon::Start() with Features containing effects flag as 'true'.");
			}
		}

		void _Effect::ValidateActive() const
		{
			if (_GetEngine().Gfx().GetActiveEffect().get() != this)
			{
				throw exception("Can't set effect uniforms when effect is not the currently active effect!");
			}
		}
	}
}