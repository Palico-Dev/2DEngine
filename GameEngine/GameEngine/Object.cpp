#include "EngineCore.h"
#include "Object.h"

IMPLEMENT_ABSTRACT_CLASS(Object)

void Object::Initialize()
{
	if(initialized)
		return;

	UUID _uid;
	CreateUUID(&_uid);

	uid = GUIDToSTRCODE(_uid);
	guid = GUIDTostring(_uid);

	initialized = true;
}

void Object::Destroy()
{
	if (!initialized)
		return;
	initialized = false;
}

void Object::Load(json::JSON& jsonData)
{
}