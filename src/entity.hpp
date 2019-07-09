
#pragma	once
#include	"__common.hpp"
#include	"renderer.hpp"
#include	"component.hpp"
#include	<unordered_map>
#include	<vector>

__begin_ns_td

class	entity
{
public:
	td::event_handler&	event_handler;
	std::vector<std::weak_ptr<component>>	components;
	vector_3	position;
protected:
	const std::string	__name;
public:
	entity(const std::string& name, const vector_3& position, td::event_handler& event_handler) : event_handler(event_handler), position(position), __name(name) {  }
	virtual ~entity() = default;
	inline __attribute__((always_inline))
	const std::string& name() const
	{
		return __name;
	}
	inline __attribute__((always_inline))
	void	add_component(std::shared_ptr<component>& component)
	{
		for (auto& weak_ptr : components)
		{
			if (weak_ptr.expired())
			{
				weak_ptr = component;
				return;
			}
		}
		components.push_back(component);
	}
	inline __attribute__((always_inline))
	void	remove_component(std::weak_ptr<component>& component)
	{
		components.erase(std::remove_if(components.begin(), components.end(), [&component](std::weak_ptr<td::component>& __component)
										{
											return &component == &__component;
										}));
	}
};


__end_ns_td
