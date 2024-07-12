struct Trie{
    map<int, Trie*> nxt; 
    bool end = false;
    ll hits;
    Trie(){ hits = 0; }

    ~Trie(){
        for(int i=0; i<26; i++){
            if(nxt.find(i)!=nxt.end() && nxt[i]) delete nxt[i];
        }
    }

    void insert(const string& s, int idx, int len){
        hits++;
        if(idx == len) {
            end = 1; return;
        }
        int nxtnode = s[idx] - 'a';
        if(!nxt[nxtnode]){
            nxt[nxtnode] = new Trie;
            nxt[nxtnode]->insert(s, idx+1, len);
        }   
        else nxt[nxtnode]->insert(s, idx+1, len);  
    }

    ll query(const string& s, int idx, int len){
        if(idx == len) {
            return hits;
        }

        ll ret = (idx == 0 ? 0 : hits);
        int nxtnode = s[idx] - 'a';
        if(nxt[nxtnode]){
            ret += nxt[nxtnode]->query(s, idx+1, len);
        }
        return ret;
    }
};
