
#pragma	once
#include	"__common.hpp"
#include	"component.hpp"
#include	"entity.hpp"
#include	<unordered_map>

__begin_ns_td

class	component_manager
{
public:
	virtual ~component_manager() = default;
	virtual std::unique_ptr<component>&	component(entity&) = 0;
	virtual void	add_component(entity&, std::unique_ptr<class component>&&) = 0;
	virtual void	remove_component(entity&) = 0;
};

template	<typename component_type>
class	component_manager_template : public component_manager
{
public:
	using component_t = component_type;
	using index_t = size_t;
	std::vector<std::unique_ptr<class component>>	components;
protected:
	std::unordered_map<id_t, index_t>	__entity_map;
public:
	virtual ~component_manager_template() = default;
	virtual std::unique_ptr<class component>&	component(entity& entity)
	{
		if (!__entity_map.count(entity.id()))
			throw std::runtime_error("Entity does not have requested component");
		return components.at(__entity_map.at(entity.id()));
	}
	virtual void	add_component(entity& entity, std::unique_ptr<class component>&& component)
	{
		if (__entity_map.count(entity.id()))
			throw std::runtime_error("Duplicate component");
		__entity_map.emplace(entity.id(), components.size());
		components.emplace_back(std::forward<std::unique_ptr<class component>>(component));
	}
	virtual void	remove_component(entity& entity)
	{
		components.erase(components.begin() + __entity_map.at(entity.id()));
		__entity_map.erase(entity.id());
	}
};

class	render_manager : public component_manager_template<render_component>
{
public:
	virtual ~render_manager() = default;
};
class	transform_manager : public component_manager_template<transform_component>
{
public:
	virtual ~transform_manager() = default;
};


class	collision_manager : public component_manager_template<collision_component>
{
private:
	int left_A, left_B;
	int right_A, right_B;
	int xcenter_A = 0;
	int xcenter_B = 0;
	int ytopcenter_A = 0;
	int ytopcenter_B = 0;
	int ybotcenter_A = 0;
	int ybotcenter_B = 0;

	int xdist = abs(xcenter_B - xcenter_A);


	//if capsule B is above capsule A
	int distsquared1() {
		int ydist = ybotcenter_B - ytopcenter_A;
		return (xdist*xdist) + (b*b);
	}

	//if capsule A is above capsule B
	int distsquared2() {
		int ydist = ybotcenter_A - ytopcenter_B;
		return (xdist*xdist) + (b*b);
	}

public:
	bool collisiondetect(class collision_component& a, class collision_component& b) {  
		leftA = a.x;
		leftB = b.x;
		rightA = a.x + a.width;
		rightB = b.x + b.width;
		xcenter_A = a.x + a.radius;
		xcenter_B = b.x + b.radius;
		ytopcenter_A = a.y + a.height;
		ytopcenter_B = b.y + b.height;
		ybotcenter_A = a.y;
		ybotcenter_B = b.y;

		if (rightA >= leftB) {
			return true;
		}
		if (bottomA <= bottomB) {
			return true;
		}
		if (distsquared1() <= (a.radius + b.radius) * (a.radius + b.radius)) {
			return true;
		}
		if (distsquared2() <= (b.topcenter + a.botcenter) * (b.topcenter + a.botcenter)) {
			return true;
		}
		else {
			return false;
		}
	}

	
	virtual ~collision_manager() = default;
};
class	input_manager : public component_manager_template<input_component>
{
public:
	virtual ~input_manager() = default;
};
class	state_manager : public component_manager_template<state_component>
{
public:
	virtual ~state_manager() = default;
};

__end_ns_td
