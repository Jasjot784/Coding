// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int even = 0;           // 0 actions taken: profit is 0
        int odd = -prices[0];   // 1 action taken (bought on day 0): profit is -prices[0]

        for (int i = 1; i < prices.size(); i++) {
            // Stay even (do nothing), OR transition from odd -> even (SELL today and pay fee)
            int neweven = max(even, odd + prices[i] - fee);
            
            // Stay odd (keep holding), OR transition from even -> odd (BUY today)
            int newodd = max(odd, even - prices[i]);

            even = neweven;
            odd = newodd;
        }

        // You always finish with max profit when you don't hold an unsold stock (even state)
        return even;
    }
};
