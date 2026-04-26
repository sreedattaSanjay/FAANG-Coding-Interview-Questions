# LLVM-Style RTTI (Run-Time Type Information)

In the codebase of **LLVM**, **MLIR**, and **onnx-mlir**, you will rarely see C++'s standard `dynamic_cast`. Instead, you will see `isa<>`, `cast<>`, and `dyn_cast<>`.

## Why not `dynamic_cast`?

Standard C++ RTTI (`dynamic_cast` and `typeid`) has significant downsides for high-performance compilers:
1.  **Memory Overhead**: It requires extra storage per class (vtables) and per object.
2.  **Performance Check**: `dynamic_cast` often involves traversing the class inheritance tree at runtime (string comparisons or tree walks), which is slow when doing millions of checks during compilation.
3.  **Flexibility**: You cannot easily disable it or customize it.

## The Solution: "Kind" Enums

LLVM uses a hand-rolled RTTI system where types are identified by an `enum` (the "Kind").

### 1. `isa<T>(val)`
**"Is A"**. Returns `true` if `val` is an instance of class `T`.
- **Implementation**: Calls `T::classof(val)`.
- **Usage**: Used for branching logic.
```cpp
if (isa<AddOp>(op)) { /* ... */ }
```

### 2. `cast<T>(val)`
**"Cast"**. Casts `val` to `T*`.
- **Safety**: **Unsafe**. It asserts (crashes) if `isa<T>(val)` is false.
- **Performance**: Zero-cost at runtime in release builds (it becomes just a raw pointer cast).
- **Usage**: Use when you have already verified the type or are architecturally certain.
```cpp
// verified by surrounding logic
AddOp *add = cast<AddOp>(op); 
```

### 3. `dyn_cast<T>(val)`
**"Dynamic Cast"**. Casts `val` to `T*` if valid, otherwise returns `nullptr`.
- **Safety**: Safe.
- **Performance**: Faster than `dynamic_cast` because it just checks an enum integer comparison.
- **Usage**: Perfect for `if` conditions.
```cpp
if (auto *add = dyn_cast<AddOp>(op)) {
    // add is valid here
    add->doSomething();
}
```

## How It Works Under the Hood

The magic relies on every class determining if it matches a given `Kind`.

1.  **Base Class**: Stores the Kind ID.
2.  **Derived Class**: Implements a static `classof(const Base*)` method.

```cpp
// In the Derived Class (e.g., BinaryOp)
static bool classof(const Operation *op) {
    return op->getKind() == Kind_BinaryOp;
}
```

When you call `isa<BinaryOp>(op)`, it compiles down to:
`op->getKind() == Kind_BinaryOp`

This is an **O(1) integer comparison**, which is blazing fast compared to standard RTTI!
