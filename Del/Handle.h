#pragma once
#include <typeindex>
class HandleBase
{
public:
	size_t index;
	size_t id;
	std::type_index type;
	HandleBase() : type(typeid(void*))
	{};
	virtual ~HandleBase()
	{};
	bool operator==(HandleBase right) const
	{
		return (id == right.id) && (index == right.index) && (type == right.type);
	};
	bool operator!=(HandleBase right) const
	{
		return !(*this == right);
	};
};
template<typename component>
class Handle : public HandleBase
{
	//no extra members should be allowed here
	//that way we can ignore polymorphism and just force cast to the type we want
	//so that easy overload methods work properly

	Handle() :type(typeid(component))
	{};
	~Handle()
	{};

	component* operator->() const
	{

	};
};

/*
Entity entity
entity.addcomponent<Pos>();
auto h = entity.gethandle<Pos>();
h->pos.x = 3;


*/
