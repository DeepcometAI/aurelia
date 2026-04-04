# Aurelia Language Specification

## Overview

Aurelia is a statically-typed, AI-native systems programming language designed for high-performance machine learning and data science workloads. This document specifies the core language features, syntax, and semantics.

## 1. Lexical Structure

### 1.1 Comments
```aurelia
# This is a single-line comment
# Comments start with # and extend to end of line
```

### 1.2 Identifiers
Identifiers start with a letter or underscore, followed by letters, digits, or underscores.
```aurelia
variable_name
_my_var
Tensor123
```

### 1.3 Keywords
Reserved keywords include:
- `fn`, `let`, `mut`, `type`, `struct`, `enum`
- `match`, `if`, `else`, `for`, `while`, `return`
- `async`, `await`, `parallel`, `tensor`, `dim`
- `true`, `false`

### 1.4 Literals
```aurelia
# Integers
42
-17
0xFF          # Hexadecimal
0b1010        # Binary

# Floats
3.14
2.5e-3
1.0e+10

# Strings
"Hello, World!"
"Escape sequences: \n \t \\ \""

# Booleans
true
false
```

## 2. Types

### 2.1 Primitive Types
- `i8`, `i16`, `i32`, `i64` - Signed integers
- `u8`, `u16`, `u32`, `u64` - Unsigned integers
- `f32`, `f64` - Floating point
- `bool` - Boolean
- `string` - String type

### 2.2 Tensor Types
```aurelia
# Fixed shape tensor
let t: tensor<[4, 3], f32>

# Symbolic dimensions
type Batch = Dim<symbol: "B", range: 1..4096>
type Embedding = Dim<symbol: "D", value: 768>
let q: tensor<[Batch, Embedding], f32>

# With attributes
let normalized: tensor<[N], f32, normalized>
let trainable: tensor<[M, N], f32, trainable, grad>
```

### 2.3 Generic Types
```aurelia
Option<T>
Result<T, E>
Array<T>
Stream<T>
```

## 3. Expressions

### 3.1 Arithmetic
```aurelia
let sum = a + b
let diff = x - y
let product = m * n
let quotient = a / b
let remainder = x % y
let power = base ^ exp
```

### 3.2 Comparison
```aurelia
a == b      # Equal
a != b      # Not equal
a < b       # Less than
a > b       # Greater than
a <= b      # Less than or equal
a >= b      # Greater than or equal
```

### 3.3 Pipe Operator
```aurelia
# Function composition
let result = x |> f |> g |> h

# Equivalent to: h(g(f(x)))
```

### 3.4 Formula Syntax (R-style)
```aurelia
# Statistical modeling
let model = y ~ x1 + x2 + bias
let interaction = y ~ x1 * x2 + log(x3)
```

### 3.5 Tensor Operations
```aurelia
# Broadcasting
let residuals = y - predictions

# Element-wise operations
let squared = x ^ 2
let normalized = (x - mean(x)) / std(x)

# Matrix operations
let product = matmul(A, B)
let transpose = A.T
```

## 4. Statements

### 4.1 Variable Declaration
```aurelia
# Immutable binding
let x = 42
let pi: f64 = 3.14159

# Mutable binding
mut counter = 0
mut buffer: tensor<[N], f32> = zeros([N])
```

### 4.2 Functions
```aurelia
fn add(a: i32, b: i32) -> i32 {
    return a + b
}

# With type inference
fn multiply(a, b) {
    return a * b
}

# Differentiable function
@differentiable
fn loss(pred: tensor<[N], f32>, target: tensor<[N], f32>) -> f32 {
    return sum((pred - target)^2) / N
}
```

### 4.3 Control Flow
```aurelia
# If expression
let max_val = if a > b { a } else { b }

# For loop
for i in 0..n {
    print(i)
}

# Parallel for loop
@parallel for i in 0..batch_size {
    process(item[i])
}

# While loop
while condition {
    # ...
}
```

### 4.4 Pattern Matching
```aurelia
match value {
    Ok(x) => print(f"Success: {x}"),
    Err(e) => print(f"Error: {e}")
}

match shape {
    [n] => print(f"Vector of length {n}"),
    [m, n] => print(f"Matrix {m}x{n}"),
    _ => print("Unknown shape")
}
```

## 5. Advanced Features

### 5.1 Automatic Differentiation
```aurelia
@differentiable
fn forward(x: tensor<[N], f32>, w: tensor<[N, M], f32>) -> tensor<[M], f32> {
    return softmax(matmul(x, w))
}

# Compiler generates gradient function
let grads = autodiff(forward, wrt: [x, w])
```

### 5.2 Async & Concurrency
```aurelia
# Async block
async {
    let data = await fetch_data()
    process(data)
}

# Structured concurrency
@parallel for i in 0..n {
    async { process_async(items[i]) }
}
```

### 5.3 Memory Management
```aurelia
# Predictive prefetch
fn stream_process(input: Stream<tensor<[N], f32>>) {
    for chunk in input {
        predict_next(chunk.next_window())
        let view = chunk.borrow()
        compute(view)
    }
}

# Deterministic memory pools
fn allocate(mut pool: MemoryPool, size: usize) -> Tensor {
    return pool.alloc(size)
}
```

### 5.4 Annotations
```aurelia
# Paper provenance
@paper { title: "My Algorithm", version: "1.0" }

# Invariants
@invariant("positive_definite")
fn check_matrix(m: tensor<[N, N], f32>) -> bool {
    return all(eigenvalues(m) > 0)
}

# Experiments
@experiment("benchmark")
fn measure_performance() -> Benchmark {
    # ...
}
```

## 6. Error Handling

### 6.1 Result Type
```aurelia
fn divide(a: f64, b: f64) -> Result<f64, DivisionError> {
    if b == 0.0 {
        return Err(DivisionError::ByZero)
    }
    return Ok(a / b)
}

# Pattern matching on results
match divide(10.0, 2.0) {
    Ok(result) => print(f"Result: {result}"),
    Err(e) => print(f"Error: {e}")
}

# Propagation with ?
fn compute() -> Result<(), IOError> {
    let data = load_file("data.bin")?
    process(data)?
    return Ok(())
}
```

### 6.2 Option Type
```aurelia
fn find_first(pred: fn(T) -> bool, items: Array<T>) -> Option<T> {
    for item in items {
        if pred(item) {
            return Some(item)
        }
    }
    return None
}
```

## 7. Modules and Imports

```aurelia
# Import module
import numpy as np
import aurelia.tensor as tensor

# Selective import
from aurelia.nn import Linear, ReLU, Dropout

# Relative import
from ..utils import helper_function
```

## 8. FFI and Interoperability

```aurelia
# Call C functions
extern "C" {
    fn cuda_malloc(size: usize) -> *mut void
    fn cuda_free(ptr: *mut void)
}

# Python interoperability
@python
def python_helper(x):
    import numpy as np
    return np.array(x)
```

---

*This specification is under active development. Features may change before the 1.0 release.*
