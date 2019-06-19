
#pragma	once
#include	"__common.hpp"
#include	"renderer.hpp"
#include	"component.hpp"

__begin_ns_td

class	entity
{
protected:
	std::vector<std::unique_ptr<component>>	__components;
public:
	entity() = default;
	virtual ~entity() = default;
};

class	actor : public entity
{
	
};

class	character : public entity
{
protected:
	using __base = entity;
	float		__vx = 0.0f, __vy = 0.0f;
	SDL_Rect	__rect;
public:
	character() = default;
	virtual ~character() = default;
};

__end_ns_td
