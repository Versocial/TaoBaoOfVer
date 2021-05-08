#include "Object.h"

Object::Object()
{
}

Object::Object(idType id)
{
	this->ID = id;
}


string Object::turnIntoString() const
{
	return "object: "+to_string(ID);
}

idType Object::id() const
{
	return ID;
}
