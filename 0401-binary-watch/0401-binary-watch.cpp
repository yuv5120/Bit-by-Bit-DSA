class Solution {
public:
    std::vector<std::string> readBinaryWatch(int num) {
        std::vector<std::string> times;
        
        for (int h = 0; h < 12; ++h) {
            for (int m = 0; m < 60; ++m) {
                int hOnes = std::bitset<4>(h).count();
                int mOnes = std::bitset<6>(m).count();

                if (hOnes + mOnes == num) {
                    times.push_back(std::to_string(h) + ":" + (m < 10 ? "0" : "") + std::to_string(m));
                }
            }
        }

        return times;
    }
};