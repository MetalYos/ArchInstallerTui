#include <PubSub.hpp>

int PubSub::subscribersId = 1;

int PubSub::Subscribe(EventIds id, EventCallback callback, void* args) {
    return Subscribe(id, { callback, args });
}

int PubSub::Subscribe(EventIds id, const SubscriptionParams& params) {
    InternalSubParams internalParams { subscribersId, params.callback, params.args };

    auto res = subscribers.find(id);
    if (res != subscribers.end()) {
        auto& subs = (*res).second;
        subs.push_back(internalParams); 
    }
    else {
        subscribers[id] = std::vector<InternalSubParams> { internalParams };
    }

    return subscribersId++;
}

void PubSub::UnSubscribe(EventIds eventId, int subscriptionId) {
    auto res = subscribers.find(eventId);
    if (res != subscribers.end()) {
        auto& subs = (*res).second;
        for (auto i = subs.begin(); i != subs.end(); ++i) {
            if ((*i).id == subscriptionId) {
                // Remove the subscriber and break out of the loop
                subs.erase(i);
            }
        }
    }
}

void PubSub::Publish(EventIds id, void* eventData) {
    auto res = subscribers.find(id);
    if (res == subscribers.end())
        return;

    auto& subs = (*res).second;
    for (auto sub : subs) {
        sub.callback(sub.args, eventData);
    }
}

