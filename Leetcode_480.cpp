// https://leetcode.com/problems/sliding-window-median/description/
class Solution {
private:
    multiset<long long> lh; // repr: max heap: descending order
    multiset<long long> uh; // repr: min heap: ascending order
    void addNum(int num) {
        lh.insert(num);
        uh.insert(*lh.rbegin());   // put the max element from lh to uh
        lh.erase(--lh.end());      // pop the max element
        /*
        we will always have two scenarios
        lh.size() = uh.size()
        lh.size() + 1 = uh.size()

        we will keep the median of the entire array in the upper half if the size of entire array is odd. if even, both halves have equal number of elements.
        */
        if (uh.size() - lh.size() > 1) {
            lh.insert(*uh.begin());
            uh.erase(uh.begin());  // put the min ele from uh to lh
        }
    }

    double getMedian() {
        if (lh.size() == uh.size()) {
            return (*lh.rbegin() + *uh.begin()) / 2.0;
        } else {
            return *uh.begin();
        }
    }

    void removeNum(int num) {
        double median = getMedian();
        if (num >= median) {
            auto it = uh.find(num); // removal using an iterator
            uh.erase(it);
        } else {
            auto it = lh.find(num);
            lh.erase(it);
        }
        // balancing in case lower half is having more elements than upper half
        if (lh.size() > uh.size()) {    
            uh.insert(*lh.rbegin());
            lh.erase(--lh.end());
        }
    }
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> medians;
        // add the elements in the initial window
        for (int i = 0; i < k; ++i) {
            addNum(nums[i]);
        }
        // move the window by 1
        for (int i = k; i < nums.size(); ++i) {
            // get the median of the current window
            medians.push_back(getMedian());
            removeNum(nums[i - k]);
            addNum(nums[i]);
        }
        medians.push_back(getMedian());

        return medians;
    }
};
