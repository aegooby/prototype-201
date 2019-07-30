
#pragma	once
#include	"__common.hpp"
#include	<typeindex>
#include	<unordered_map>
#include	<list>

__begin_ns_td

class	event
{
public:
	event() = default;
	virtual ~event() = 0;
};

class	animation_event : public event
{
public:
	
	class entity&	entity;
	std::string		name;
public:
	animation_event(class entity& entity, const std::string& name) : entity(entity), name(name) {  }
	virtual ~animation_event() = default;
};

class	animation_complete_event : public event
{
public:
	class entity&	entity;
	std::string		name;
public:
	animation_complete_event(class entity& entity, const std::string& name) : entity(entity), name(name) {  }
	virtual ~animation_complete_event() = default;
};

class	collision_event : public event
{
public:
	class entity&	entity_a;
	class entity&	entity_b;
public:
	collision_event(class entity& entity_a, class entity& entity_b) : entity_a(entity_a), entity_b(entity_b) {  }
	virtual ~collision_event() = default;
};

__end_ns_td
