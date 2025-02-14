struct Trie{
  struct Node{                        // node information depends on problems;
    Node *links[26];
    bool flag = false;

    bool containsKey(char ch){
      return links[ch - 'a'] != NULL;
    }
    void put(char ch, Node* node){    // set as reference node
      links[ch - 'a'] = node;
    }
    Node* get(char ch){               // get the reference node
      return links[ch - 'a'];
    }
    void setEnd(){                    // set as the end of a word
      flag = true;
    }
    bool isEnd(){                     // check it it end of a word
      return flag;
    }
 
  } *root;
 
  Trie(){
    root = new Node();
  }
 
  // TC = O(word.size())
  void insert(string word){           // update according to problem 
    Node* node = root;
    for(auto c : word){
      if ( !node->containsKey(c) ){
        node->put(c, new Node());
      }
      node->add();
      node = node->get(c);
    }
    node->setEnd();
  }
 
  // TC = O(word.size())
  int search(string word){            // update according to problem
    Node* node = root;
    for(auto c : word){
      if ( !node->containsKey(c) ){
        return 0;
      }
      node = node->get(c);
    }
  }
 
} ;
 
void solve ( int cs ){
  Trie* trie = new Trie();

}

sample problem : https://www.spoj.com/status/ADAINDEX,mahdi_talukder/