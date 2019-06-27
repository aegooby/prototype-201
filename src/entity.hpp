
#pragma	once
#include	"__common.hpp"
#include	"renderer.hpp"
#include	"component.hpp"
#include	<unordered_map>

__begin_ns_td

class	entity
{
protected:
	std::unordered_map<std::string, std::unique_ptr<component>>	__components;
public:
	entity() = default;
	virtual ~entity() = 0;
	inline __attribute__((always_inline))
	void	add_component(std::unique_ptr<component>&& component)
	{
		
	}
};

entity::~entity() = default;

class	actor : public entity
{
protected:
public:
};

class	character : public actor
{
protected:
public:
	character() = default;
	virtual ~character() = default;
};

__end_ns_td
