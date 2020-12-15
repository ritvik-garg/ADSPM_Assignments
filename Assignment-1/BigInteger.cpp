#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;


string divideBy2(string a){
	int len_a = a.size();
	string res="";
	int i,val,val1, rem=0;
	for(i=0;i<len_a;i++){
		val1=a[i]-'0';
		val = rem*10+val1;
		if(val%2==1){
			rem=1;
		}
		else
			rem=0;
		res += to_string(val/2);
	}
	string result="";
	int res_len = res.length();
	for(i =0; i<res_len; i++)
	{
		if(res[i] > '0')
			break;
	}
	
	for(;i<res_len; i++)
		result += res[i];
	
	return result;
}

string addition(string a, string b){
	int len_a = a.size();
	int len_b = b.size();
	int val1,val2,sum,carry=0;

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	string result="";
	int i;
	for(i=0;i<len_b;i++){
		val1 = a[i]-'0';
		val2 = b[i]-'0';
		sum=val1+val2+carry;
		result += to_string(sum%10);
		carry = sum/10;
	}
	for(;i<len_a;i++){
		val1 = a[i]-'0';
		sum = val1+carry;
		result += to_string(sum%10);
		carry = sum/10;
	}
	result += to_string(carry);

	int res_len=result.length();
	string res="";
	for(i = res_len-1; i>= 0;i--)
	{
		if(result[i] > '0')
			break;
	}
	
	for(;i >= 0;i--)
		res += result[i];
	
	return res;
}

bool isGreater(string a, string b){
	int len_a = a.size();
	int len_b = b.size();
	if(len_b==len_a){
		if(a>b){
			return true;
		}
		return false;
	}
	else if(len_a > len_b)
		return true;
	else
		return false;
}

string subtract(string a, string b){
	int len_a = a.size();
	int len_b = b.size();

	if(len_a == len_b && (b[0]>a[0])){
		return "-1";
	}
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	string res="";
	int val1, val2, diff,k;
	for(int i=0; i<len_a;i++){
		if(i>=len_b){
			res += a[i];
		}
		else{
			val1 = a[i]-'0';
			val2 = b[i]-'0';
			if(val1>=val2){
				diff = val1-val2;
				res += to_string(diff);
			}
			else{
				k=1;
				while(a[i+k]=='0'){
					a[i+k] = '9';
					k++;
				}
				a[i+k] -= 1;
				val1 += 10;
				diff = val1-val2;
				res += to_string(diff);
			}
		}
	}

	int i;
	reverse(res.begin(), res.end());
	for(i=0;i<res.size();i++)
	{
		if(res[i] > '0')
			break;
	}

	res = res.substr(i);
	return res;
}

string multiplyBigInt(string a, string b){
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int len_a = a.size();
	int len_b = b.size();
	int res_len =  len_a + len_b;
	int num1, num2, mult;

	int result[res_len] = {0};
	for(int i=0;i<len_a; i++){
		num1 = a[i]-'0';
		for(int j=0;j<len_b; j++){
			num2 = b[j]-'0';
			mult = num1*num2;
			result[i+j] += mult;
			result[i+j+1] += result[i+j]/10;
			result[i+j] %= 10;
		}
	}
	int i;
	string res="";
	for(i = res_len-1; i>= 0;i--)
	{
		if(result[i] > 0)
			break;
	}
	for(;i >= 0;i--)
		res += to_string(result[i]);
	return res;
}

string multiplyByInt(int val, string result){

	int i, carry=0, prod;
	for(i=0; i< result.size(); i++){
		prod = (result[i]-'0')*val + carry;
		result[i]= char(prod%10 + '0');
		carry = prod/10;

	}

	while(carry!=0){
		result += char(carry%10 + '0');
		carry /= 10;
	}
	return result;
}

string factorial(string number){
	int k = stoi(number);
	string result = "1";
	for(int i=2; i<=k; i++){
		result = multiplyByInt(i, result);
	}
	reverse(result.begin(), result.end());
	return result;
}


string exp(string base, int exponent){
	if(exponent==0)
		return "1";
	else if(exponent==1)
		return base;
	else{
		string result="1";
		while(exponent) {
			if(exponent & 1) { 
				result = multiplyBigInt(result, base);

			}
			base = multiplyBigInt(base, base);
			exponent >>= 1;	
		}
		return result;
	}
}

string gcd(string a, string b){

	while(a!=b){
		if(isGreater(a,b))
			a = subtract(a,b);
		else
			b = subtract(b,a);
	}
	return a;
}


string binarySearchSubtract(string a, string b){

	string left="0", right=a;//greater to right
	string m1,m2,m3,m4;

	while (isGreater(right, left))
	{
		m1= addition(right,left);
		m2 = divideBy2(m1);
		m3= multiplyBigInt(m2,b);
		if(isGreater(a,m3)){
			m4 = subtract(a, m3);
			if(isGreater(m4,b))
				left = addition(m2,"1");
			else
				right = m2;
		}
		else
			right = m2;
	}
	m3= multiplyBigInt(left,b);
	return subtract(a,m3);
}

string gcd2(string a, string b){

	while(a!=b){
		if(isGreater(a,b)){
			a = binarySearchSubtract(a,b);
		}
		else
			b = binarySearchSubtract(b,a);
	}
	return a;
}


int main()
{
	int num_query;
	cin >> num_query;
	int a,b,c,len_a,len_b, diff;
	string ans,p,q;
	while(num_query--){
		cin >>a;
		if(a==1){
			cin >> p>>b;
			ans = exp(p,b);
		}
		else if(a==2){
			cin >> p>>q;
			len_a = p.size();
			len_b = q.size();
			diff = len_a-len_b;
			diff = abs(diff);
			if(diff <= 3){
				ans=gcd(p,q);
			}
			else if(diff>5){
				ans=gcd2(p,q);
			}else if(len_a < 30 && len_b<30){
				ans=gcd2(p,q);
			}else if(len_a>=30 && len_b >=30){
				ans=gcd(p,q);
			}else if((len_a >= 30 && len_b<30) || (len_a < 30 && len_b>=30)){
				if(diff>5)
					ans=gcd2(p,q);
				else
					ans=gcd(p,q);
			}
		}
		else if(a==3){
			cin >> p;
			ans = factorial(p);
		}
		cout << ans << endl;
	}
	return 0; 
}