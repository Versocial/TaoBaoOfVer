#include "Object.h"

Object::Object()
{
}

Object::Object(idType id)
{
	this->ID = id;
}

Object::~Object()
{
}


idType Object::id() const
{
	return ID;
}
