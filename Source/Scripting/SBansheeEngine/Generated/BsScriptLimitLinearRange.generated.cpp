#include "BsScriptLimitLinearRange.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "BsScriptSpring.generated.h"
#include "BsScriptSpring.generated.h"

namespace bs
{
	ScriptLimitLinearRange::ScriptLimitLinearRange(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{ }

	void ScriptLimitLinearRange::initRuntimeData()
	{ }

	MonoObject*ScriptLimitLinearRange::box(const __LimitLinearRangeInterop& value)
	{
		return MonoUtil::box(metaData.scriptClass->_getInternalClass(), (void*)&value);
	}

	__LimitLinearRangeInterop ScriptLimitLinearRange::unbox(MonoObject* value)
	{
		return *(__LimitLinearRangeInterop*)MonoUtil::unbox(value);
	}

	LimitLinearRange ScriptLimitLinearRange::fromInterop(const __LimitLinearRangeInterop& value)
	{
		LimitLinearRange output;
		output.lower = value.lower;
		output.upper = value.upper;
		output.contactDist = value.contactDist;
		output.restitution = value.restitution;
		output.spring = value.spring;

		return output;
	}

	__LimitLinearRangeInterop ScriptLimitLinearRange::toInterop(const LimitLinearRange& value)
	{
		__LimitLinearRangeInterop output;
		output.lower = value.lower;
		output.upper = value.upper;
		output.contactDist = value.contactDist;
		output.restitution = value.restitution;
		output.spring = value.spring;

		return output;
	}

}
