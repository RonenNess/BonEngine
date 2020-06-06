#include <_CAPI/CAPI_Managers_Diagnostics.h>
#include <BonEngine.h>

// Get counter value.
int64_t BON_Diagnostics_GetCounter(int id)
{
	return bon::_GetEngine().Diagnostics()._GetCounter(id);
}

// Increase counter value.
void BON_Diagnostics_IncreaseCounter(int id, int amount)
{
	bon::_GetEngine().Diagnostics()._IncreaseCounter(id, amount);
}

// Reset counter value.
void BON_Diagnostics_ResetCounter(int id)
{
	bon::_GetEngine().Diagnostics()._ResetCounter(id);
}