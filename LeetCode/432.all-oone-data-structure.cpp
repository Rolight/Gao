/*
 * [432] All O`one Data Structure
 *
 * https://leetcode.com/problems/all-oone-data-structure/description/
 *
 * algorithms
 * Hard (27.98%)
 * Total Accepted:    9.8K
 * Total Submissions: 35K
 * Testcase Example:  '["AllOne","getMaxKey","getMinKey"]\n[[],[],[]]'
 *
 * Implement a data structure supporting the following operations:
 *
 *
 *
 * Inc(Key) - Inserts a new key  with value 1. Or increments an existing key by
 * 1. Key is guaranteed to be a non-empty string.
 * Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise
 * decrements an existing key by 1. If the key does not exist, this function
 * does nothing. Key is guaranteed to be a non-empty string.
 * GetMaxKey() - Returns one of the keys with maximal value. If no element
 * exists, return an empty string "".
 * GetMinKey() - Returns one of the keys with minimal value. If no element
 * exists, return an empty string "".
 *
 *
 *
 *
 * Challenge: Perform all these in O(1) time complexity.
 *
 */
#include <cassert>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class AllOne {
    struct ListNode {
        unordered_set<int> keys;
        int value;

        ListNode(int value) : value(value) {}
    };

    // key name lookup table
    vector<string> int2key_table;
    unordered_map<string, int> key2int_table;
    vector<int> value;

    // bucket {value: {key_ids}}
    list<ListNode> buckets;
    typedef list<ListNode>::iterator BucketIter;
    unordered_map<int, BucketIter> value2bucket_table;

    int string2int(string &str) {
        int ret;
        if (key2int_table.count(str) == 0) {
            ret = key2int_table.size();
            key2int_table[str] = ret;
            int2key_table.push_back(str);
            value.push_back(0);
        } else {
            ret = key2int_table[str];
        }
        return ret;
    }

    string int2string(int key_id) {
        if (key_id > int2key_table.size()) return "";
        return int2key_table[key_id];
    }

    void add_new_element(int key_id) {
        if (value2bucket_table.count(1) == 0) {
            buckets.push_front(ListNode(1));
            value2bucket_table[1] = buckets.begin();
        }
        BucketIter bucket = buckets.begin();
        bucket->keys.insert(key_id);
    }

    void remove_from_bucket(BucketIter bucket, int key_id) {
        bucket->keys.erase(key_id);
        if (bucket->keys.size() == 0) {
            value2bucket_table.erase(bucket->value);
            buckets.erase(bucket);
        }
    }

    void add_to_bucket(BucketIter bucket, int key_id) {
        bucket->keys.insert(key_id);
    }

   public:
    /** Initialize your data structure here. */
    AllOne() {
        int2key_table.clear();
        key2int_table.clear();
        value.clear();
        buckets.clear();
        value2bucket_table.clear();
    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key
     * by 1. */
    void inc(string key) {
        int key_id = string2int(key);
        if (value[key_id] == 0) {
            value[key_id] = 1;
            add_new_element(key_id);
        } else {
            // find old bucket
            BucketIter old_bucket = value2bucket_table[value[key_id]];
            // incr value and add it to new bucket
            int new_value = value[key_id] + 1;
            BucketIter bucket;
            if (value2bucket_table.count(new_value) == 0) {
                BucketIter insert_pos = old_bucket;
                ++insert_pos;
                bucket = buckets.insert(insert_pos, ListNode(new_value));
                value2bucket_table[new_value] = bucket;
            } else {
                bucket = value2bucket_table[new_value];
            }
            add_to_bucket(bucket, key_id);
            // remove from old bucket and update value table
            value[key_id] = new_value;
            remove_from_bucket(old_bucket, key_id);
        }
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the
     * data structure. */
    void dec(string key) {
        // if key doesn't in table, does nothing
        if (key2int_table.count(key) == 0) return;
        int key_id = string2int(key);
        // find old bucket
        BucketIter old_bucket = value2bucket_table[value[key_id]];
        // add it to new bucket if new_value is not zero
        int new_value = value[key_id] - 1;
        if (new_value != 0) {
            BucketIter bucket;
            if (value2bucket_table.count(new_value) == 0) {
                BucketIter insert_pos = old_bucket;
                bucket = buckets.insert(insert_pos, ListNode(new_value));
                value2bucket_table[new_value] = bucket;
            } else {
                bucket = value2bucket_table[new_value];
            }
            add_to_bucket(bucket, key_id);
        }
        // decr value and remove it from old bucket
        --value[key_id];
        remove_from_bucket(old_bucket, key_id);
    }

    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        // maximal value is the last bucket
        if (buckets.size() == 0) return "";
        ListNode &bucket = buckets.back();
        int key_id = *(bucket.keys.begin());
        return int2string(key_id);
    }

    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if (buckets.size() == 0) return "";
        ListNode &bucket = buckets.front();
        int key_id = *(bucket.keys.begin());
        return int2string(key_id);
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * string param_3 = obj.getMaxKey();
 * string param_4 = obj.getMinKey();
 */