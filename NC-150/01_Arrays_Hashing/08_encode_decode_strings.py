"""
LeetCode 271: Encode and Decode Strings
https://leetcode.com/problems/encode-and-decode-strings/

Design an algorithm to encode a list of strings to a string. 
The encoded string is then sent over the network and is decoded 
back to the original list of strings.

Time Complexity: O(n) where n is total length of all strings
Space Complexity: O(1) extra space (excluding output)
"""

from typing import List


class Codec:
    """
    Solution 1: Length-prefix encoding
    Format: length + '#' + string content
    Example: ["hello", "world"] -> "5#hello5#world"
    """
    
    def encode(self, strs: List[str]) -> str:
        """Encodes a list of strings to a single string."""
        encoded = ""
        for s in strs:
            encoded += str(len(s)) + "#" + s
        return encoded

    def decode(self, s: str) -> List[str]:
        """Decodes a single string to a list of strings."""
        result = []
        i = 0
        
        while i < len(s):
            # Find the delimiter '#'
            j = i
            while s[j] != '#':
                j += 1
            
            # Extract length
            length = int(s[i:j])
            
            # Extract string content
            result.append(s[j + 1:j + 1 + length])
            
            # Move to next encoded string
            i = j + 1 + length
        
        return result


class CodecChunked:
    """
    Solution 2: Fixed-size length prefix (4 bytes)
    More robust for binary data
    """
    
    def encode(self, strs: List[str]) -> str:
        encoded = ""
        for s in strs:
            # 4-character zero-padded length
            encoded += f"{len(s):04d}" + s
        return encoded

    def decode(self, s: str) -> List[str]:
        result = []
        i = 0
        
        while i < len(s):
            length = int(s[i:i + 4])
            result.append(s[i + 4:i + 4 + length])
            i = i + 4 + length
        
        return result


class CodecEscape:
    """
    Solution 3: Escape character encoding
    Use delimiter and escape special characters
    """
    
    def encode(self, strs: List[str]) -> str:
        # Use '/' as escape, '/:' as delimiter
        encoded = ""
        for s in strs:
            for c in s:
                if c == '/':
                    encoded += "//"
                else:
                    encoded += c
            encoded += "/:"
        return encoded

    def decode(self, s: str) -> List[str]:
        result = []
        current = ""
        i = 0
        
        while i < len(s):
            if s[i] == '/' and i + 1 < len(s):
                if s[i + 1] == '/':
                    current += '/'
                    i += 2
                elif s[i + 1] == ':':
                    result.append(current)
                    current = ""
                    i += 2
            else:
                current += s[i]
                i += 1
        
        return result


if __name__ == "__main__":
    codec = Codec()
    
    # Test Case 1: Basic case
    strs1 = ["Hello", "World"]
    encoded1 = codec.encode(strs1)
    print(f"Test 1 Encoded: \"{encoded1}\"")
    decoded1 = codec.decode(encoded1)
    print(f"Test 1 Decoded: {decoded1}")
    # Expected: ["Hello", "World"]
    
    # Test Case 2: Empty strings
    strs2 = ["", ""]
    encoded2 = codec.encode(strs2)
    print(f"Test 2 Encoded: \"{encoded2}\"")
    decoded2 = codec.decode(encoded2)
    print(f"Test 2 Decoded: {decoded2}")
    # Expected: ["", ""]
    
    # Test Case 3: String with delimiter character
    strs3 = ["a#b", "c#d"]
    encoded3 = codec.encode(strs3)
    print(f"Test 3 Encoded: \"{encoded3}\"")
    decoded3 = codec.decode(encoded3)
    print(f"Test 3 Decoded: {decoded3}")
    # Expected: ["a#b", "c#d"]
    
    # Test Case 4: Empty list
    strs4 = []
    encoded4 = codec.encode(strs4)
    print(f"Test 4 Encoded: \"{encoded4}\"")
    decoded4 = codec.decode(encoded4)
    print(f"Test 4 Decoded: {decoded4}")
    # Expected: []
    
    # Test Case 5: Numbers in strings
    strs5 = ["123", "45#67"]
    encoded5 = codec.encode(strs5)
    print(f"Test 5 Encoded: \"{encoded5}\"")
    decoded5 = codec.decode(encoded5)
    print(f"Test 5 Decoded: {decoded5}")
    # Expected: ["123", "45#67"]
    
    # Test Case 6: Single string
    strs6 = ["single"]
    encoded6 = codec.encode(strs6)
    print(f"Test 6 Encoded: \"{encoded6}\"")
    decoded6 = codec.decode(encoded6)
    print(f"Test 6 Decoded: {decoded6}")
    # Expected: ["single"]

