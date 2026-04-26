# Valid Sudoku (LeetCode #36)

## Problem Statement

Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

1. Each **row** must contain the digits 1-9 without repetition.
2. Each **column** must contain the digits 1-9 without repetition.
3. Each of the nine **3x3 sub-boxes** must contain the digits 1-9 without repetition.

**Note**: A Sudoku board (partially filled) could be valid but is not necessarily solvable. Only the filled cells need to be validated.

### Examples

```
Input: board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true
```

### Constraints
- board.length == 9
- board[i].length == 9
- board[i][j] is a digit 1-9 or '.'

## Intuition

We need to check three constraints simultaneously:
1. No duplicate in any row
2. No duplicate in any column  
3. No duplicate in any 3x3 box

Key insight: Use **hash sets** to track seen numbers for each row, column, and box. If we encounter a number already in its respective set, the board is invalid.

**Box index formula**: For cell (i, j), its 3x3 box index is:
```
box_index = 3 * (i // 3) + (j // 3)
```

## Approach

### Approach 1: Three Sets (Rows, Cols, Boxes)

```
1. Create 9 sets for rows, 9 for columns, 9 for boxes
2. For each cell (i, j) with digit d:
   a. Calculate box index = 3 * (i // 3) + (j // 3)
   b. If d in rows[i] or cols[j] or boxes[box_index]: return false
   c. Add d to all three sets
3. Return true
```

### Approach 2: Single Set with Encoded Keys

```
1. Create single set
2. For each cell (i, j) with digit d:
   a. Create three keys: (d, "row", i), (d, "col", j), (d, "box", i//3, j//3)
   b. If any key exists in set: return false
   c. Add all three keys to set
3. Return true
```

### Approach 3: Bitmask

```
1. Use 9 integers for rows, cols, boxes (each bit represents a digit)
2. For digit d at (i, j):
   a. mask = 1 << d
   b. If (rows[i] & mask) or (cols[j] & mask) or (boxes[box_idx] & mask): return false
   c. Set the bit: rows[i] |= mask, etc.
```

## Visual Walkthrough

### Box Index Calculation

```
Board indices:
(0,0)(0,1)(0,2) | (0,3)(0,4)(0,5) | (0,6)(0,7)(0,8)
(1,0)(1,1)(1,2) | (1,3)(1,4)(1,5) | (1,6)(1,7)(1,8)
(2,0)(2,1)(2,2) | (2,3)(2,4)(2,5) | (2,6)(2,7)(2,8)
---------------+----------------+----------------
(3,0)(3,1)(3,2) | (3,3)(3,4)(3,5) | (3,6)(3,7)(3,8)
...

Box indices (3*(i//3) + j//3):
   0    0    0  |    1    1    1  |    2    2    2
   0    0    0  |    1    1    1  |    2    2    2
   0    0    0  |    1    1    1  |    2    2    2
---------------+----------------+----------------
   3    3    3  |    4    4    4  |    5    5    5
   3    3    3  |    4    4    4  |    5    5    5
   3    3    3  |    4    4    4  |    5    5    5
---------------+----------------+----------------
   6    6    6  |    7    7    7  |    8    8    8
   6    6    6  |    7    7    7  |    8    8    8
   6    6    6  |    7    7    7  |    8    8    8
```

### Example Validation

```
Processing cell (0,0) = '5':
- rows[0] = {} → add '5' → {5}
- cols[0] = {} → add '5' → {5}
- boxes[0] = {} → add '5' → {5}

Processing cell (0,1) = '3':
- rows[0] = {5} → add '3' → {5,3}
- cols[1] = {} → add '3' → {3}
- boxes[0] = {5} → add '3' → {5,3}

...

If we encounter '5' again in row 0:
- Check: '5' in rows[0]? → YES! → Return FALSE
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Empty board | All '.' | `true` | No constraints violated |
| Single number | One '5', rest '.' | `true` | Minimal valid case |
| Duplicate in row | Two '5's in row 0 | `false` | Row constraint |
| Duplicate in col | Two '5's in col 0 | `false` | Column constraint |
| Duplicate in box | Two '5's in box 0 | `false` | Box constraint |
| Same digit, different regions | '5' in row 0 and row 1 | `true` | Not a violation |
| Full valid board | Complete Sudoku | `true` | All constraints met |

## Complexity Analysis

Since the board is always 9x9:

- **Time Complexity**: O(81) = O(1)
  - We iterate through each cell exactly once
  - Set operations are O(1) on average
  
- **Space Complexity**: O(81) = O(1)
  - At most 9 elements in each of 27 sets (9 rows + 9 cols + 9 boxes)
  - Or 27 integers for bitmask approach

**Note**: If board was n×n, complexity would be O(n²)

## Common Mistakes

1. **Wrong box index formula**: It's `3*(i//3) + j//3`, not `i//3 + 3*(j//3)`
2. **Forgetting to skip '.'**: Empty cells should be ignored
3. **Character vs integer confusion**: '5' is a char, need proper handling
4. **Checking if board is solvable**: Problem only asks if current state is valid

## Related Problems

- [Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) - Actually solve the puzzle (backtracking)
- [Check if Every Row and Column Contains All Numbers](https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/) - Similar validation

## Key Takeaways

1. **Multiple constraint checking**: Use separate data structures for each constraint
2. **Box index formula**: `3*(row//3) + col//3` maps 2D position to 1D box index
3. **Bitmask optimization**: Use bits to represent presence of digits 1-9
4. **Fixed size = O(1)**: When input size is constant, complexity is constant
5. **Encoded keys in single set**: Alternative to multiple sets with tuple keys

