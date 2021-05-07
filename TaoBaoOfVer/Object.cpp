#include "Object.h"

Object::Object(string str)
{
}

Object::Object(istream& input)
{
}

string Object::turnIntoString() const
{
	return "object: "+to_string(ID);
}

idType Object::id() const
{
	return ID;
}
