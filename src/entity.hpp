
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
	std::unordered_map<std::string, std::unique_ptr<component>>	__components;
public:
	entity(td::event_handler& event_handler) : event_handler(event_handler) {  }
	virtual ~entity() = 0;
	inline __attribute__((always_inline))
	void	add_component(std::unique_ptr<component>&& component)
	{
		using ptr = std::unique_ptr<td::component>;
		__components.emplace(component->id(), std::forward<ptr>(component));
	}
	inline __attribute__((always_inline))
	void	remove_component(const std::string& id)
	{
		__components.erase(id);
	}
};

class	actor : public entity
{
public:
	using __base = entity;
	std::unique_ptr<render_component>	render = std::make_unique<render_component>(*this);
protected:
public:
	actor(td::event_handler& event_handler) : __base(event_handler) {  }
	virtual ~actor() = default;
};

class	character : public actor
{
public:
	using __base = actor;
protected:
public:
	character(td::event_handler& event_handler) : __base(event_handler) {  }
	virtual ~character() = default;
};

class	player : public character
{
public:
	using __base = character;
public:
	player(td::event_handler& event_handler) : __base(event_handler) {  }
	std::unique_ptr<input_component>	render = std::make_unique<input_component>(*this);
};

__end_ns_td
