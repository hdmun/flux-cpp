#ifndef _FLUXCPP_DISPATCHER_HPP_
#define _FLUXCPP_DISPATCHER_HPP_

#include <memory>
#include <concurrent_unordered_map.h>
#include <concurrent_queue.h>
#include <cstdint>

#include "fluxcpp/store.hpp"
#include "fluxcpp/action.hpp"

namespace fluxcpp
{

class Dispatcher
{
    using ActionId = std::size_t;

public:

    template<typename T>
    void Listen(std::function<void(T*)> handler)
    {
        // TODO : 컴파일 타임에 계산하도록 수정
        auto typeHashId = typeid(T).hash_code();

        auto itStore = _stores.find(typeHashId);
        if (_stores.end() == itStore)
        {
            std::unique_ptr<StoreContainer<T> > store = std::make_unique<StoreContainer<T> >();
            store->Listen(handler);
            _stores[typeHashId] = std::move(store);
        }
        else
        {
            // TODO : 추상화 하지 않고 사용하는 방법이 없을까?
            StoreContainer<T>* store = static_cast<StoreContainer<T>*>(itStore->second.get());
            // store.Listen(handler);
        }
    }

    template<typename T>
    void Fire(std::shared_ptr<T> payload)
    {
        // TODO : 컴파일 타임에 계산하도록 수정
        auto typeHashId = typeid(T).hash_code();

        auto iter = _stores.find(typeHashId);
        if (iter == _stores.end())
            return;

        auto store = iter->second.get();
        // 람다로 한 번 말기
        auto actoin = [store, payload]()
        {
            store->Dispatch(std::move(payload));
        };
        _actions.push(std::move(actoin));
    }

    void DispatchAll()
    {
        // 호출 시점 횟수 만큼 루프
        auto count = _actions.unsafe_size();
        for (auto i = 0; i < count; ++i)
        {
            std::function<void()> action;
            _actions.try_pop(action);
            action();
        }
    }

private:
    concurrency::concurrent_unordered_map<
        ActionId, std::unique_ptr<IStoreContainer> > _stores;
    concurrency::concurrent_queue<std::function<void()> > _actions;
};

} // end of namespace fluxcpp
#endif // _FLUXCPP_DISPATCHER_HPP_