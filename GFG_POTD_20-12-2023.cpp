// https://www.geeksforgeeks.org/problems/variation-in-nim-game4317/1
int findWinner(int n, int arr[]){
        // code here
        int res=arr[0];
         for(int i=1;i<n;i++){
             res^=arr[i];
         }
         if(res==0)return 1;
         if(n%2==0)return 1;
         else return 2;
        
    }
