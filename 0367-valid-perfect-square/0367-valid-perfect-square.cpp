class Solution {
public:
    bool isPerfectSquare(int num) {
        int odd = 1;

        while(num>0){
            num = num - odd;
            odd = odd + 2;
        }
        return num==0;
    }
};