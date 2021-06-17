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

void Object::setID(idType id)
{
	ID = id;
}


idType Object::id() const
{
	return ID;
}
