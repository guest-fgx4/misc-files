class Solution {
public:
    double myPow(double x, int n) {
       double res = 1.0;

        if (n == 0) return 1.0;

        long long un = n;

        if (un < 0)
        {
            un = un * -1;
            x = 1/x;
        }

        res = myPow(x, un / 2);
        if (un & 1)
        {
            return res * res * x;
        }
        else
        {
            return res * res;
        }

       return res;
    }
};
