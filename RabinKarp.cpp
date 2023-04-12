/* 
    Author : Sukhendu Patra
*/
#include<bits/stdc++.h>
#define pb push_back
#define pf push_front
#define ppb pop_back
#define fast_io ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define loop(i, a, b) for(int i=a; i<b; i++)
#define inf (1ll<<60)
#define MOD 1000000009
#define MOD1 998244353
#define base 31
#define base1 53
#define inf1 (int)1e9
#define INF 1e18
#define nline "\n"
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
/*---------------------------------------------------------------------------------------------------------------------------*/
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size 3
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return arr[0];} //for non prime b
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
bool revsort(ll a, ll b) {return a > b;}
ll combination(ll n, ll r, ll m, ll *fact, ll *ifact) {ll val1 = fact[n]; ll val2 = ifact[n - r]; ll val3 = ifact[r]; return (((val1 * val2) % m) * val3) % m;}
void google(int t) {cout << "Case #" << t << ": ";}
vector<ll> sieve(int n) {int*arr = new int[n + 1](); vector<ll> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;}  //only for prime m, (a and m should be coprime)
ll phin(ll n) {ll number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0) n /= 2;} for (ll i = 3; i <= sqrt(n); i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //O(sqrt(N))
ll giveSqrt(ll x){ll low = 1, high = 3e9, ans = 1;while(low<=high){ll mid = (low+high)/2;if(mid*mid<=x){ans = mid;low = mid+1;}else high = mid-1;}return ans;}
// ll getRandomNumber(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 
/*--------------------------------------------------------------------------------------------------------------------------*/
 /*CSES - String Matching
 Given a string and a pattern, your task is to count the number of positions 
 where the pattern occurs in the string.
The first input line has a string of length n,and the second input line has a pattern 
of length m.Both of them consist of characters a–z.
=> A Rabin Karp Algorithm implementation*/

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
 
void solve(){
    string txt;cin >> txt;
    string pat;cin >> pat;
    int t = txt.size();
    int p = pat.size();
    ll pat_hsh = 0,powp=1;
    for(int i = 0;i<p;i++){
        pat_hsh = (pat_hsh+(mod_mul(powp,(pat[i]-'a'+1),MOD)))%MOD;
        powp = mod_mul(powp,base,MOD);
    }
    
    build(txt);
    vector<int> occurences;
    for (int i = 0; i + p - 1 < t; i++) {
        ll cur_h = getHsh(i,i+p-1);
        if (cur_h == pat_hsh){
            occurences.push_back(i);
        }
    }
    cout << occurences.size() << nline;
}
 
int main(){
    fast_io;
    cout<<fixed;
    cout<<setprecision(10);
    int t=1;
    precal();
    while(t--){
        solve();
    }
    return 0;
}