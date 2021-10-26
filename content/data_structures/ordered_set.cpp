#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
             tree_order_statistics_node_update>;

int main() {
	ordered_set<pair<int,int>> st;
	st.insert({1, 22});
	st.insert({1, 33});
	st.insert({1, 44});
	st.insert({1, 55});
	cout << st.order_of_key({1,33}) << endl;
	cout << st.order_of_key({1,35}) << endl; // Where would it be?
	cout << (*st.find_by_order(2)).second << endl;
	return 0;
}
