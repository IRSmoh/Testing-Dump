#pragma once
#include "ComponentStorage.h"
#include <tuple>
class ComponentWorld
{
public:
	ComponentStorage components;
	ComponentWorld()
	{
		components.AddStorage<int>();
		components.AddStorage<float>();
	}
	~ComponentWorld(){};

};

