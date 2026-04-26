# Koko Eating Bananas (LeetCode #875)

## Problem Statement

Koko loves to eat bananas. There are `n` piles of bananas with `piles[i]` bananas in each pile. She can eat `k` bananas per hour. Each hour, she chooses a pile and eats `k` bananas from it. If the pile has less than `k` bananas, she eats all of them and won't eat any more bananas during that hour.

Return the minimum integer `k` such that she can eat all bananas within `h` hours.

### Examples

```
Input: piles = [3,6,7,11], h = 8
Output: 4
Explanation: With k=4, hours needed = ceil(3/4)+ceil(6/4)+ceil(7/4)+ceil(11/4) = 1+2+2+3 = 8

Input: piles = [30,11,23,4,20], h = 5
Output: 30
```

## Intuition

This is a **"binary search on answer"** problem:
- The answer (eating speed k) is in range [1, max(piles)]
- If Koko can finish with speed k, she can finish with any speed > k
- We want the MINIMUM k that works

## Approach

```
1. Search space: [1, max(piles)]
2. For each mid speed:
   - Calculate hours needed
   - If can finish: try smaller speed (right = mid)
   - If can't: need faster speed (left = mid + 1)
3. Return left (minimum valid speed)
```

## Key Formula

Hours to eat pile of size `p` at speed `k`:
```
hours = ceil(p / k) = (p + k - 1) / k
```

## Complexity Analysis

- **Time**: O(n × log(max(piles)))
- **Space**: O(1)

## Key Takeaways

1. **Binary search on answer**: Search the result space, not the input
2. **Monotonic property**: Higher k always finishes faster
3. **Finding minimum**: Use `right = mid` when condition is true

