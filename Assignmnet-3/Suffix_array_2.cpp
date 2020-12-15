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
    return ;
}


void buildSuffixArray(string s, vector<ll>& sa){
	// cout << "in buildarray unction : \n" << s << endl;
	ll len = s.size();

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
	return;

}

// bananabanana$ :

// Suffix Array : 
// 12 11 5 9 3 7 1 6 0 10 4 8 2 

// LCP Array : 
// 0 1 1 3 3 5 0 6 0 2 2 4 0 

void get_lcp(vector<ll> sa, string s, vector<ll>& lcp){
	ll str_len = s.length();
	ll index_from_sa[str_len];
	// ll lcp[str_len];

	for(ll i=0;i<str_len;i++)
		index_from_sa[sa[i]] = i;

	ll next_suffix, kasai=0;

	for(ll i=0;i<str_len;i++){

		if (index_from_sa[i] == str_len-1) 
		{ 
			kasai = 0; 
			continue; 
		}

		next_suffix = sa[index_from_sa[i]+1];

		while(i+kasai<str_len && next_suffix+kasai<str_len && s[i+kasai]==s[next_suffix+kasai]){
			kasai++;
		}

		lcp[index_from_sa[i]] = kasai;

		if(kasai>0){
			kasai--;
		}
	}

	// cout << "inverse array : \n";
	// for(ll i=0;i<str_len;i++)
	// 	cout << index_from_sa[i] << " ";
	// cout << endl;

	// cout << "lcp array : \n";
	// for(ll i=0;i<str_len;i++)
	// 	cout << lcp[i] << " ";
	// cout << endl;


	return;
}

ll getLCP(string s1,string s2)
{
    ll l1=s1.length();
    ll l2=s2.length();

    ll len = min (l1, l2);
    ll count=0;
    for(ll i=0;i<len;i++)
    {
        if(s1[i]==s2[i])
            count++;
        else
            break;
    }
    return count;
}

int main(){
	string s, s_modified;
	cin >> s;
	s_modified= s+"$";
	ll str_len2 = s_modified.length();
	vector<ll> s_arr2(str_len2);
	buildSuffixArray(s_modified, s_arr2);

	// cout << "\nsuffix array 2: \n";
	// for(ll i=0;i<str_len2;i++)
	// 	cout << s_arr2[i] << " ";

	s_arr2.erase(s_arr2.begin());
	// cout << endl;
	// get_lcp(s_arr2, s, lcp);
	ll k;
	cin >> k;

	ll maxLength=-1;;
    ll l;
    string s1,s2;

    for(ll i=0;i<=s.size()-k;i++)
    {
        s1=s.substr(s_arr2[i]);
        s2=s.substr(s_arr2[i+k-1]);
        l=getLCP(s1,s2);

        if(maxLength<l)
            maxLength=l;

    }

    if(maxLength==0)
        maxLength--;

    cout<<maxLength<<endl;   
	return 0;
}