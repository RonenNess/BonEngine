#include <Assets/Types/Effect.h>
#include <BonEngine.h>

namespace bon
{
	namespace assets
	{
		_Effect::_Effect(const char* path) : IAsset(path)
		{
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