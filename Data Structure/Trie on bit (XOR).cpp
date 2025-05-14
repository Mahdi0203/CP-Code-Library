#include<bits/stdc++.h>
using namespace std;

#define bug(a) cout << #a << " : " << a <<endl;
using ll = long long;

struct Trie{
  static const int B = 31;
  struct Node{
    Node* links[2];
    int sz;

    Node(){
      links[0] = links[1] = NULL;
      sz = 0;
    }
    
    bool containsKey(int bit){
      return links[bit] != NULL;
    }
    void put(int bit, Node* node){
      links[bit] = node;
    }
    Node* get(int bit){
      return links[bit];
    }
    int get_sz(int bit){
      return links[bit]->sz;
    }

  } *root;

  Trie(){
    root = new Node();
  }

  void insert(int num){
    Node* node = root;
    node->sz++;
    for(int i = B; i >= 0; i--){
      int bit = (num >> i) & 1;
      if ( !node->containsKey(bit) ){
        node->put(bit, new Node());
      }
      node = node->get(bit);
      node->sz++;
    }
  }

  int query(int x, int k){    // number of values s.t. val ^ x < k
    Node* node = root;
    int ans = 0;
    for(int i = B; i >= 0; i--){
      if ( node == NULL ) {
        break;
      }
      int bit1 = (x >> i) & 1, bit2 = (k >> i) & 1;
      if ( bit2 ){
        if ( node->containsKey(bit1) ){
          ans += node->get_sz(bit1);
        }
        node = node->get(!bit1);
      }
      else{
        node = node->get(bit1);
      }
    }
    return ans;
  }

  int get_max(int x){     // // returns maximum of val ^ x
    Node* node = root;
    int ans = 0;
    for(int i = B; i >= 0; i--){
      int bit = (x >> i) & 1;
      if ( node->containsKey(!bit) ){
        ans += (1 << i);
        node = node->get(!bit);
      }
      else{
        node = node->get(bit);
      }
    }
    return ans;
  }

  int get_min(int x){   // returns minimum of val ^ x
    Node* node = root;
    int ans = 0;
    for(int i = B; i >= 0; i--){
      int bit = (x >> i) & 1;
      if ( node->containsKey(bit) ) {
        node = node->get(bit);
      }
      else{
        ans += (1 << i);
        node = node->get(!bit);
      }
    }
    return ans;
  }
  void del(node* cur) {
    for (int i = 0; i < 2; i++) if (cur -> nxt[i]) del(cur -> nxt[i]);
    delete(cur);
  }
} ; 

void solve ( int cs ){
  Trie* trie = new Trie();
  /* to get number of pair s.t. (val ^ x >= k)
    ans = (all possible pair - (no. of pair (val ^ x < k))
  */
}
