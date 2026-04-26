# Encode and Decode Strings (LeetCode #271)

## Problem Statement

Design an algorithm to **encode** a list of strings to a single string. The encoded string is then sent over the network and is **decoded** back to the original list of strings.

Implement the `Codec` class:
- `encode(strs)`: Encodes a list of strings to a single string.
- `decode(s)`: Decodes a single string to a list of strings.

### Examples

```
Input: ["Hello","World"]
Encoded: "5#Hello5#World" (using length-prefix method)
Decoded: ["Hello","World"]

Input: [""]
Encoded: "0#"
Decoded: [""]
```

### Constraints
- 1 <= strs.length <= 200
- 0 <= strs[i].length <= 200
- strs[i] contains any possible characters out of 256 valid ASCII characters

## Intuition

The challenge is to encode multiple strings into one string such that we can **unambiguously decode** it back. The tricky part: strings can contain **any character**, including whatever delimiter we might choose.

**Key insight**: We can't use a simple delimiter because the strings might contain that delimiter. Instead, we use **length-prefix encoding**:
- Prefix each string with its length
- Use a delimiter between length and content

Format: `length#content`

Since we know the exact length, we can extract exactly that many characters, regardless of what they contain (even '#' characters).

## Approach

### Approach 1: Length-Prefix Encoding (Optimal)

**Encoding**:
```
For each string s:
    append len(s) + "#" + s
```

**Decoding**:
```
While not at end:
    1. Find '#' to get length
    2. Read next 'length' characters as the string
    3. Move pointer forward
```

### Approach 2: Escape Character Encoding

**Encoding**:
```
For each string s:
    Escape special characters
    Append escaped string + delimiter
```

**Decoding**:
```
Parse character by character
Handle escape sequences
Split on delimiter
```

### Approach 3: Fixed-Size Length Prefix

```
For each string s:
    Append 4-byte length (padded) + s
```

## Visual Walkthrough

### Example: ["Hello", "World"]

**Encoding Process**:
```
"Hello" → length=5 → "5#Hello"
"World" → length=5 → "5#World"

Combined: "5#Hello5#World"
```

**Decoding Process**:
```
Input: "5#Hello5#World"
       ^

Step 1: Find '#' at position 1
        Length = "5" = 5
        Extract s[2:2+5] = "Hello"
        Move to position 7

        "5#Hello5#World"
               ^

Step 2: Find '#' at position 8
        Length = "5" = 5
        Extract s[9:9+5] = "World"
        Move to position 14 (end)

Result: ["Hello", "World"]
```

### Handling Edge Cases

```
["a#b", "c#d"]

Encoding:
"a#b" → length=3 → "3#a#b"
"c#d" → length=3 → "3#c#d"

Combined: "3#a#b3#c#d"

Decoding:
"3#a#b3#c#d"
 ^
Length = 3, extract "a#b" (next 3 chars after #)
        ^
Length = 3, extract "c#d"

The '#' inside the string doesn't confuse us because we know exactly how many characters to read!
```

## Edge Cases Analysis

| Edge Case | Input Example | Encoded | Why It Works |
|-----------|---------------|---------|--------------|
| Empty list | `[]` | `""` | Nothing to encode |
| Empty strings | `["", ""]` | `"0#0#"` | Length 0 means read 0 chars |
| Contains '#' | `["a#b"]` | `"3#a#b"` | Length tells us to read 3 chars |
| Contains numbers | `["123"]` | `"3#123"` | We find '#' first, then read |
| Long string | `["a"*1000]` | `"1000#aaa..."` | Length handles any size |
| Unicode | `["你好"]` | Varies by encoding | Length in bytes or chars |

## Complexity Analysis

- **Time Complexity**: O(n)
  - n = total length of all strings combined
  - Each character is processed once in encoding and decoding
  
- **Space Complexity**: O(1) extra space
  - Output space doesn't count
  - Only use a few pointers/indices

## Common Mistakes

1. **Using simple delimiter**: `["a,b", "c"]` → `"a,b,c"` → Can't decode properly!
2. **Not handling empty strings**: Empty string has length 0, not absent
3. **Off-by-one in length extraction**: Carefully track where length ends and content begins
4. **Unicode length issues**: String length in characters vs bytes can differ

## Why Other Approaches Fail

### Simple Delimiter (e.g., comma)
```
["a,b", "c,d"] → "a,b,c,d" → ["a", "b", "c", "d"] ✗
```

### Escape Characters Only
```
Escaping every special character is complex and error-prone
May increase string length significantly
```

## Related Problems

- [Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) - Similar concept for trees
- [Serialize and Deserialize BST](https://leetcode.com/problems/serialize-and-deserialize-bst/)

## Key Takeaways

1. **Length-prefix encoding**: Classic technique for serialization
2. **Self-describing format**: Length tells you exactly how many bytes to read
3. **Network protocols use this**: HTTP, TCP, protobuf all use length-prefixing
4. **Delimiter choice matters**: Length prefix avoids delimiter conflicts entirely
5. **Think about all possible inputs**: Any 256 ASCII characters means can't rely on special chars

