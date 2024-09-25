// https://leetcode.com/problems/sum-of-prefix-scores-of-strings/?envType=daily-question&envId=2024-09-25
struct Trie {
    Trie* child[26] = {};
    int count = 0;
    
    void insert_word(string& s) {
        Trie* p = this;
        for(auto c : s) {
            int chi = c - 'a';
            if (p->child[chi] == NULL) {
                p->child[chi] = new Trie();
            }
            p = p->child[chi];
            p->count++;
        }
    }
    int count_word(string& s) {
        Trie* p = this;
        int result = 0; 
        for (int i = 0; i < s.size() && p != NULL; i++) {
            int charact_index = s[i] - 'a';
            p = p->child[charact_index];
            if (p != NULL)
                result += p->count;
        }
        return result;
    }
};
class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        Trie* t = new Trie();
        for(auto w : words) {
            t->insert_word(w);
        }
        vector<int> res;
        for (auto w: words) {
            int c = t->count_word(w);
            res.push_back(c);
        }
        return res;
    }
};
