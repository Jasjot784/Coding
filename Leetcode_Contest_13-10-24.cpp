// https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/
class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size(); // Get the size of the input array
        vector<long long> res; // Result vector to store x-sums
        unordered_map<long long, long long> m, p; // Frequency map (m) and presence map (p)
        set<pair<long long, long long>> a, b; // Two sets for managing elements based on frequency
        long long s = 0; // Variable to store the current x-sum

        // Iterate through each element in the nums array
        for (int i = 0; i < n; ++i) {
            int v = nums[i]; // Current element

            // Check if the current element has been seen before
            if (p.count(v)) {
                if (p[v]) { // If the element is in the top x frequent set (b)
                    b.erase({m[v], v}); // Remove it from the set b
                    s -= m[v] * v; // Subtract its contribution from the sum
                } else {
                    a.erase({m[v], v}); // If not in b, remove from set a
                }
            }

            // Increment the frequency of the current element
            ++m[v];

            // If the size of b is less than x, add the current element to b
            if (b.size() < x) {
                b.insert({m[v], v}); // Insert into the set b
                p[v] = 1; // Mark the element as present in top x
                s += v * m[v]; // Add its contribution to the sum
            } else {
                // If the size of b is equal to x, compare with the smallest in b
                auto z = *b.begin(); // Get the smallest element in b
                if (z < pair<long long, long long>(m[v], v)) {
                    // If the current element's frequency is higher or same with higher value
                    b.erase(z); // Remove the smallest element from b
                    s -= z.first * z.second; // Subtract its contribution from sum
                    a.insert(z); // Insert it into set a (the "others" set)
                    p[z.second] = 0; // Mark it as not in the top x
                    b.insert({m[v], v}); // Add the current element to b
                    p[v] = 1; // Mark the current element as present in top x
                    s += v * m[v]; // Add its contribution to the sum
                } else {
                    a.insert({m[v], v}); // If the current element is not added, insert it into a
                    p[v] = 0; // Mark it as not present in top x
                }
            }

            // If we have processed at least k elements, we compute the result
            if (i + 1 >= k) {
                res.push_back(s); // Add the current x-sum to results
                v = nums[i - k + 1]; // Determine the element going out of the window

                // Update the sum and sets for the outgoing element
                if (p[v]) { // If the outgoing element is in top x (b)
                    b.erase({m[v], v}); // Remove it from b
                    s -= m[v] * v; // Subtract its contribution from sum
                } else {
                    a.erase({m[v], v}); // If not in b, remove it from a
                }

                --m[v]; // Decrease the frequency of the outgoing element
                // Manage the balance between the two sets
                while (b.size() < x && !a.empty()) {
                    auto z = *a.rbegin(); // Get the highest frequency element from a
                    a.erase(z); // Remove it from a
                    b.insert(z); // Add it to b
                    p[z.second] = 1; // Mark it as present in top x
                    s += z.first * z.second; // Add its contribution to the sum
                }

                // If still below x elements in b after adjustments
                if (b.size() < x) {
                    b.insert({m[v], v}); // Add the outgoing element back to b
                    p[v] = 1; // Mark it as present in top x
                    s += v * m[v]; // Add its contribution to the sum
                } else {
                    // Compare with the smallest in b again
                    auto z = *b.begin();
                    if (z < pair<long long, long long>(m[v], v)) {
                        // If the current element's frequency is higher or equal to the lowest in b
                        b.erase(z); // Remove the smallest element from b
                        s -= z.first * z.second; // Subtract its contribution from sum
                        a.insert(z); // Insert it into set a
                        p[z.second] = 0; // Mark it as not present in top x
                        b.insert({m[v], v}); // Add current element to b
                        p[v] = 1; // Mark current element as present in top x
                        s += v * m[v]; // Add its contribution to the sum
                    } else {
                        a.insert({m[v], v}); // If not added, insert into a
                        p[v] = 0; // Mark it as not present in top x
                    }
                }
            }
        }
        return res; // Return the vector of x-sums
    }
};
