const int N = 1e7+10;
vector <ll> pw(N);
vector <ll> inv(N);
vector <ll> hsh(N);
void precal(){
    pw[0] = 1;
    for(int i = 1;i<N;i++)
        pw[i] = mod_mul(pw[i-1],base,MOD);
    int pw_inv = mminvprime(base,MOD);
    inv[0] = 1;
    for(int i = 1;i<N;i++)
        inv[i] = mod_mul(inv[i-1],pw_inv,MOD);
}


void build(string s){
    int n = s.size();
    for(int i = 0;i<n;i++)
        hsh[i] = mod_add((i == 0)? 0: hsh[i-1],mod_mul(pw[i],s[i]-'a'+1,MOD),MOD);
}
int getHsh(int i,int j){
    int res = mod_add(hsh[j],(i == 0) ? 0 : -hsh[i-1],MOD);
    res = mod_mul(res,inv[i],MOD);
    return res;
}