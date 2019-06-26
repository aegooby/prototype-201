
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
