
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
	virtual ~entity() = default;
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
	std::unique_ptr<render_component>	render = std::make_unique<render_component>();
protected:
public:
	actor() = default;
	virtual ~actor() = default;
};

class	character : public actor
{
protected:
public:
	character() = default;
	virtual ~character() = default;
};

class	player : public character
{
public:
	std::unique_ptr<input_component>	render = std::make_unique<input_component>();
};

__end_ns_td
