
#pragma	once
#include	"__common.hpp"
#include	"system.hpp"
#include	"component.hpp"
#include	"ecs_common.hpp"
#include	"state.hpp"
#include	<typeinfo>
#include	<typeindex>
#include	<unordered_map>
#include	<vector>

__begin_ns_td

class	entity
{
public:
	class world&	world;
	system_flag		flag;
public:
	const id_t			id;
	const entity_type	type;
protected:
	std::unique_ptr<component>&	__component(std::type_index);
	void	__add_component(std::unique_ptr<class component>&&, std::type_index);
	void	__remove_component(std::type_index);
public:
	entity(const id_t, const entity_type, class world&);
	virtual ~entity() = default;
	template	<typename component_type>
	component_type&	component()
	{
		return *static_cast<component_type*>(__component(typeid(component_type)).get());
	}
	template	<typename component_type, typename ... types>
	void	add_component(types&& ... args)
	{
		__add_component(std::make_unique<component_type>(*this, std::forward<types>(args)...), typeid(component_type));
	}
	template	<typename component_type>
	void	remove_component()
	{
		__remove_component(typeid(component_type));
	}
	bool	operator ==(const entity&);
	
	// Preventing copying and moving
	entity(const entity&) = delete;
	entity(entity&&) = delete;
	entity&	operator =(const entity&) = delete;
	entity&	operator =(entity&&) = delete;
};

__end_ns_td
