
#pragma once
#include "../__common.hpp"
#include "../key.hpp"
#include "../physx.hpp"
#include "../util.hpp"

#include <bitset>
#include <memory>
#include <string>
#include <typeindex>
#include <vector>

namespace p201
{
/**
 * @brief Components contain data only. There's no reason for a component to
 *        contain anything other than a constructor or destructor. I've broken
 *        that rule though because I'm an idiot. So this is why I have to go
 *        through this shit and add dumb ass documentation because I don't know
 *        what the fuck I'm doing.
 */
struct component
{
    static constexpr std::size_t flag      = 0;
    static constexpr std::size_t flag_bits = 32;

    class entity& entity;

    component(class entity& entity) : entity(entity) { }
    virtual ~component() = 0;

    component(const component&) = delete;
    component(component&&)      = delete;
    component& operator=(const component&) = delete;
    component& operator=(component&&) = delete;
};

inline component::~component() = default;

namespace components
{
struct render : public component
{
    using __base = component;

    static constexpr std::size_t flag = 1;

    /** @brief Whether or not to display the sprite on rendering. */
    bool visible = true;
    /** @brief Whether to transform the rendering to isometric. */
    bool iso = true;
    /** @brief Whether to camera transform the sprite. */
    bool camera = true;
    /** @brief Family of flipbooks associated with this component. */
    std::string family = "unknown";
    /** @brief Floating point rect that textures are rendered onto. */
    SDL_FRect rect = { .x = 0.0f, .y = 0.0f, .w = 0.0f, .h = 0.0f };
    /** @brief Portion of source rectangle to be rendered. */
    SDL_Rect srcrect = { .x = 0, .y = 0, .w = 0, .h = 0 };
    /** @brief Texture rendered onto rect. */
    SDL_Texture* texture = nullptr;
    /** @brief The displacement factor of the sprite from its center point. */
    vector_2 offset = vector_2(0.0f, 0.0f);

    render(class entity& entity) : __base(entity) { }
    virtual ~render() override = default;
};

struct transform : public component
{
    using __base = component;

    static constexpr std::size_t flag = 2;

    /** @brief Used in direction bitset. */
    enum
    {
        north = 0,
        south = 1,
        east  = 2,
        west  = 3,
    };

    /** @brief Previous coordinate used to interpolate in updates. */
    vector_3 lerp = vector_3(0.0f, 0.0f, 0.0f);
    /** @brief Game coordinate position (not isometric position). */
    vector_3 position = vector_3(0.0f, 0.0f, 0.0f);
    /** @brief Direction the entity is facing (not always used). */
    std::bitset<4> direction;

    transform(class entity& entity) : __base(entity) { }
    virtual ~transform() override = default;
};

struct physics : public component
{
    using __base = component;

    static constexpr std::size_t flag = 3;

    enum shape : std::size_t
    {
        undefined = 0,
        capsule   = 1,
        box       = 2,
    };

    bool  dynamic = true;
    float sf      = 0.0f;
    float df      = 0.0f;
    float e       = 0.0f;
    float density = 0.0f;
    shape shape   = undefined;
    union shape_param
    {
        struct
        {
            float r;
            float hh;
        } capsule;
        struct
        {
            float hx;
            float hy;
            float hz;
        } box;
        shape_param()  = default;
        ~shape_param() = default;
    } shape_params;

    px::rigid_actor* actor = nullptr;

    physics(class entity& entity) : __base(entity) { }
    virtual ~physics() override = default;

    void init(px::scene& scene)
    {
        auto material = px::sdk.main->createMaterial(sf, df, e);
        if (!material) throw std::runtime_error("Failed to create material");
        auto transform = px::PxTransform(px::PxVec3(0, 0, 0));
        /** @todo Temporary values */
        /** @todo Add switch for shape types */
        auto create = [this, &transform,
                       &material](const auto& geometry) -> px::rigid_actor*
        {
            if (dynamic)
                return px::PxCreateDynamic(*px::sdk.main, transform, geometry,
                                           *material, density);
            else
                return px::PxCreateStatic(*px::sdk.main, transform, geometry,
                                          *material);
        };
        switch (shape)
        {
            case capsule:
            {
                actor = create(px::PxCapsuleGeometry(shape_params.capsule.r,
                                                     shape_params.capsule.hh));
                break;
            }
            case box:
            {
                actor = create(px::PxBoxGeometry(shape_params.box.hx,
                                                 shape_params.box.hy,
                                                 shape_params.box.hz));
                break;
            }
            default:
                break;
        }
        scene.main->addActor(*actor);
    }
};

struct character : public component
{
    using __base = component;

    static constexpr std::size_t flag = 4;

    character(class entity& entity) : __base(entity) { }
    virtual ~character() override = default;

    px::controller* controller = nullptr;
    vector_3        accel      = vector_3(0.0f, 0.0f, 0.0f);
    vector_3        velocity   = vector_3(0.0f, 0.0f, 0.0f);

    void init(px::controller_manager& controller_manager, physics& physics)
    {
        px::PxCapsuleControllerDesc desc;

        auto material =
            px::sdk.main->createMaterial(physics.sf, physics.df, physics.e);
        /** @todo Temporary values */
        desc.radius      = physics.shape_params.capsule.r;
        desc.height      = physics.shape_params.capsule.hh;
        desc.stepOffset  = 0.01f;
        desc.density     = physics.density;
        desc.material    = material;
        desc.upDirection = px::vector_3(0, 0, 1);

        controller = controller_manager.main->createController(desc);
    }
};

struct input : public component
{
    using __base = component;

    static constexpr std::size_t flag = 5;

    input(class entity& entity) : __base(entity) { }
    virtual ~input() override = default;
};

struct animation : public component
{
    using __base = component;

    static constexpr std::size_t flag = 6;

    std::string name      = "default";
    std::size_t frame     = 0;
    std::size_t index     = 0;
    float       fps       = 0.0f;
    bool        interrupt = false;
    bool        loop      = true;

    animation(class entity& entity) : __base(entity) { }
    virtual ~animation() override = default;
};

struct camera_focus : public component
{
    using __base = component;

    static constexpr std::size_t flag = 7;

    camera_focus(class entity& entity) : __base(entity) { }
    virtual ~camera_focus() override = default;
};

struct health : public component
{
    using __base = component;

    static constexpr std::size_t flag = 8;

    float hp         = 0.0f;
    float max_hp     = 0.0f;
    float shield     = 0.0f;
    float max_shield = 0.0f;

    health(class entity& entity) : __base(entity) { }
    virtual ~health() override = default;
};

struct hud : public component
{
    using __base = component;

    static constexpr std::size_t flag = 9;

    hud(class entity& entity) : __base(entity) { }
    virtual ~hud() override = default;
};
} // namespace components
} // namespace p201
