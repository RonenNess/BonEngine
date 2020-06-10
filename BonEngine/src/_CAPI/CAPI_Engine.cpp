#include <_CAPI/CAPI_Engine.h>
#include <_CAPI/CAPI_Scene.h>
#include <BonEngine.h>
#include <string>


/**
 * Special manager that accept callbacks.
 * We use this as a trick to allow external languages (binds) to create custom managers using callbacks.
 */
class _CallbacksManager : public bon::IManager
{
public:
	BON_CallbackNoArgs __Initialize;
	BON_CallbackNoArgs __Start;
	BON_CallbackNoArgs __Dispose;
	BON_CallbackDoubleArg __Update;
	std::string _id;

protected:
	/**
	 * Initialize manager when engine starts.
	 */
	virtual void _Initialize() override 
	{
		__Initialize();
	}

	/**
	 * Called when main loop starts.
	 */
	virtual void _Start() override
	{
		__Start();
	}

	/**
	 * Clear / free this manager's resources.
	 */
	virtual void _Dispose() override
	{
		__Dispose();
	}

	/**
	 * Called every frame.
	 */
	virtual void _Update(double deltaTime) override
	{
		__Update(deltaTime);
	}

	/**
	 * Handles an event from OS.
	 */
	virtual void _HandleEvent(SDL_Event& event) override
	{
		// NOT SUPPORTED FOR BINDS
	}

	/**
	 * Get manager identifier.
	 */
	virtual const char* _GetId() const override
	{
		return _id.c_str();
	}
};

// create and return a manager with callbacks
bon::IManager* BON_Manager_Create(BON_CallbackNoArgs initialize, BON_CallbackNoArgs start, BON_CallbackNoArgs dispose, BON_CallbackDoubleArg update, const char* id)
{
	_CallbacksManager* ret = new _CallbacksManager();
	ret->__Initialize = initialize;
	ret->__Start = start;
	ret->__Dispose = dispose;
	ret->__Update = update;
	ret->_id = id;
	return ret;
}

// register a custom manager.
void BON_Manager_Register(bon::IManager* manager)
{
	bon::_GetEngine().RegisterCustomManager(manager);
}

// destroy a manager
void BON_Manager_Destroy(bon::IManager* manager)
{
	delete manager;
}

// get engine instance
bon::engine::Engine* BON_GetEngine()
{
	return &bon::_GetEngine();
}

// get Game manager.
bon::IGame* BON_Engine_Game()
{
	return &bon::_GetEngine().Game();
}

// get Assets manager.
bon::IAssets* BON_Engine_Assets()
{
	return &bon::_GetEngine().Assets();
}

// get Gfx manager.
bon::IGfx* BON_Engine_Gfx()
{
	return &bon::_GetEngine().Gfx();
}

// get Sfx manager.
bon::ISfx* BON_Engine_Sfx()
{
	return &bon::_GetEngine().Sfx();
}

// get Input manager.
bon::IInput* BON_Engine_Input()
{
	return &bon::_GetEngine().Input();
}

// get Log manager.
bon::ILog* BON_Engine_Log()
{
	return &bon::_GetEngine().Log();
}

// get Diagnostics manager.
bon::IDiagnostics* BON_Engine_Diagnostics()
{
	return &bon::_GetEngine().Diagnostics();
}

// get manager by name.
bon::IManager* BON_Engine_GetManager(const char* id)
{
	return bon::_GetEngine().GetManagerById(id);
}

// get engine current state
BON_Engine_States BON_Engine_CurrentState()
{
	return (BON_Engine_States)(bon::_GetEngine().CurrentState());
}

// get updates count.
unsigned long long BON_Engine_UpdatesCount()
{
	return bon::_GetEngine().UpdatesCount();
}

// get fixed updates count.
unsigned long long BON_Engine_FixedUpdatesCount()
{
	return bon::_GetEngine().FixedUpdatesCount();
}

// get if engine is destroyed.
BON_DLLEXPORT bool BON_Engine_Destroyed()
{
	return bon::_GetEngine().Destroyed();
}

// get if engine is running.
BON_DLLEXPORT bool BON_Engine_Running()
{
	return bon::_GetEngine().Running();
}

// get fixed updates interval.
double BON_Engine_GetFixedUpdatesInterval()
{
	return bon::_GetEngine().FixedUpdatesInterval;
}

// set fixed updates interval.
void BON_Engine_SetFixedUpdatesInterval(double value)
{
	bon::_GetEngine().FixedUpdatesInterval = value;
}