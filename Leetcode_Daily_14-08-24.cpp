// https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/?envType=daily-question&envId=2024-08-14
// Important concept of nth element in C++ STL
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        const int n=nums.size();
        vector<int> d(n*(n-1)/2);
        int index=0;
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++)
                d[index++]=abs(nums[i]-nums[j]);
        }
        nth_element(d.begin(), d.begin()+(k-1), d.end());
        return d[k-1];
    }
};


 
auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();

// method 2 binary search
class Solution {
public:
    int smallestDistancePair(std::vector<int>& numbers, int k) {
        std::sort(numbers.begin(), numbers.end());
        int minDistance = 0, maxDistance = numbers.back() - numbers.front();
        
        while (minDistance < maxDistance) {
            int midDistance = minDistance + (maxDistance - minDistance) / 2;
            if (countPairsWithinDistance(numbers, midDistance) < k) {
                minDistance = midDistance + 1;
            } else {
                maxDistance = midDistance;
            }
        }
        
        return minDistance;
    }

private:
    int countPairsWithinDistance(const std::vector<int>& numbers, int targetDistance) {
        int count = 0, left = 0;
        for (int right = 1; right < numbers.size(); ++right) {
            while (numbers[right] - numbers[left] > targetDistance) {
                ++left;
            }
            count += right - left;
        }
        return count;
    }
};

