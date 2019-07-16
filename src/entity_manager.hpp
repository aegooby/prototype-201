
#pragma	once
#include	"__common.hpp"
#include	"ecs_common.hpp"
#include	"world.hpp"
#include	<unordered_map>

__begin_ns_td

class	entity_manager
{
public:
	std::unordered_map<id_t, std::unique_ptr<entity>>	entities;
protected:
	size_t	__entityc = 0;
	class world&	world;
public:
	entity_manager(class world& world) : world(world) {  }
	~entity_manager() = default;
	void	add_entity(const std::string&);
	void	remove_entity(id_t);
};

__end_ns_td
