#pragma once
#include <EventDefs.hpp>
#include <unordered_map>
#include <vector>

// 1st arg - user data
// 2nd arg - event data
typedef void (*EventCallback)(void*, void*);

class PubSub {
public:
    struct SubscriptionParams {
        EventCallback callback;
        void* args;
    };

private:
    struct InternalSubParams {
        int id;
        EventCallback callback;
        void* args;
    };

public:
    static PubSub& Instance() {
        static PubSub instance;
        return instance;
    }

    PubSub(const PubSub& pubsub) = delete;

    int Subscribe(EventIds id, EventCallback callback, void* args);
    int Subscribe(EventIds id, const SubscriptionParams& params);
    void UnSubscribe(EventIds eventId, int subscriptionId);
    void Publish(EventIds id, void* eventData = nullptr);

private:
    PubSub() {}

private:
    static int subscribersId;
    std::unordered_map<EventIds, std::vector<InternalSubParams>> subscribers;
};
