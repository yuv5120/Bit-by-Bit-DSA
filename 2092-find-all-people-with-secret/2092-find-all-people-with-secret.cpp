class Solution {
public:
 using int1=pair<int, int>;
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        vector<vector<int1>> adj(n);
        for(auto& meet: meetings){
            int x=meet[0], y=meet[1], time=meet[2];
            adj[x].emplace_back(time, y);
            adj[y].emplace_back(time, x);
        }
        vector<int> known(n, INT_MAX);
        vector<int> list;
        priority_queue<int1, vector<int1>, greater<int1>> pq;
        pq.emplace(0, 0);
        pq.emplace(0, firstPerson);
        while(!pq.empty()){
            auto [s, x]=pq.top();
            pq.pop();
            if (known[x]!=INT_MAX) continue;
            list.push_back(x);
            known[x]=s;
            for(auto& [t, y]: adj[x]){
                if (known[y]!=INT_MAX ||t<s) continue;
                pq.emplace(t, y);
            
            }
        }
        
        return list;
    }
};