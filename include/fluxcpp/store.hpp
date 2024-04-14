#ifndef _FLUXCPP_STORE_HPP_
#define _FLUXCPP_STORE_HPP_

#include <list>
#include <functional>

#include "fluxcpp/core/trait.hpp"
#include "fluxcpp/action.hpp"

namespace fluxcpp
{

class StoreHandler : public Trait
{
public:
    template<typename T>
    StoreHandler(T handler)
        : Trait(handler)
    {
    }

    template<typename T>
    void Invoke(T* action)
    {
        auto handler = cast<std::function<void(T*)> >();
        handler(action);
    }
};

class StoreContainer
{
public:
    template<typename T>
    void Listen(std::function<void(T*)> handler)
    {
        _handlers.push_back(StoreHandler(std::move(handler)));
    }

    template<typename T>
    void Dispatch(std::shared_ptr<T> payload)
    {
        for (auto& handler : _handlers)
        {
            handler.Invoke(payload.get());
        }
    }

private:
    std::list<StoreHandler> _handlers;
};

} // end of namespace fluxcpp
#endif // _FLUXCPP_STORE_HPP_