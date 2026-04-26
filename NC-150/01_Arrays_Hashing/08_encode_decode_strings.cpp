/*
 * LeetCode 271: Encode and Decode Strings
 * https://leetcode.com/problems/encode-and-decode-strings/
 * 
 * Design an algorithm to encode a list of strings to a string. 
 * The encoded string is then sent over the network and is decoded 
 * back to the original list of strings.
 * 
 * Time Complexity: O(n) where n is total length of all strings
 * Space Complexity: O(1) extra space (excluding output)
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Codec {
public:
    // Solution 1: Length-prefix encoding
    // Format: length + '#' + string content
    // Example: ["hello", "world"] -> "5#hello5#world"
    
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string encoded = "";
        for (const string& s : strs) {
            encoded += to_string(s.length()) + "#" + s;
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> result;
        int i = 0;
        
        while (i < s.length()) {
            // Find the delimiter '#'
            int j = i;
            while (s[j] != '#') {
                j++;
            }
            
            // Extract length
            int len = stoi(s.substr(i, j - i));
            
            // Extract string content
            string str = s.substr(j + 1, len);
            result.push_back(str);
            
            // Move to next encoded string
            i = j + 1 + len;
        }
        
        return result;
    }
};

// Alternative: Escape character encoding
class CodecEscape {
public:
    // Use delimiter and escape special characters
    // '/' is escape char, '//' means literal '/', '/:' is delimiter
    
    string encode(vector<string>& strs) {
        string encoded = "";
        for (const string& s : strs) {
            for (char c : s) {
                if (c == '/') {
                    encoded += "//";  // Escape the escape char
                } else {
                    encoded += c;
                }
            }
            encoded += "/:";  // Delimiter between strings
        }
        return encoded;
    }

    vector<string> decode(string s) {
        vector<string> result;
        string current = "";
        int i = 0;
        
        while (i < s.length()) {
            if (s[i] == '/' && i + 1 < s.length()) {
                if (s[i + 1] == '/') {
                    current += '/';  // Escaped slash
                    i += 2;
                } else if (s[i + 1] == ':') {
                    result.push_back(current);  // End of string
                    current = "";
                    i += 2;
                }
            } else {
                current += s[i];
                i++;
            }
        }
        
        return result;
    }
};

void printVector(vector<string>& v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << "\"" << v[i] << "\"";
        if (i < v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    Codec codec;
    
    // Test Case 1: Basic case
    vector<string> strs1 = {"Hello", "World"};
    string encoded1 = codec.encode(strs1);
    cout << "Test 1 Encoded: \"" << encoded1 << "\"" << endl;
    vector<string> decoded1 = codec.decode(encoded1);
    cout << "Test 1 Decoded: ";
    printVector(decoded1);
    // Expected: ["Hello", "World"]
    
    // Test Case 2: Empty strings
    vector<string> strs2 = {"", ""};
    string encoded2 = codec.encode(strs2);
    cout << "Test 2 Encoded: \"" << encoded2 << "\"" << endl;
    vector<string> decoded2 = codec.decode(encoded2);
    cout << "Test 2 Decoded: ";
    printVector(decoded2);
    // Expected: ["", ""]
    
    // Test Case 3: String with delimiter character
    vector<string> strs3 = {"a#b", "c#d"};
    string encoded3 = codec.encode(strs3);
    cout << "Test 3 Encoded: \"" << encoded3 << "\"" << endl;
    vector<string> decoded3 = codec.decode(encoded3);
    cout << "Test 3 Decoded: ";
    printVector(decoded3);
    // Expected: ["a#b", "c#d"]
    
    // Test Case 4: Empty list
    vector<string> strs4 = {};
    string encoded4 = codec.encode(strs4);
    cout << "Test 4 Encoded: \"" << encoded4 << "\"" << endl;
    vector<string> decoded4 = codec.decode(encoded4);
    cout << "Test 4 Decoded: ";
    printVector(decoded4);
    // Expected: []
    
    // Test Case 5: Numbers in strings
    vector<string> strs5 = {"123", "45#67"};
    string encoded5 = codec.encode(strs5);
    cout << "Test 5 Encoded: \"" << encoded5 << "\"" << endl;
    vector<string> decoded5 = codec.decode(encoded5);
    cout << "Test 5 Decoded: ";
    printVector(decoded5);
    // Expected: ["123", "45#67"]
    
    // Test Case 6: Single string
    vector<string> strs6 = {"single"};
    string encoded6 = codec.encode(strs6);
    cout << "Test 6 Encoded: \"" << encoded6 << "\"" << endl;
    vector<string> decoded6 = codec.decode(encoded6);
    cout << "Test 6 Decoded: ";
    printVector(decoded6);
    // Expected: ["single"]
    
    return 0;
}

