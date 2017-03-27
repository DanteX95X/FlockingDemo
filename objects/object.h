#ifndef OBJECT_H
#define OBJECT_H

#include "../utilities/vector2.h"

class Object
{
public:
	Object();
	Object(Vector2 initPosition, Vector2 initSize);
	virtual ~Object();
	
	virtual void Update() = 0;
	
	Vector2 GetPosition();
	Vector2 GetSize();
	
	void SetPosition(Vector2 newPosition);
	void SetSize(Vector2 newSize);
	
protected:
	Vector2 position;
	Vector2 size;
};

#endif //OBJECT_H