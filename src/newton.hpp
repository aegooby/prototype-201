
#pragma	once
#include	"__common.hpp"
#include	"entity.hpp"
#include	"component.hpp"

__begin_ns_td

class	newton
{
private:
protected:
public:
	newton() = default;
	~newton() = default;
	inline __attribute__((always_inline))
	void	update(std::unordered_map<std::string, std::unique_ptr<entity>>& entities)
	{
		for (auto& entity : entities)
		{
			for (auto& component : entity.second->components)
			{
				if (auto transform = memory::weak_cast<transform_component*>(component))
				{
					entity.second->position += transform->velocity;
					transform->velocity += transform->acceleration;
				}
			}
		}
	}
};

__end_ns_td
