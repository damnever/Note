// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

#include <iostream>
#include <vector>

using namespace std;

class Solution1 {
    public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0;
        size_t size = prices.size();

        for (size_t i = 0; i < size; i++) {
            int buy_price = prices[i];
            for (size_t j = i+1; j < size; j++) {
                max_profit = max(max_profit, prices[j]-buy_price);
            }
        }

        return max_profit;
    }
};

class Solution {
    // Ref: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/solution/
    public:
    int maxProfit(vector<int>& prices) {
        int min_price = numeric_limits<int>::max(), max_profit = 0;

        for (size_t i = 0, size = prices.size(); i < size; i++) {
            int price = prices[i];
            if (price < min_price) {
                min_price = price;
            } else {
                max_profit = max(max_profit, price - min_price);
            }
        }

        return max_profit;
    }
};


int main(int argc, const char* argv[]) {
    Solution1 s1 = Solution1();
    Solution s = Solution();
    {
        int prices_arr[] = {7,1,5,3,6,4};
        vector<int> prices(prices_arr, prices_arr + sizeof(prices_arr)/sizeof(int));
        cout << s1.maxProfit(prices) << '\n';
        cout << s.maxProfit(prices) << '\n';
    }
    {
        int prices_arr[] = {7,6,4,3,1};
        vector<int> prices(prices_arr, prices_arr + sizeof(prices_arr)/sizeof(int));
        cout << s1.maxProfit(prices) << '\n';
        cout << s.maxProfit(prices) << '\n';
    }
    return 0;
}
