#include <_CAPI/CAPI.h>
#include <BonEngine.h>


// start engine with special scene to accept callback
void BON_Start(bon::engine::Scene* scene)
{
	bon::Start(*scene);
}

// stopand exit the engine.
void BON_Stop()
{
	bon::_GetEngine().Stop();
}