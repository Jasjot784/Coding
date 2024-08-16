// // https://www.geeksforgeeks.org/problems/number-of-paths0926/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
// Certainly! Here’s a concise explanation of how to compute the modular inverse using Fermat's Little Theorem:

// ---

// To compute \(\frac{a}{b} \mod MOD\), we need the modular inverse of \(b\) modulo \(MOD\). The modular inverse of \(b\), denoted \(b^{-1}\), is a number such that:

// \[ b \cdot b^{-1} \equiv 1 \mod MOD \]

// For a prime modulus \(MOD\), the modular inverse of \(b\) can be found using Fermat's Little Theorem. Fermat's Little Theorem states:

// \[ b^{MOD-1} \equiv 1 \mod MOD \]

// Therefore:

// \[ b \cdot b^{MOD-2} \equiv 1 \mod MOD \]

// Thus, the modular inverse of \(b\) is:

// \[ b^{-1} \equiv b^{MOD-2} \mod MOD \]

// --- 

// This result leverages the property of modular arithmetic under a prime modulus to efficiently compute the modular inverse.
class Solution
{
    public:
     #define MOD (int)(1e9+7)
    long long BinExp(int base,int power)
    {
        long long ans=1;
        while(power)
        {
            if(power&1) ans=(ans*base)%MOD;
            base=(base*1LL*base)%MOD;
            power>>=1;
        }
        return ans;
    }
    long long  numberOfPaths(int m, int n)
    {
        // (m+n-2) C (n-1)
        // = (m+n-2)! / (n-1)! *(m-1)!
        
        long long num=1;
        for(int i=n;i<=m+n-2;i++) num=(num*i)%MOD;
        
        long long den=1;
        for(int i=1;i<=m-1;i++) den=(den*i)%MOD;
        
        return (num*BinExp(den,MOD-2))%MOD;
    }


};
