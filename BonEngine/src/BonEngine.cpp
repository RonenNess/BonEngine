#include <BonEngine.h>

namespace bon
{
	// get engine instance
	engine::Engine& _GetEngine()
	{
		static engine::Engine engine;
		return engine;
	}

	// start running the engine
	void Start(engine::Scene& startingScene)
	{
		engine::Engine& engine = _GetEngine();
		engine.Start(startingScene);
	}

	// credits and version
	const char* __author__ = "Ronen Ness";
	const char* __version__ = _BON_VERSION_STR;
}