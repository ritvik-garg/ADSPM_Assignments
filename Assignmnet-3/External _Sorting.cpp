#include<bits/stdc++.h>
using namespace std;
#define INT_SIZE 8
#define ll long long 
#define runnable_size 100000

ll num_words=0;

struct dataNode{
	ll data;
	int fileNo;	
};

void swap (dataNode* a, dataNode* b){
	dataNode temp = *a;
	*a = *b;
	*b = temp;
}

class MinHeap{
	dataNode* arr;
	int heap_size;

public:

	MinHeap(dataNode a[], int h_size){
		heap_size = h_size;
		arr=a;
		int upper_ele = (heap_size-1)/2;
		for(int j=upper_ele; j >=0; j--)
			MinHeapify(j);
	}

	int left(int index){
		return 2*index+1;
	}

	int right(int index){
		return 2*index+2;
	}

	dataNode getMin(){
		return arr[0];
	}

	void replaceMin(dataNode temp){
		arr[0]=temp;
		MinHeapify(0);
	}

	void MinHeapify(int index){
		int l_child = left(index);
		int r_child = right(index);

		int smallest = index;

		if(arr[l_child].data < arr[index].data && l_child < heap_size)
			smallest = l_child;
		if(arr[r_child].data < arr[smallest].data && r_child < heap_size)
			smallest = r_child;
		if(smallest!=index){
			swap(&arr[index], &arr[smallest]);
			MinHeapify(smallest);
		}
	} 
};

void merge(ll arr[], ll left, ll mid, ll right){
	ll num_left = mid-left+1;
	ll num_right = right-mid;

	ll left_temp[num_left], right_temp[num_right];

	for( ll i=0; i<num_left; i++)
		left_temp[i]=arr[left+i];

	for( ll i=0; i<num_right; i++)
		right_temp[i]=arr[mid+1+i];
	
	ll i=0, j=0, k=left;
	while(i<num_left && j<num_right){
		if(left_temp[i] <= right_temp[j])
			arr[k++] = left_temp[i++];
		else
			arr[k++] = right_temp[j++];
	}

	while(i<num_left)
		arr[k++] = left_temp[i++];

	while(j<num_right)
		arr[k++] = right_temp[j++];
	
}

void mergeSort(ll arr[], ll left, ll right){
	if(left<right){
		ll mid = left+(right-left)/2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid+1, right);
		merge(arr, left, mid, right);
	}
}

void mergeFiles(string op_file, int k_way){
	FILE* in_tempFiles[k_way];
	string filename = "";
	for( ll i=0; i<k_way; i++){
		filename += to_string(i);
		in_tempFiles[i] = fopen(filename.c_str(), "r");
		filename="";
	}

	FILE* out = fopen(op_file.c_str(), "w");
	dataNode* arr = new dataNode[k_way];
	ll i;
	for(i=0; i<k_way; i++){
		if(fscanf(in_tempFiles[i], "%lld,", &arr[i].data) != 1)
			break;
		arr[i].fileNo = i;
	}

	MinHeap heap(arr, i);

	ll processedFiles=0;
	ll count=0;
	while(processedFiles != k_way){
		dataNode topElement = heap.getMin();

		if(count != num_words){
			count++;
			fprintf(out, "%lld,", topElement.data);
		}
		else{
			count++;
			fprintf(out, "%lld", topElement.data);
		}

		if(fscanf(in_tempFiles[topElement.fileNo], "%lld,", &topElement.data)!=1){
			topElement.data=LONG_MAX;
			processedFiles++;
		}
		// else
		// 	count++;
		heap.replaceMin(topElement);
	}

	// cout << "count of num : " << count << endl;
	for (ll i = 0; i < k_way; i++) 
		fclose(in_tempFiles[i]); 

	fclose(out); 
}

int main(int argc, char *argv[]){
	string in_filename = argv[1];
	string op_filename = argv[2];

	ifstream inputFile(in_filename, ios::binary);
	inputFile.seekg(0, ios::end);
	ll inFile_size = inputFile.tellg();
	// cout<<"Size of the file is"<<" "<< inFile_size<<" "<<"bytes" << endl;

	ll k_way;
	/* split llo k files and sort */
	FILE* inFile = fopen(in_filename.c_str(), "r");
	FILE* f; 
	string outputFilename = "";

	ll* fileData = new ll[runnable_size*(sizeof(ll))];
	ll i;

	ll k=0;
	num_words = 0;
	bool flag = true;
	while(flag){
		outputFilename += to_string(k);
		f = fopen(outputFilename.c_str(), "w");
		outputFilename = "";

		for(i=0;i<runnable_size/sizeof(ll);i++){
			if(fscanf(inFile, "%lld,", &fileData[i]) != 1){
				flag = false;
				break;
			}
			num_words++;
			// cout << fileData[i] << " ";
		}
		// cout << i << "filedata : " << k <<endl;
		if(i!=0){
			// sort(fileData, fileData+i);
			mergeSort(fileData, 0, i - 1);

			for(ll j=0;j<i;j++){
				fprintf(f, "%lld,", fileData[j]);
			}
			k++;
		}
		fclose(f); 
	}
	if(i==0)
		k_way = k-1;
	else
		k_way = k;

	fclose(inFile); 
	k_way = k;
	// cout << "final k-way : " << k_way << endl;
	// cout << "number of wrods in this file : " << num_words <<endl;
	mergeFiles(op_filename, k_way);
	return 0;
}
