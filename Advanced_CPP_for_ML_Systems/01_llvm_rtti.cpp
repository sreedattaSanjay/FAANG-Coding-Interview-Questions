/*
 * Module 1: LLVM-style RTTI (Run-Time Type Information)
 * 
 * In ML compilers (LLVM, MLIR, ONNX-MLIR), standard C++ RTTI (dynamic_cast) is 
 * often avoided because it is:
 * 1. Slow (requires traversing class hierarchy at runtime).
 * 2. Memory intensive (vtable overhead per class).
 * 3. Not available if RTTI is disabled (-fno-rtti).
 * 
 * Instead, these systems use a manual, lightweight RTTI system based on 
 * kind enums (discriminators).
 * 
 * This example demonstrates how to implement:
 * - Kind enums for type identification.
 * - isa<T>(x): Checks if x is of type T.
 * - cast<T>(x): Unsafely casts x to T (asserts on failure).
 * - dyn_cast<T>(x): Safely casts x to T, returning nullptr on failure.
 */

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

// 1. The Kind Enum - The core of manual RTTI
// Every class in the hierarchy will be assigned a unique Kind.
enum OperationKind {
    Kind_BinaryOp,
    Kind_UnaryOp,
    Kind_ConstantOp,
    Kind_ReturnOp
};

// 2. Base Class - Stores the Kind
class Operation {
public:
    OperationKind getKind() const { return kind; }
    virtual ~Operation() = default; 

protected:
    // Constructor is protected so only derived classes can set the valid kind
    Operation(OperationKind k) : kind(k) {}

private:
    const OperationKind kind;
};

// 3. Derived Classes
class BinaryOp : public Operation {
public:
    // Support for class hierarchy checking
    static bool classof(const Operation *op) {
        return op->getKind() == Kind_BinaryOp;
    }

    BinaryOp(std::string name) : Operation(Kind_BinaryOp), opName(name) {}
    
    void dump() { std::cout << "BinaryOp: " << opName << "\n"; }

private:
    std::string opName;
};

class UnaryOp : public Operation {
public:
    static bool classof(const Operation *op) {
        return op->getKind() == Kind_UnaryOp;
    }

    UnaryOp() : Operation(Kind_UnaryOp) {}
};

class ConstantOp : public Operation {
public:
    static bool classof(const Operation *op) {
        return op->getKind() == Kind_ConstantOp;
    }

    ConstantOp(int val) : Operation(Kind_ConstantOp), value(val) {}
    int getValue() const { return value; }

private:
    int value;
};

// 4. The Casting Infrastructure (Simplified LLVM Style)

// isa<T>(Val) - Returns true if Val is an instance of T
template <typename T, typename U>
bool isa(const U *Val) {
    return T::classof(Val);
}

// cast<T>(Val) - Casts Val to T, asserting if the check fails.
// Use this when you are 100% sure of the type.
template <typename T, typename U>
T *cast(U *Val) {
    assert(isa<T>(Val) && "cast<T>() argument of incompatible type!");
    return static_cast<T *>(Val);
}

// dyn_cast<T>(Val) - Casts Val to T if possible, otherwise returns nullptr.
// This is your safe runtime check (replacement for dynamic_cast).
template <typename T, typename U>
T *dyn_cast(U *Val) {
    return isa<T>(Val) ? static_cast<T *>(Val) : nullptr;
}


int main() {
    std::cout << "=== LLVM-Style RTTI Demo ===\n";

    // Create a heterogeneous list of operations (common in Compilers)
    std::vector<Operation*> ops;
    ops.push_back(new BinaryOp("Add"));
    ops.push_back(new ConstantOp(42));
    ops.push_back(new BinaryOp("Mul"));
    ops.push_back(new UnaryOp());

    std::cout << "Processing Operations:\n";
    for (Operation *op : ops) {
        
        // Example usage of dyn_cast (Safe Casting)
        // Similar to: if (auto *binOp = dynamic_cast<BinaryOp*>(op))
        if (BinaryOp *binOp = dyn_cast<BinaryOp>(op)) {
            std::cout << "  Found BinaryOp: ";
            binOp->dump();
        } 
        else if (isa<ConstantOp>(op)) {
            // Example usage of isa (Type Checking) and cast (Unsafe/Asserted Cast)
            // We know it's a ConstantOp because of isa check, so cast is safe.
            ConstantOp *constOp = cast<ConstantOp>(op);
            std::cout << "  Found ConstantOp: " << constOp->getValue() << "\n";
        }
        else {
            std::cout << "  Found Unknown/Other Op (Kind: " << op->getKind() << ")\n";
        }
    }

    // Cleanup
    for (auto op : ops) delete op;

    return 0;
}
