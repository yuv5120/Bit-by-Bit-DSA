#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Packet {
    int source, destination, timestamp, id;
};

class Router {
    int memoryLimit;
    queue<Packet> q;
    int nextId;
    set<tuple<int,int,int>> packetSet;
    unordered_map<int, ordered_set<pair<int,int>>> destMap;
    
public:
    Router(int memoryLimit) : memoryLimit(memoryLimit), nextId(0) { }
    
    bool addPacket(int source, int destination, int timestamp) {
        tuple<int,int,int> key = {source, destination, timestamp};
        if (packetSet.count(key))
            return false;
        if (q.size() == memoryLimit) {
            Packet front = q.front();
            q.pop();
            packetSet.erase({front.source, front.destination, front.timestamp});
            auto it = destMap.find(front.destination);
            if (it != destMap.end()) {
                it->second.erase({front.timestamp, front.id});
                if (it->second.empty())
                    destMap.erase(it);
            }
        }
        Packet newPacket {source, destination, timestamp, nextId++};
        q.push(newPacket);
        packetSet.insert(key);
        destMap[destination].insert({timestamp, newPacket.id});
        return true;
    }
    
    vector<int> forwardPacket() {
        if (q.empty())
            return {};
        Packet front = q.front();
        q.pop();
        packetSet.erase({front.source, front.destination, front.timestamp});
        auto it = destMap.find(front.destination);
        if (it != destMap.end()) {
            it->second.erase({front.timestamp, front.id});
            if (it->second.empty())
                destMap.erase(it);
        }
        return {front.source, front.destination, front.timestamp};
    }
    
    int getCount(int destination, int startTime, int endTime) {
        if (destMap.find(destination) == destMap.end())
            return 0;
        auto &os = destMap[destination];
        int countEnd = os.order_of_key({endTime + 1, 0});
        int countStart = os.order_of_key({startTime, 0});
        return countEnd - countStart;
    }
};
/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */