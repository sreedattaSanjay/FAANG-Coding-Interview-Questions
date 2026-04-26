# Car Fleet (LeetCode #853)

## Problem Statement

There are `n` cars going to the same destination along a one-lane road. The destination is `target` miles away.

You are given two integer arrays `position` and `speed`, both of length `n`, where `position[i]` is the position of the `i`th car and `speed[i]` is the speed of the `i`th car (miles per hour).

A **car fleet** is some non-empty set of cars driving at the same position and same speed. A car can catch up to a car in front of it and join its fleet (can't pass - single lane!).

Return the **number of car fleets** that will arrive at the destination.

### Examples

```
Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
Explanation:
- Car at position 10 reaches at time 1.0
- Car at position 8 reaches at time 1.0, catches up with car at 10
- Car at position 0 reaches at time 12.0
- Cars at 5 and 3 form a fleet

Three fleets: {10, 8}, {5, 3}, {0}
```

### Constraints
- n == position.length == speed.length
- 1 <= n <= 10^5
- 0 < target <= 10^6
- 0 <= position[i] < target
- All positions are unique
- 0 < speed[i] <= 10^6

## Intuition

**Key insight**: A car can only form a fleet with cars AHEAD of it. If a faster car is behind a slower car, it catches up. If a slower car is behind a faster car, they never meet.

**Algorithm**:
1. Calculate time for each car to reach target (if no blocking)
2. Sort cars by position (closest to target first)
3. Process from front: if current car is slower than the fleet ahead, it forms a new fleet

## Approach

```
1. Calculate time[i] = (target - position[i]) / speed[i]
2. Sort by position (descending)
3. For each car:
   - If time > stack.top(): new fleet (push time)
   - Else: catches up (don't push)
4. Return stack size (number of fleets)
```

## Visual Walkthrough

### Example: target=12, pos=[10,8,0,5,3], speed=[2,4,1,1,3]

```
Calculate times:
Car at 10: (12-10)/2 = 1.0 hours
Car at 8:  (12-8)/4  = 1.0 hours
Car at 0:  (12-0)/1  = 12.0 hours
Car at 5:  (12-5)/1  = 7.0 hours
Car at 3:  (12-3)/3  = 3.0 hours

Sort by position (descending):
Position: 10   8    5    3    0
Time:     1.0  1.0  7.0  3.0  12.0

Process:
- Car at 10: time=1.0, stack=[], push → stack=[1.0]
- Car at 8:  time=1.0 <= 1.0, catches up (fleet!)
- Car at 5:  time=7.0 > 1.0, new fleet → stack=[1.0, 7.0]
- Car at 3:  time=3.0 <= 7.0, catches up to fleet ahead
- Car at 0:  time=12.0 > 7.0, new fleet → stack=[1.0, 7.0, 12.0]

Number of fleets: 3
```

## Edge Cases Analysis

| Edge Case | Input | Expected | Why |
|-----------|-------|----------|-----|
| Single car | `pos=[0]` | 1 | One car = one fleet |
| All same speed | `pos=[1,2,3], speed=[1,1,1]` | 3 | Never catch up |
| All catch up | `pos=[0,1,2], speed=[3,2,1]` | 1 | Fastest behind |
| Two cars swap | `pos=[0,4], speed=[2,1]` | 1 | Faster catches slower |

## Complexity Analysis

- **Time Complexity**: O(n log n)
  - Sorting dominates
  - Single pass through sorted array
  
- **Space Complexity**: O(n)
  - Array of cars
  - Stack for fleets

## Common Mistakes

1. **Wrong sort order**: Must process from closest to target
2. **Integer division**: Use floating point for time
3. **Strict vs non-strict**: A car can catch up if time <= fleet time
4. **Not understanding fleet formation**: Cars merge, don't pass

## Why Stack Works

Stack maintains fleets in order:
- Each element represents a fleet's arrival time
- When a car has a larger time than top, it's slower and can't catch up
- When a car has smaller/equal time, it catches up (doesn't create new fleet)

## Related Problems

- [Car Fleet II](https://leetcode.com/problems/car-fleet-ii/) - Harder variant
- [Number of Collisions](https://leetcode.com/problems/count-collisions-on-a-road/)

## Key Takeaways

1. **Sort by position**: Process from front to back
2. **Time to target**: Key metric for comparison
3. **Stack for fleet tracking**: Monotonic increasing times
4. **Catching up = not creating new fleet**: Time comparison

