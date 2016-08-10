#include "Property.h"

Property::Property(bool b, int id)
{
	isSolid = b;
	tileID = id;
}


Property::~Property()
{
	isSolid = NULL;
	tileID = NULL;
}


bool Property::checkSolid()
{
	return isSolid;
}

int Property::getTileID()
{
	return tileID;
}