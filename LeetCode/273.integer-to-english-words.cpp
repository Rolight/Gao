/*
 * [273] Integer to English Words
 *
 * https://leetcode.com/problems/integer-to-english-words/description/
 *
 * algorithms
 * Hard (22.76%)
 * Total Accepted:    58.3K
 * Total Submissions: 256.3K
 * Testcase Example:  '123'
 *
 *
 * Convert a non-negative integer to its english words representation. Given
 * input is guaranteed to be less than 231 - 1.
 *
 *
 * For example,
 *
 * 123 -> "One Hundred Twenty Three"
 * 12345 -> "Twelve Thousand Three Hundred Forty Five"
 * 1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty
 * Seven"
 */
#include <iostream>
#include <string>

using std::string;

const string units[] = {"Zero", "One", "Two",   "Three", "Four",
                        "Five", "Six", "Seven", "Eight", "Nine"};
const string btens[] = {"Ten",      "Eleven",  "Twelve",  "Thirteen",
                        "Fourteen", "Fifteen", "Sixteen", "Seventeen",
                        "Eighteen", "Nineteen"};
const string tens[] = {"",      "Ten",   "Twenty",  "Thirty", "Forty",
                       "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
const string large[] = {"Hundred", "Thousand", "Million", "Billion"};

class Solution {
   public:
    string gao_unit(int num) {
        // supposed num < 999
        string ret = "";
        if (num / 100 != 0) {
            ret += units[num / 100] + " " + large[0];
        }
        num %= 100;
        if (num / 10 != 0) {
            if (ret != "") ret += " ";
            if (num / 10 == 1) {
                ret += btens[num - 10];
                num = 0;
            } else {
                ret += tens[num / 10];
            }
        }
        num %= 10;
        if (num != 0) {
            if (ret != "") ret += " ";
            ret += units[num];
        }
        return ret;
    }

    string gao_billon(int num) {
        string ret = "";
        if (num / 1000000 != 0) {
            ret += gao_unit(num / 1000000) + " " + large[2];
        }
        num %= 1000000;
        if (num / 1000 != 0) {
            if (ret != "") ret += " ";
            ret += gao_unit(num / 1000) + " " + large[1];
        }
        num %= 1000;
        if (num != 0) {
            if (ret != "") ret += " ";
            ret += gao_unit(num);
        }
        return ret;
    }
    string numberToWords(int num) {
        if (num == 0) return units[0];
        string ret = "";
        if (num / 1000000000 != 0) {
            ret += gao_unit(num / 1000000000) + " " + large[3];
        }
        num %= 1000000000;
        if (num != 0) {
            if (ret != "") ret += " ";
            ret += gao_billon(num);
        }
        return ret;
    }
};

int main() {
    int n;
    while (std::cin >> n) {
        Solution s;
        std::cout << s.numberToWords(n) << std::endl;
    }
    return 0;
}
