#pragma once
#include <typeindex>
#include <typeinfo>
#include <vector>
#include <memory>

//the point of this class is 'simple'
//we have to be able to store a vector of component vectors.
//aka, we don't specifically know how many components we will have.
//but we have to be able to access them by their type, probably best done through hash codes.
//in any case, we =need= type safety to ensure sanity, which means we'll need some polymorphism
//to deal with the base storage.
//To get the right type we can compare with the requested type, determine its hash code, and then see if we have the type.
//if that fails we can return null.
//to convert the base class to a derived version dynamic_cast() probably will work best.

class ComponentVecBase
{
public:
	type_index type;
	ComponentVecBase() : type(type_index(typeid(void)))
	{};
	
	//this is a self reminder, one, if you are going to edit the sizes of derived classes vs the base class
	//or require special handling, make the deconstructor of the base class(es) virtual
	//two, it's required that there is at least one virtual method for dynamic_cast<> to compile
	//this solves both of those issues without requiring a pointless virtual method.
	virtual ~ComponentVecBase(){};
};
template<typename component>
class ComponentVec : public ComponentVecBase
{
public:
	
	std::vector<component> components;

	ComponentVec() : ComponentVecBase()
	{
		type = type_index(typeid(component));
	}
	~ComponentVec(){};

};
class ComponentStorage
{
private:
	//we need a vector of polymorphic types.
	//I don't want to worry about destruction of the type, so we could use shared/unique pointers.
	//nothing else should -ever- own this, but it should be editable by others.
	//unique_ptr<> sounds best so far, so that's whats going to be used.

	std::vector<std::unique_ptr<ComponentVecBase>> storage;
public:
	ComponentStorage(){};
	~ComponentStorage(){};


	template<typename T>
	ComponentVec<T>* GetStorage()
	{
		//search the sub storage and determine if the component type matches, return that if it does.
		for (auto& sub_vec : storage)
		{
			if (sub_vec->type == type_index(typeid(T)))
			{
				return dynamic_cast<ComponentVec<T>*>(sub_vec.get());
			}
		}
		//we couldn't find anything.
		return nullptr;
	}
	//returns 0 on successfully adding storage.
	//returns -1 on attempting to add duplicate storage type.
	template<typename T>
	int AddStorage()
	{
		for (auto& sub_vec : storage)
		{
			if (sub_vec->type == type_index(typeid(T)))
				return -1;
		}
		storage.push_back(std::unique_ptr<ComponentVecBase>(new ComponentVec<T>()));
		return 0;
	}
};

