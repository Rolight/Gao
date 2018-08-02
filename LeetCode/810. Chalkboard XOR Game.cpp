class Solution {
   public:
    bool xorGame(vector<int> &nums) {
        int xsum = 0;
        for (int i = 0; i < nums.size(); i++) xsum ^= nums[i];
        return nums.size() % 2 == 0 || xsum == 0;
    }
};