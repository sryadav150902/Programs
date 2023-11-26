#include <bits/stdc++.h>
using namespace std;

struct minHeapNode
{
	char data;
	int freq;
	minHeapNode *left, *right;
	minHeapNode(char d, int f)
	{
		left = right = NULL;
		this->data = d;
		this->freq = f;
	}
};

struct compare
{
	bool operator()(minHeapNode *A, minHeapNode *B)
	{
		return (A->freq > B->freq);
	}
};


void printCodes(struct minHeapNode* root, string str){
	if(root == nullptr){
		return;
	}
	if(root->data != '$'){
		cout << root->data << ": " << str << endl;
	}
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}
void huffmanCode(vector<char> &data, vector<int> &freq,int size)
{
	struct minHeapNode *left,*right,*temp;
	priority_queue<minHeapNode*,vector<minHeapNode*>,compare>pq;

	for(int i=0;i<size;i++){
		pq.push(new minHeapNode(data[i],freq[i]));
	}

	while(pq.size()!=1){
		left = pq.top();
		pq.pop();
		right = pq.top();
		pq.pop();
		temp = new minHeapNode('$',left->freq+right->freq);
		temp->left = left;
		temp->right = right;
		pq.push(temp);
	}
	printCodes(pq.top(),"");
}



int main()
{
	int n;
	cin >> n;
	vector<char> data(n);
	vector<int> freq(n);
	cout << "Enter characters: ";
	for (int i = 0; i < n; i++)
	{
		cin >> data[i];
	}
	cout << "Enter frequency: ";
	for (int i = 0; i < n; i++)
	{
		cin >> freq[i];
	}

	huffmanCode(data, freq,n);
	return 0;
}