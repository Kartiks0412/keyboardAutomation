#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    bool flag = false;
    Node* links[26];
    
    Node() {
        flag = false;
        for (int i = 0; i < 26; i++) {
            links[i] = nullptr;
        }
    }
    
    bool containsKey(char ch) { 
        return ch >= 'a' && ch <= 'z' && links[ch - 'a'] != nullptr; 
    }
    
    void put(char ch, Node* node) { 
        if (ch >= 'a' && ch <= 'z') {
            links[ch - 'a'] = node; 
        }
    }
    
    Node* get(char ch) { 
        if (ch >= 'a' && ch <= 'z') {
            return links[ch - 'a']; 
        }
        return nullptr;
    }
    
    bool isEnd() { return flag; }
    
    void setEnd() { flag = true; }
};

class Trie {
    Node* root;
    
    void dfs(Node* node, vector<string>& suggestions, string& path) {
        if (suggestions.size() == 3) return;
        
        if (node->isEnd()) {
            suggestions.push_back(path);
        }
        
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (node->containsKey(ch)) {
                path.push_back(ch);
                dfs(node->get(ch), suggestions, path);
                path.pop_back();
            }
        }
    }
    
public:
    Trie() { root = new Node(); }
    
    void addWord(string word) {
        // Convert to lowercase for consistency
        for (char &ch : word) {
            ch = tolower(ch);
        }
        
        Node* node = root;
        for (char ch : word) {
            if (ch >= 'a' && ch <= 'z') {  // Only add alphabetic characters
                if (!node->containsKey(ch)) {
                    node->put(ch, new Node());
                }
                node = node->get(ch);
            }
        }
        node->setEnd();
    }
    
    vector<string> giveSuggestions(string prefix) {
        // Convert prefix to lowercase
        for (char &ch : prefix) {
            ch = tolower(ch);
        }
        
        Node* node = root;
        for (char ch : prefix) {
            if (ch >= 'a' && ch <= 'z') {
                if (!node->containsKey(ch)) {
                    return {};
                }
                node = node->get(ch);
            }
        }
        
        string path = prefix;
        vector<string> suggestions;
        dfs(node, suggestions, path);
        return suggestions;
    }
};

Trie dictionary;

vector<string> split(string &s) {
    stringstream ss(s);
    string word;
    vector<string> res;
    while (ss >> word) {
        res.push_back(word);
    }
    return res;
}

string processCharInput(string &ip, string pressed) {
    ip += pressed;
    if (pressed == " ") {
        vector<string> words = split(ip);
        if (!words.empty()) {
            for(int i=0;i<words.size();i++){
                string currWord = words[i];
                dictionary.addWord(currWord);
            }
        }
    }
    return ip;
}

vector<string> giveSuggestions(string ip) {
    vector<string> words = split(ip);
    if (words.empty()) return {};
    
    string prefix = words.back();
    return dictionary.giveSuggestions(prefix);
}

void onSuggestionSelected(string &ip, const string &suggestion) {
    vector<string> words = split(ip);
    if (words.empty()) return;
    
    words.back() = suggestion;
    ip.clear();
    for (int i = 0; i < words.size(); ++i) {
        ip += words[i];
        if (i < words.size() - 1) ip += " ";
    }
    ip += " ";
    dictionary.addWord(suggestion);
}

int main() {
    string sentence;
    
    cout << "start typing manually or # for getting suggestions" << endl;
    cout << "! for quiting" << endl;
    
    while (true) {
        string pressed;
        cout << "Enter text: ";
        getline(cin, pressed);
        
        if (pressed == "!") break;

        if (pressed == "#") {
            vector<string> suggestions = giveSuggestions(sentence);
            if (!suggestions.empty()) {
                vector<string> words = split(sentence);
                cout << "suggestions based on " << sentence << endl;
                for (auto &t : suggestions) {
                    cout << t << " ";
                }
                cout << endl;
                cout << "out of " << suggestions.size() << " which suggestion do u want to select (1-" << suggestions.size() << "): ";
                int i = 0;
                cin >> i;
                cin.ignore(); // Clear the newline from input buffer
                i--;
                if (i < 0 || i >= suggestions.size()) {
                    cout << "out of range" << endl;
                    continue;
                }
                onSuggestionSelected(sentence, suggestions[i]);

                cout << "Selected suggestion: " << suggestions[i] << endl;
            } else {
                cout << "No suggestions available." << endl;
            }
        } else {
            string updated = processCharInput(sentence, pressed);
            cout << "Current sentence: " << updated << endl;
        }
    }

    cout << "Final sentence: " << sentence << endl;
    return 0;
}