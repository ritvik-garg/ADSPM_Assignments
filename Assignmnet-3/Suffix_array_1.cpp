#include<bits/stdc++.h>
using namespace std;
#define ll long long

void count_sort(vector<ll>& sa, vector<ll> c){
	ll n = sa.size();
	vector<ll> count(n);

	for(auto x : c)
		count[x]++;

	vector<ll> sa_modified(n);

	vector<ll> pos(n);
	pos[0] = 0 ;
	for(ll i = 1; i < n;i++ ) {
		pos[i] = pos[i-1] + count[i-1];
	}

	for(auto x : sa)
		sa_modified[pos[c[x]]++] = x;

	sa = sa_modified;
}


void buildSuffixArray(string s){
	// cout << "in buildarray unction : \n" << s << endl;
	ll len = s.size();
	vector<ll> sa(len);
	vector<ll> eq_class(len);

	vector<pair<char, ll>> a(len);
	for(ll i=0; i<len ;i++){
		a[i] = {s[i], i};
	}
	sort(a.begin(), a.end());
	for(ll i=0; i<len; i++){
		sa[i] = a[i].second;
	}
	// cout <<"1\n";

	eq_class[sa[0]] = 0;
	for(ll i=1; i<len ;i++){
		if(a[i].first == a[i-1].first)
			eq_class[sa[i]] = eq_class[sa[i-1]];
		else
			eq_class[sa[i]] = eq_class[sa[i-1]]+1;
	}

	// cout << "\nsuffix array 2: \n";
	// for(ll i=0;i<str_len2;i++)
	// 	cout << s_arr2[i] << " ";
	// cout << endl;

	// cout <<"2\n";
	ll k=0;
	while(pow(2,k) < len){
		for(ll i=0; i<len; i++){
			sa[i] = fmod(sa[i]-pow(2,k) + len, len);
		}

		count_sort(sa,eq_class);

		vector<ll> eq_class_modified(len);
		eq_class_modified[sa[0]] = 0;

		for(ll i=1; i<len; i++){
			pair<ll, ll> prev = {eq_class[sa[i-1]], eq_class[(sa[i-1] + (1<<k))%len]};
			pair<ll, ll> current = {eq_class[sa[i]], eq_class[(sa[i] + (1<<k))%len]};

			if (prev==current)
				eq_class_modified[sa[i]] = eq_class_modified[sa[i-1]];
			else
				eq_class_modified[sa[i]] = eq_class_modified[sa[i-1]]+1;
		}

		eq_class = eq_class_modified;
		k++;
	}
	// cout <<"2\n";

	// for(ll i=0;i<len; i++){
	// 	// cout << sa[i] << " ";
	// 	if(sa[i]<len/2){
	// 		cout << s.substr(sa[i],len/2)<< endl;
	// 		break;
	// 	}
	// }
	// cout <<"4\n";
	// cout << "\nsuffix array 2: \n";
	// for(ll i=0;i<len;i++)
	// 	cout << sa[i] << " ";
	// cout << endl;

	for(ll i=0;i<len; i++){
		// cout << sa[i] << " ";
		if(sa[i]<len/2){
			cout << s.substr(sa[i],len/2)<< endl;
			break;
		}
	}

	return;
}

int main(){
	string s;
	cin >> s;
	s = s+s+"$";
	// cout << "2s is : " << s<<endl;
	buildSuffixArray(s);
	return 0;
}