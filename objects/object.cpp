#include "object.h"

Object::Object()
	: position(), size()
{
}

Object::Object(Vector2 initPosition, Vector2 initSize)
	: position{initPosition}, size{initSize}
{
}

Object::~Object()
{
}

Vector2 Object::GetPosition() { return position; }
Vector2 Object::GetSize() { return size; }

void Object::SetPosition(	Vector2 newPosition) { position = newPosition; }
void Object::SetSize(Vector2 newSize) { size = newSize; }
