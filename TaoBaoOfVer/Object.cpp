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

istream& Object::operator>>(istream& in, Object& obj)
{
	// TODO: 在此处插入 return 语句
}
