/*
 * [381] Insert Delete GetRandom O(1) - Duplicates allowed
 *
 * https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/description/
 *
 * algorithms
 * Hard (29.65%)
 * Total Accepted:    24.9K
 * Total Submissions: 83.8K
 * Testcase Example:
 * '["RandomizedCollection","insert","insert","insert","getRandom","remove","getRandom"]\n[[],[1],[1],[2],[],[1],[]]'
 *
 * Design a data structure that supports all following operations in average
 * O(1) time.
 * Note: Duplicate elements are allowed.
 *
 *
 * insert(val): Inserts an item val to the collection.
 * remove(val): Removes an item val from the collection if present.
 * getRandom: Returns a random element from current collection of elements. The
 * probability of each element being returned is linearly related to the number
 * of same value the collection contains.
 *
 *
 *
 * Example:
 *
 * // Init an empty collection.
 * RandomizedCollection collection = new RandomizedCollection();
 *
 * // Inserts 1 to the collection. Returns true as the collection did not
 * contain 1.
 * collection.insert(1);
 *
 * // Inserts another 1 to the collection. Returns false as the collection
 * contained 1. Collection now contains [1,1].
 * collection.insert(1);
 *
 * // Inserts 2 to the collection, returns true. Collection now contains
 * [1,1,2].
 * collection.insert(2);
 *
 * // getRandom should return 1 with the probability 2/3, and returns 2 with
 * the probability 1/3.
 * collection.getRandom();
 *
 * // Removes 1 from the collection, returns true. Collection now contains
 * [1,2].
 * collection.remove(1);
 *
 * // getRandom should return 1 and 2 both equally likely.
 * collection.getRandom();
 *
 *
 */
#include <algorithm>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class RandomizedCollection {
    unordered_map<int, unordered_set<int> > mp;
    vector<int> rid;
    default_random_engine generator;

   public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        mp.clear();
        rid.clear();
    }

    /** Inserts a value to the collection. Returns true if the collection did
     * not already contain the specified element. */
    bool insert(int val) {
        rid.push_back(val);
        int cur_id = rid.size() - 1;
        mp[val].insert(cur_id);
        return mp[val].size() == 1;
    }

    /** Removes a value from the collection. Returns true if the collection
     * contained the specified element. */
    bool remove(int val) {
        if (mp.count(val) == 0 || mp[val].size() == 0) return false;
        int rmv_id = *mp[val].begin();
        int tail_val = rid.back(), tail_id = rid.size() - 1;
        if (rmv_id == tail_id) {
            mp[val].erase(rmv_id);
            rid.pop_back();
        } else {
            swap(rid[rmv_id], rid[tail_id]);
            mp[val].erase(rmv_id);
            mp[tail_val].erase(tail_id);
            mp[tail_val].insert(rmv_id);
            rid.pop_back();
        }
        return true;
    }

    /** Get a random element from the collection. */
    int getRandom() {
        std::uniform_int_distribution<int> distribution(0, rid.size() - 1);
        int g = distribution(generator);
        return rid[g];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
