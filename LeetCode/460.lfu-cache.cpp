/*
 * [460] LFU Cache
 *
 * https://leetcode.com/problems/lfu-cache/description/
 *
 * algorithms
 * Hard (25.09%)
 * Total Accepted:    21.3K
 * Total Submissions: 84.2K
 * Testcase Example:
 * '["LFUCache","put","put","get","put","get","get","put","get","get","get"]\n[[2],[1,1],[2,2],[1],[3,3],[2],[3],[4,4],[1],[3],[4]]'
 *
 * Design and implement a data structure for Least Frequently Used (LFU) cache.
 * It should support the following operations: get and put.
 *
 *
 *
 * get(key) - Get the value (will always be positive) of the key if the key
 * exists in the cache, otherwise return -1.
 * put(key, value) - Set or insert the value if the key is not already present.
 * When the cache reaches its capacity, it should invalidate the least
 * frequently used item before inserting a new item. For the purpose of this
 * problem, when there is a tie (i.e., two or more keys that have the same
 * frequency), the least recently used key would be evicted.
 *
 *
 * Follow up:
 * Could you do both operations in O(1) time complexity?
 *
 * Example:
 *
 * LFUCache cache = new LFUCache( 2 <capacity>);
 *
 * cache.put(1, 1);
 * cache.put(2, 2);
 * cache.get(1);       // returns 1
 * cache.put(3, 3);    // evicts key 2
 * cache.get(2);       // returns -1 (not found)
 * cache.get(3);       // returns 3.
 * cache.put(4, 4);    // evicts key 1.
 * cache.get(1);       // returns -1 (not found)
 * cache.get(3);       // returns 3
 * cache.get(4);       // returns 4
 *
 *
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LFUCache {
    struct Value {
        int value;
        int times;
        list<int>::iterator list_iter;
    };

    struct Bucket {
        list<int> keys;
        list<int>::iterator list_iter;
    };

    unordered_map<int, Bucket> buckets;
    unordered_map<int, Value> KV;
    list<int> values;

    int capacity;

    void incr(int key_id) {
        Value &val = KV[key_id];
        Bucket &bucket = buckets[val.times];

        Bucket *new_bucket;
        // check if new bucket exists
        if (buckets.count(val.times + 1) == 0) {
            // create new bucket
            list<int>::iterator new_bucket_iter = bucket.list_iter;
            new_bucket_iter = values.insert(++new_bucket_iter, val.times + 1);
            new_bucket = &buckets[val.times + 1];
            new_bucket->list_iter = new_bucket_iter;
        } else {
            new_bucket = &buckets[val.times + 1];
        }
        // remove from old bucket
        bucket.keys.erase(val.list_iter);
        // check if need to delete old bucket
        if (bucket.keys.size() == 0) {
            // delete old bucket
            values.erase(bucket.list_iter);
            buckets.erase(val.times);
        }
        ++val.times;
        // add to new bucket
        new_bucket->keys.push_front(key_id);
        val.list_iter = new_bucket->keys.begin();
    }

    void free_up() {
        int minimal_times = *values.begin();
        Bucket &bucket = buckets[minimal_times];
        int free_up_key = bucket.keys.back();
        bucket.keys.pop_back();
        KV.erase(free_up_key);
        // check if need to delete bucket
        if (bucket.keys.size() == 0) {
            values.erase(bucket.list_iter);
            buckets.erase(minimal_times);
        }
    }

    void add_new_key(int key_id, int value) {
        Bucket *bucket;
        if (buckets.count(1) == 0) {
            bucket = &buckets[1];
            values.push_front(1);
            bucket->list_iter = values.begin();
        } else {
            bucket = &buckets[1];
        }
        bucket->keys.push_front(key_id);
        Value &val = KV[key_id];
        val.list_iter = bucket->keys.begin();
        val.times = 1;
        val.value = value;
    }

   public:
    LFUCache(int capacity) : capacity(capacity) {
        buckets.clear();
        KV.clear();
        values.clear();
    }

    int get(int key) {
        if (this->capacity == 0) return -1;
        if (KV.count(key) == 0) return -1;
        incr(key);
        return KV[key].value;
    }

    void put(int key, int value) {
        if (this->capacity == 0) return;
        if (KV.count(key) == 0) {
            if (KV.size() == this->capacity) {
                free_up();
            }
            add_new_key(key, value);
        } else {
            incr(key);
            KV[key].value = value;
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */