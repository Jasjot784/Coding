// https://leetcode.com/problems/sentence-similarity-iii/description/?envType=daily-question&envId=2024-10-06
#include <vector>
#include <string>
#include <sstream>

class Solution {
public:
    bool areSentencesSimilar(std::string sent1, std::string sent2) {
        std::vector<std::string> words1, words2;
        std::stringstream ss1(sent1), ss2(sent2);
        std::string word;

        // Split sentences into words
        while (ss1 >> word) {
            words1.push_back(word);
        }
        while (ss2 >> word) {
            words2.push_back(word);
        }

        int n = words1.size();
        int m = words2.size();

        // Find the maximum matching words from the start
        int start = 0;
        while (start < n && start < m && words1[start] == words2[start]) {
            start++;
        }

        // Find the maximum matching words from the end
        int end = 0;
        while (end < n - start && end < m - start && words1[n - 1 - end] == words2[m - 1 - end]) {
            end++;
        }

        // Check if the combined matched words cover at least one of the sentences
        return start + end >= n || start + end >= m;
    }
};
