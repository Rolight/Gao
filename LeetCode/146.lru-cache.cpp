#include <list>
#include <unordered_map>

using std::list;
using std::unordered_map;

struct Node {
    int key, value;
    Node(int key, int value) : key(key), value(value) {}
};

class LRUCache {
   public:
    list<Node> l;
    unordered_map<int, list<Node>::iterator> mp;
    int cap;

    LRUCache(int capacity) { this->cap = capacity; }

    int get(int key) {
        if (mp.count(key) == 0) return -1;
        list<Node>::iterator ret = mp[key];
        int value = ret->value;

        Node newNode(key, value);
        l.erase(ret);
        l.push_back(newNode);
        ret = l.end();
        ret--;
        mp[key] = ret;

        return value;
    }

    void put(int key, int value) {
        if (l.size() == cap && mp.count(key) == 0) {
            list<Node>::iterator ret = l.begin();
            mp.erase(ret->key);
            l.erase(ret);
        }
        if (mp.count(key) != 0) {
            list<Node>::iterator ret = mp[key];
            l.erase(ret);
        }
        Node newNode(key, value);
        l.push_back(newNode);
        list<Node>::iterator ret = l.end();
        ret--;
        mp[key] = ret;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */