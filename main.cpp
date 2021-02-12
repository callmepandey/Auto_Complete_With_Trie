#include<bits/stdc++.h>
using namespace std;
vector <char> Characters = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
struct Trie{
    map < char , Trie* > children;
    bool found;
    Trie(){
        found = false;
    }
};
void insert(Trie *&root, string s){
    if(root==NULL){
        root = new Trie();
    }
    Trie *temp = root;
    for(int i = 0;i<s.size();i++){
        if(temp->children[s[i]]==NULL){
            temp->children[s[i]] = new Trie;
        }
        temp = temp->children[s[i]];
    }
    temp->found = true;
}
bool search(Trie *root, string s){
    for(int i = 0;i<s.size();i++){
        if(root->children[s[i]]==NULL) return false;
        root = root->children[s[i]];
    }
    if(root and root->found) return true;
    return false;
}

void FindSuggestion(string curretString,Trie *root,vector <string> &response){
    bool found = false;
    for(char c : Characters){
        if(root->children[c]){
            found = true;
        }
    }
    if(root->found){
        response.push_back(curretString);
    }
    if(found==false){
        return ;
    }
    for(char c : Characters){
        if(root->children[c]){
            FindSuggestion(curretString+c,root->children[c],response);
        }
    }
}
void finder(string s , Trie *root , string initial , vector <string> &response){
    for(char c : s){
        if(root->children[c]==NULL){
            return ;
        }
        initial.push_back(c);
        root = root->children[c];
    }
    FindSuggestion(initial,root,response);
    
}
int main(){
    Trie *root = new Trie();
    int n;
    cin >> n;
    string s;
    getline(cin,s);
    while(n--){
        getline(cin,s);
        insert(root,s);
    }
    int q;
    cin >> q;
    getline(cin,s);
    while(q--){
        getline(cin,s);
        vector <string> Suggestion;
        Suggestion.clear();
        string initial = "" ;
        finder(s ,  root , initial , Suggestion);
        if(Suggestion.size()==0){
            cout << "Oops Word Not Found \n";
        } else {
            cout << "Do You Mean ?" << endl;
            for(auto val : Suggestion){
                cout << val << endl;
            }
        }
    }
}
