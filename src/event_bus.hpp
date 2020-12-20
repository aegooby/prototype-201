
#pragma once
#include "__common.hpp"
#include "event.hpp"

namespace p201
{

class function_handler
{
    protected:
    virtual void call(std::unique_ptr<event>&& event) = 0;

    public:
    virtual ~function_handler() = default;
    virtual void exec(std::unique_ptr<event>&& event)
    {
        call(std::forward<std::unique_ptr<class event>>(event));
    }
};

template<typename system_type, typename event_type>
class function_handler_sp : public function_handler
{
    public:
    using event_t  = event_type;
    using system_t = system_type;
    typedef void (system_t::*function_t)(event_t&);

    private:
    system_t&  __system;
    function_t __function;

    protected:
    virtual void call(std::unique_ptr<event>&& event) override
    {
        (__system.*__function)(*static_cast<event_t*>(event.get()));
    }

    public:
    function_handler_sp(system_t& system, function_t function)
        : __system(system), __function(function)
    {
    }
    virtual ~function_handler_sp() = default;
};

class event_bus
{
    public:
    using list_t = std::list<std::unique_ptr<function_handler>>;

    protected:
    std::unordered_map<std::type_index, std::unique_ptr<list_t>> __subscribers;
    class world&                                                 world;

    public:
    event_bus(class world& world) : world(world) { }
    ~event_bus() = default;
    template<typename event_type, typename... types>
    void publish(types&&... args)
    {
        auto& handlers = __subscribers.at(typeid(event_type));
        if (!handlers) return;
        for (auto& handler : *handlers)
        {
            if (handler)
                handler->exec(
                    std::make_unique<event_type>(std::forward<types>(args)...));
        }
    }
    template<typename system_type, typename event_type>
    void subscribe(system_type& system,
                   void (system_type::*function)(event_type&))
    {
        if (!__subscribers.count(typeid(event_type)))
        {
            __subscribers.emplace(typeid(event_type),
                                  std::make_unique<list_t>());
        }
        auto& handlers = __subscribers.at(typeid(event_type));
        handlers->emplace_back(
            std::make_unique<function_handler_sp<system_type, event_type>>(
                system, function));
    }
};

} // namespace p201
