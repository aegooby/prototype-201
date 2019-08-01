
#pragma	once
#include	"__common.hpp"
#include	"render_system.hpp"
#include	"point.hpp"
#include	<unordered_map>
#include	<vector>

__begin_ns_td

class	sprite
{
public:
	static const	std::unordered_map<state, std::string>	names;
	static const	std::unordered_map<std::string, state>	states;
};

struct	sprite_info
{
	const uint32_t	frames;
	const point_2	origin;
	const uint32_t	width;
	const uint32_t	height;
	sprite_info(uint32_t frames, const point_2& origin, uint32_t width, uint32_t height) : frames(frames), origin(origin), width(width), height(height) {  }
	~sprite_info() = default;
};

class	sprite_flipbook
{
public:
	uint32_t	framec = 0;
	uint32_t	index = 0;
protected:
	const std::string	__entity_name;
	const std::string	__name;
	float				__fps = 0;
public:
	const sprite_info	info;
public:
	sprite_flipbook(const std::string& entity_name, const std::string& name, float fps, const sprite_info& info) : __entity_name(entity_name), __name(name), __fps(fps), info(info)
	{
		if (__fps <= 0 || __fps > float(global::game_fps))
			throw std::runtime_error(std::string("Invalid fps, flipbook: ") + this->name());
	}
	sprite_flipbook(sprite_flipbook&& other) : __entity_name(other.__entity_name), __name(other.__name), __fps(other.__fps), info(other.info)
	{
		
	}
	sprite_flipbook&	operator =(sprite_flipbook&& other)
	{
		__fps = other.__fps;
		return *this;
	}
	virtual ~sprite_flipbook() = default;
	inline __attribute__((always_inline))
	const std::string&	name() const
	{
		return __name;
	}
	inline __attribute__((always_inline))
	const std::string&	entity_name() const
	{
		return __entity_name;
	}
	inline __attribute__((always_inline))
	void	fps(float fps)
	{
		if (__fps <= 0 || __fps > float(global::game_fps))
			throw std::runtime_error(std::string("Invalid fps, flipbook: ") + name());
		__fps = fps;
	}
	inline __attribute__((always_inline))
	float	fps() const
	{
		return __fps;
	}
	inline __attribute__((always_inline))
	size_t	frame_delay() const
	{
		return size_t(1.0f / __fps * global::game_fps);
	}
	inline __attribute__((always_inline))
	size_t	frames() const
	{
		return info.frames;
	}
	inline __attribute__((always_inline))
	float	seconds() const
	{
		return 1.0f / __fps * frames();
	}
	void	reset()
	{
		framec = 0;
		index = 0;
	}
	
	// Preventing copying
	sprite_flipbook(const sprite_flipbook&) = delete;
	sprite_flipbook&	operator =(const sprite_flipbook&) = delete;
};



__end_ns_td
