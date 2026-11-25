class Solution {
public:
    bool dooperation(int len, vector<int>& nums,
                 unordered_map<int, uint64_t>& mp,
                 uint64_t B) {

    int n = nums.size();
    int sz = len;

    uint64_t power = 1;
    for(int i = 1; i < sz; i++) power *= B;

    uint64_t H = 0;

    // Hash the first window
    for(int i = 0; i < sz; i++) {
        H = H * B + mp[nums[i]];
    }

    unordered_map<uint64_t, int> freq;
    freq[H]++;

    // Slide the window
    for(int i = sz; i < n; i++) {
        uint64_t outgoing = mp[nums[i-sz]];
        uint64_t incoming = mp[nums[i]];

        H = (H - outgoing * power) * B + incoming;

        freq[H]++;
    }

    for(auto it : freq) {
        if(it.second == 1) return true;
    }

    return false;
}
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

unordered_map<int, uint64_t> mp;

auto getHash = [&](int x) -> uint64_t {
    if(!mp.count(x)) mp[x] = rng();
    return mp[x];
};      
for(int x : nums) getHash(x);

        int left = 1, right = n;
int ans = n;
uint64_t B = 31;
while(left <= right) {
    int mid = left + (right-left)/2;

    if(dooperation(mid, nums, mp, B)) {
        ans = mid;
        right = mid-1;
    }
    else {
        left = mid+1;
    }
}

return ans;
    }
};
