#include<bits/stdc++.h>
using namespace std;

void count_sort(vector<int>& sa, vector<int> c){
	int n = sa.size();
	vector<int> count(n);

	for(auto x : c)
		count[x]++;

	vector<int> sa_modified(n);

	vector<int> pos(n);
	pos[0] = 0 ;
	for(int i = 1; i < n;i++ ) {
        pos[i] = pos[i-1] + count[i-1];
    }
    
    for(auto x : sa)
        sa_modified[pos[c[x]]++] = x;

    sa = sa_modified;
}


void buildSuffixArray(string s, vector<int>& sa){
	// cout << "in buildarray unction : \n" << s << endl;
	int len = s.size();

	vector<int> eq_class(len);

	vector<pair<char, int>> a(len);
	for(int i=0; i<len ;i++){
		a[i] = {s[i], i};
	}
	sort(a.begin(), a.end());
	for(int i=0; i<len; i++){
		sa[i] = a[i].second;
	}
	// cout <<"1\n";

	eq_class[sa[0]] = 0;
	for(int i=1; i<len ;i++){
		if(a[i].first == a[i-1].first)
			eq_class[sa[i]] = eq_class[sa[i-1]];
		else
			eq_class[sa[i]] = eq_class[sa[i-1]]+1;
	}

	// cout << "\nsuffix array 2: \n";
	// for(int i=0;i<str_len2;i++)
	// 	cout << s_arr2[i] << " ";
	// cout << endl;

	// cout <<"2\n";
	int k=0;
	while(pow(2,k) < len){
		for(int i=0; i<len; i++){
			sa[i] = fmod(sa[i]-pow(2,k) + len, len);
		}

		count_sort(sa,eq_class);

		vector<int> eq_class_modified(len);
		eq_class_modified[sa[0]] = 0;

		for(int i=1; i<len; i++){
			pair<int, int> prev = {eq_class[sa[i-1]], eq_class[(sa[i-1] + (1<<k))%len]};
			pair<int, int> current = {eq_class[sa[i]], eq_class[(sa[i] + (1<<k))%len]};

			if (prev==current)
				eq_class_modified[sa[i]] = eq_class_modified[sa[i-1]];
			else
				eq_class_modified[sa[i]] = eq_class_modified[sa[i-1]]+1;
		}

		eq_class = eq_class_modified;
		k++;
	}
	// cout <<"2\n";

	// for(int i=0;i<len; i++){
	// 	// cout << sa[i] << " ";
	// 	if(sa[i]<len/2){
	// 		cout << s.substr(sa[i],len/2)<< endl;
	// 		break;
	// 	}
	// }
	// cout <<"4\n";
	return;

}

// bananabanana$ :

// Suffix Array : 
// 12 11 5 9 3 7 1 6 0 10 4 8 2 

// LCP Array : 
// 0 1 1 3 3 5 0 6 0 2 2 4 0 

void get_lcp(vector<int> sa, string s, vector<int>& lcp){
	int str_len = s.length();
	int index_from_sa[str_len];
	// int lcp[str_len];

	for(int i=0;i<str_len;i++)
		index_from_sa[sa[i]] = i;

	int next_suffix, kasai=0;

	for(int i=0;i<str_len;i++){

		if (index_from_sa[i] == 0) 
		{ 
			kasai = 0; 
			continue; 
		}

		next_suffix = sa[index_from_sa[i]-1];

		while(i+kasai<str_len && next_suffix+kasai<str_len && s[i+kasai]==s[next_suffix+kasai]){
			kasai++;
		}

		lcp[index_from_sa[i]] = kasai;

		if(kasai>0){
			kasai--;
		}
	}

	// cout << "inverse array : \n";
	// for(int i=0;i<str_len;i++)
	// 	cout << index_from_sa[i] << " ";
	// cout << endl;

	// cout << "lcp array : \n";
	// for(int i=0;i<str_len;i++)
	// 	cout << lcp[i] << " ";
	// cout << endl;


	return;
}

void getLongestPalindrome(vector<int> s_arr, vector<int> lcp, string s_modified, int actual_len){
	int len = s_modified.length();	
	int pos = 0;
	int llength = 0;
	for(int i=1;i<len;i++){

		if(lcp[i] > llength){
			if((s_arr[i-1]>actual_len && s_arr[i]<actual_len )||(s_arr[i-1] < actual_len && s_arr[i]> actual_len)){
				// if(llength < lcp[i]){
				// cout << "i " << i << endl;
					llength = lcp[i];
					pos = s_arr[i];
					// cout << "length : " << llength << "  pos : " << pos << endl;
				// }
			}
		}
	}
	cout << s_modified.substr(pos, llength) << endl;
	return ;
}

int main(){
	string s, s_modified;
	cin >> s;
	string rev = string(s.rbegin(),s.rend()); 
	s_modified= s + "$" + rev + "#";
	int str_len = s_modified.length();
	int s_len = s.length();
	vector<int> s_arr(str_len), lcp(str_len);
	buildSuffixArray(s_modified, s_arr);

	// cout << "\nsuffix array before erasing : \n";
	// for(int i=0;i<str_len;i++)
	// 	cout << s_arr[i] << " ";
	// cout << endl;

	s_arr.erase(s_arr.begin());
	// cout << "new array size : " << s_arr.size() << endl;

	// cout << "\nsuffix array after: \n";
	// for(int i=0;i<str_len-1;i++)
	// 	cout << s_arr[i] << " ";
	// cout << endl;
	// cout << endl;
	s_modified= s + "$" + rev;
	get_lcp(s_arr, s_modified, lcp);

	getLongestPalindrome(s_arr, lcp, s_modified, s_len);

	return 0;
}