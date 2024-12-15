#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

vector<ll> E; //expenses
vector< tuple<ll, double,double> > C; //cards; M,X,Y
vector<vector<double> > dp; //[ci][s]
int ns;

double iter(int ci, int flags)
{
    if( ci == C.size() ) return 0.0;
    if( dp[ci][flags] > 0.0 ) return dp[ci][flags];

    double mx = 0.0;
    for(int s=0; s <= ns; ++s){
        if( flags & s ) continue; // invalid set

        ll sum = 0;
        auto ts = s;

        for(int i=0; i < E.size(); ++i, ts >>= 1){
            if( ts & 1 ){
                sum += E[i];
            }
        }

        double cb;
        if( sum >= get<0>(C[ci]) ) cb = (double)sum * get<1>(C[ci]) / 100.0;
        else cb = (double)sum * get<2>(C[ci]) / 100.0;

        mx = max(mx, cb + iter(ci+1, flags | s ) );
    }

    return dp[ci][flags] = mx;
}

inline void solve()
{
    int c;
    cin >> c;
    C.resize(c);
    for(auto&[M,X,Y] : C) cin >> M >> X >> Y;

    int n;
    cin >> n;
    E.resize(n);
    for(auto& i : E) cin >> i;

    /// check : PASSED
    /*
    cout<< C.size() << "\n";
    for(auto i : C ) cout << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << "\n";
    cout << E.size() << "\n";
    for(auto i : E ) cout << i << " ";
    cout << "\n";
    */

    ns = 1 << E.size();
    dp.resize( C.size(), vector<double>(ns, 0.0) );
    //cout << dp.size() << " " << dp[0].size() << " " << iter(0, 0) << "\n";
    cout << fixed << setprecision(6) << iter(0,0) << "\n";

    dp.clear();
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

