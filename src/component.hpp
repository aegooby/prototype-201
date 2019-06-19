
#pragma	once
#include	"__common.hpp"

__begin_ns_td

class	component
{
public:
	component() = default;
	virtual ~component() = 0;
};

class	sprite_component : public component
{
public:
	sprite_component() = default;
	virtual ~sprite_component() = default;
};

class	physics_component : public component
{
public:
	physics_component() = default;
	virtual ~physics_component() = default;
};

__end_ns_td
