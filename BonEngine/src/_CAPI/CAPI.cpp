#include <_CAPI/CAPI.h>
#include <BonEngine.h>


// start engine with special scene to accept callback
void BON_Start(bon::engine::Scene* scene)
{
	bon::Start(*scene);
}

// start engine with special scene to accept callback + params
void BON_StartEx(bon::engine::Scene* scene, bool forceOpenGL, bool enableEffects, bool enableLogs, bool registerToSignals)
{
	bon::BonFeatures features;
	features.ForceOpenGL = forceOpenGL;
	features.EffectsEnabled = enableEffects;
	features.Logging = enableLogs;
	features.RegisterSignalsHandler = registerToSignals;
	bon::Start(*scene, features);
}

// stopand exit the engine.
void BON_Stop()
{
	bon::_GetEngine().Stop();
}