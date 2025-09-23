class Solution {
public:
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
    int compareVersion(string version1, string version2) {
        vector<string> v1_revisions = split(version1, '.');
    vector<string> v2_revisions = split(version2, '.');
    int max_length = max(v1_revisions.size(), v2_revisions.size());
    for (int i = 0; i < max_length; ++i) {
     int rev1 = i < v1_revisions.size() ? stoi(v1_revisions[i]) : 0;
     int rev2 = i < v2_revisions.size() ? stoi(v2_revisions[i]) : 0;
        if (rev1 < rev2) {
            return -1;
        } else if (rev1 > rev2) {
            return 1;
        }
    }
    return 0;
    }
};