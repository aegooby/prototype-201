
#pragma	once
#include	"__common.hpp"

__begin_ns_td

template	<typename value_type, size_t rows, size_t cols>
class	matrix;

template	<typename value_type, size_t dim>
class	vector;

template	<typename value_type, size_t dim>
class	vertex;

template	<typename value_type, size_t __size>
class	st_array;

template	<typename value_type, size_t rows, size_t columns>
class	st_table;

template	<typename value_type, size_t __size>
class	array;

template	<typename value_type, size_t rows, size_t cols>
class	table;

class	window;
class	mouse;
class	clock;
class	newton;
class	keyboard;
class	engine;
class	entity;
class	component;
class	render_component;
class	transform_component;
class	collision_component;
class	renderer;
class	sprite_base;
class	sprite;
class	sprite_flipbook;
class	render_component;
class	event_manager;
class	event;
class	action_event;
class	world;
class	system;
class	entity_manager;
class	render_manager;
class	transform_manager;
class	collision_manager;

__end_ns_td
