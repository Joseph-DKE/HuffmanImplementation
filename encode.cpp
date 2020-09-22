#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>


/**
The original implementation of the huffman encoding algorithm was derived from
https://www.techiedelight.com/huffman-coding/
The decoding segment of the algorithm was discarded and the encoding segment
was modified to take in a file, create two new files and store the huffman code in
"Huffman.txt" and store the dictionary for decoding the huffman code in "Dictionary.txt"
*/

using namespace std;

// A Tree node
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

// Function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};

// traverse the Huffman Tree and store Huffman Codes
// in a map.
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right)
	{
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// Builds Huffman Tree and decode given input text
void buildHuffmanTree(string text)
{
	// count frequency of appearance of each character
	// and store it in a map
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of
	// Huffman tree;
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root stores pointer to root of Huffman Tree
	Node* root = pq.top();

	// traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	//getting file
    ofstream dicfile; //putting file into readfile
    dicfile.open("Dictionary.txt", ios::app);

	for (auto pair: huffmanCode) {
		dicfile << pair.first << " _ " << pair.second << "~" << '\n';
	}
	dicfile.close();

	// print encoded string
	string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	//creating a file to write to
    ofstream writefile;
    //opening the file and giving it a name
    writefile.open("Huffman.txt", ios::out); //appending to file
    //writing into the file
    writefile << str; //write final base64 into the file incomplete...
    //closing the file
    writefile.close();

}

// Huffman coding algorithm
int main()
{
	string text = "", temp;
    string name; //name of file to be converted
    cout << "Enter name of file to be encoded, example 'a.txt': ";
    cin >> name;
	//getting file
    ifstream readfile; //putting file into readfile
    readfile.open(name, ios::in);
    getline(readfile, text); //read characters from the file

    readfile.close();


	buildHuffmanTree(text);

	return 0;
}
