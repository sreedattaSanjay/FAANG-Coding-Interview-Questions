# Best Time to Buy and Sell Stock (LeetCode #121)

## Problem Statement

You are given an array `prices` where `prices[i]` is the price of a given stock on the `i`th day.

You want to maximize your profit by choosing a **single day** to buy one stock and choosing a **different day in the future** to sell that stock.

Return the **maximum profit** you can achieve from this transaction. If you cannot achieve any profit, return `0`.

### Examples

```
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6).
             Profit = 6 - 1 = 5.

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: No profitable transaction possible.
```

### Constraints
- 1 <= prices.length <= 10^5
- 0 <= prices[i] <= 10^4

## Intuition

We want to find the maximum `prices[j] - prices[i]` where `j > i`.

**Key insight**: For any selling day, the optimal buying day is the day with the **minimum price** seen so far (before the selling day).

As we iterate through prices:
1. Track the minimum price we've seen so far
2. Calculate potential profit if we sell today
3. Update maximum profit if current profit is higher

## Approach

### Approach 1: Track Minimum Price (Optimal)

```
1. Initialize minPrice = infinity, maxProfit = 0
2. For each price:
   a. minPrice = min(minPrice, price)
   b. profit = price - minPrice
   c. maxProfit = max(maxProfit, profit)
3. Return maxProfit
```

### Approach 2: Kadane's Algorithm Variant

Think of it as maximum subarray of daily changes:
- Daily change = prices[i] - prices[i-1]
- Maximum profit = maximum sum of consecutive daily changes

### Approach 3: Two Pointers

```
1. left = buy day, right = sell day
2. If prices[right] < prices[left]: left = right (found new minimum)
3. Else: calculate profit, update maximum
```

## Visual Walkthrough

### Example: prices = [7, 1, 5, 3, 6, 4]

```
Day   Price   MinPrice   Profit   MaxProfit
---   -----   --------   ------   ---------
0     7       7          0        0
1     1       1          0        0         ← new minimum!
2     5       1          4        4         ← profit possible
3     3       1          2        4
4     6       1          5        5         ← maximum profit!
5     4       1          3        5

Final answer: 5
```

### Graph Visualization

```
Price
7 |   *
6 |                   *
5 |           *
4 |                       *
3 |               *
2 |
1 |       *  (buy)---------(sell)
  +---+---+---+---+---+---+
  0   1   2   3   4   5   Day
  
Buy at day 1 (price=1), sell at day 4 (price=6)
Profit = 6 - 1 = 5
```

## Edge Cases Analysis

| Edge Case | Input Example | Expected Output | Why It's Tricky |
|-----------|---------------|-----------------|-----------------|
| Single element | `[5]` | `0` | No future day to sell |
| Two elements, profit | `[1, 5]` | `4` | Simple case |
| Two elements, loss | `[5, 1]` | `0` | No profit possible |
| Always decreasing | `[5, 4, 3, 2, 1]` | `0` | No valid transaction |
| Always increasing | `[1, 2, 3, 4, 5]` | `4` | Buy first, sell last |
| All same | `[3, 3, 3]` | `0` | No profit |
| Min at end | `[3, 2, 1]` | `0` | Can't sell in past |
| Best not at end | `[1, 5, 2]` | `4` | Don't always sell last |

## Complexity Analysis

- **Time Complexity**: O(n)
  - Single pass through the array
  
- **Space Complexity**: O(1)
  - Only using two variables

## Common Mistakes

1. **Not considering "can't profit" case**: Return 0, not negative
2. **Using future minimum**: We can only use past minimum prices
3. **Selling before buying**: j must be > i
4. **Nested loops**: O(n²) is too slow for 10^5 elements
5. **Resetting min incorrectly**: Min is a running minimum, not reset each day

## Related Problems

- [Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) - Multiple transactions
- [Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/) - At most 2 transactions
- [Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/) - At most k transactions
- [Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) - Related Kadane's algorithm

## Key Takeaways

1. **Track running minimum**: For "max difference" problems
2. **One pass is enough**: Don't need to look back
3. **Consider no-profit case**: Always check if profit can be 0
4. **Order matters**: Must buy before sell
5. **Simple is beautiful**: This clean O(n) solution is optimal

