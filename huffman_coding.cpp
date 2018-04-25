#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

struct node {
    string ch;
    int f{};
    node *left{};
    node *right{};
};


class huffman_cmp{
public:
    explicit huffman_cmp(const bool& revparam = false){reverse = revparam;}
    bool operator() (const node* lhs, const node* rhs) const{
        if (reverse) return (lhs->f < rhs->f);
        else return (rhs->f < lhs->f);
    }
private:
    bool reverse;
};

typedef priority_queue<node*, vector<node*>, huffman_cmp> huffman_pq;
typedef pair<node*, string> node_info;



int main() {

    // introduction
    cout << "Huffman Coding" << endl;
    cout << "Input Format:" << endl;
    cout << " - first line: N - the integer number of characters (N > 1)" << endl;
    cout << " - N following lines: <ch> <f> - <ch> is the character,  <f> is its frequency (<f> > 0)"<<endl;
    cout << "Example Input: "<<endl;
    cout << " 6"<<endl;
    cout << " B 6"<<endl;
    cout << " C 2"<<endl;
    cout << " _ 10"<<endl;
    cout << " E 7"<<endl;
    cout << " A 11"<<endl;
    cout << " D 10"<<endl;
    cout << "Enter your input: "<<endl;

    // reading input
    int n;
    cin>>n;
    if (n < 2){
        return 0;
    }
    huffman_pq hm_pq;
    for (int i = 0; i < n; i++){
        string ch;
        int f = 0;
        cin>>ch>>f;
        auto tmp = new node();
        tmp->ch = ch;
        tmp->f = f;
        hm_pq.push(tmp);
    }

    // Use priority queue (min heap) to create Huffman Tree
    while (hm_pq.size() > 1){
        node * lNode = hm_pq.top();
        hm_pq.pop();
        node * rNode = hm_pq.top();
        hm_pq.pop();
        node * pNode;
        pNode = new node();
        pNode->left = lNode;
        pNode->right = rNode;
        pNode->ch = "";
        pNode->f = lNode->f + rNode->f;
        hm_pq.push(pNode);
    }

    // traverse the Huffman Tree using Depth First Search
    auto huffman_tree = hm_pq.top();
    stack<node_info> nodes;
    nodes.push(node_info(huffman_tree, ""));
    unordered_map<string, string> huffman_code_mapping;
    while (!nodes.empty()){
        auto tmp = nodes.top();
        nodes.pop();
        if (!tmp.first->left && !tmp.first->right){
            huffman_code_mapping[tmp.first->ch] = tmp.second;
        } else{
            // in huffman tree, if a node has a child, then it has both left and right children
            nodes.push(node_info(tmp.first->right, tmp.second + "1"));
            nodes.push(node_info(tmp.first->left, tmp.second + "0"));
        }
    }

    // Print out Huffman Coding table
    cout<<"Huffman coding table: "<<endl;
    for (auto x: huffman_code_mapping){
        cout<<x.first<<" "<<x.second<<endl;
    }
    return 0;
}