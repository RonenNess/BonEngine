#include <BonEngine.h>

namespace bon
{
	// enabled features (set during init).
	BonFeatures _features;

	// get engine instance
	engine::Engine& _GetEngine()
	{
		static engine::Engine engine;
		return engine;
	}

	// start running the engine
	void Start(engine::Scene& startingScene, const BonFeatures& features)
	{
		_features = features;
		engine::Engine& engine = _GetEngine();
		engine.Start(startingScene);
	}

	// start running the engine
	void Start(engine::Scene& startingScene)
	{
		BonFeatures defaultFeatures;
		Start(startingScene, defaultFeatures);
	}
	
	// get enabled features
	const BonFeatures& Features()
	{
		return _features;
	}

	// credits and version
	const char* __author__ = "Ronen Ness";
	const char* __version__ = _BON_VERSION_STR;
}