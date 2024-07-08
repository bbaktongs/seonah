#include "seonah.h"

template<typename T>
struct KMP{    
    int N, M;
    vector<T> S; vector<T> P;
    vector<int>fail;

    KMP(int n, int m, vector<T>& s, vector<T>& p){
        N = n; M = m; S = s; P = p;
        fail.resize(M, 0);
    }

    KMP(string s, string p){
        static_assert(is_same<T, char>::value);
        for(char &c:s) S.push_back(c);
        for(char &c:p) P.push_back(c);
        N = s.size(), M = p.size(); fail.resize(M, 0);
    }

    void f(){
        for(int i=1, j=0; i < M; i++){
            while(j>0 && P[i] != P[j]) j = fail[j-1];
            if(P[i] == P[j]) fail[i] = ++j;
        }
    }

    vector<int> solve() {
        f();
        vector<int>ret;
        for(int i=0, j=0; i<N; i++){
            while(j>0 && S[i]!=P[j]) j = fail[j-1];
            if(S[i] == P[j]){
                if(j == M-1){
                    // 0-based
                    ret.push_back(i-M+1);
                    j = fail[j];
                }
                else j++;
            }
        }
        return ret;
    }
};
 
