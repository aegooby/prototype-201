
#pragma	once
#include	"__common.hpp"
#include	"renderer.hpp"
#include	"component.hpp"
#include	<unordered_map>

__begin_ns_td

class	entity
{
public:
	td::event_handler&	event_handler;
protected:
	const std::string	__name;
public:
	entity(td::event_handler& event_handler, const std::string& name) : event_handler(event_handler), __name(name) {  }
	virtual ~entity() = 0;
	inline __attribute__((always_inline))
	const std::string& name() const
	{
		return __name;
	}
};

class	actor : public entity
{
public:
	using __base = entity;
	std::weak_ptr<render_component>	render;
protected:
public:
	actor(td::event_handler& event_handler, const std::string& name) : __base(event_handler, name) {  }
	virtual ~actor() = default;
};

class	character : public actor
{
public:
	using __base = actor;
protected:
public:
	character(td::event_handler& event_handler, const std::string& name) : __base(event_handler, name) {  }
	virtual ~character() = default;
};

class	player : public character
{
public:
	using __base = character;
public:
	player(td::event_handler& event_handler, const std::string& name) : __base(event_handler, name) {  }
//	std::unique_ptr<input_component>	input = std::make_unique<input_component>(*this);
};

__end_ns_td
