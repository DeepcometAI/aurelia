# Aurelia Programming Language - AI & Data Science

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Version](https://img.shields.io/badge/version-0.1.0--alpha-orange.svg)](https://github.com/DeepcometAI/aurelia/releases)
[![Docs](https://img.shields.io/badge/docs-reference-green.svg)](./docs)
[![Status](https://img.shields.io/badge/status-Specification--First-lightgrey.svg)](#)

**Aurelia** is a next-generation systems programming language where neural computation is a **first-class compiler primitive**. Designed to eliminate legacy abstraction layers, it integrates tensor algebra, automatic differentiation, predictive memory allocation, and NPU targeting directly into the language runtime.

## 🚀 Quick Start

### Prerequisites
- C++23 compiler (clang++ ≥ 16, g++ ≥ 13)
- CMake ≥ 3.28
- LLVM ≥ 17, MLIR ≥ 17
- Python ≥ 3.10

### Building from Source
```bash
git clone https://github.com/DeepcometAI/aurelia.git
cd aurelia
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

### Hello World in Aurelia
```aurelia
# hello.aul
fn main() -> Result<(), IOError> {
    print("Hello, Aurelia!")
    
    # First-class tensor support
    let data = tensor<[4, 3], f32>([[1.0, 2.0, 3.0],
                                     [4.0, 5.0, 6.0],
                                     [7.0, 8.0, 9.0],
                                     [10.0, 11.0, 12.0]])
    
    # Automatic broadcasting and fusion
    let normalized = (data - mean(data)) / std(data)
    
    print(normalized)
    return Ok(())
}
```

Compile and run:
```bash
aulc hello.aul -o hello
./hello
```

## 📚 Key Features

### 1. First-Class Tensor Primitives
```aurelia
type Batch = Dim<symbol: "B", range: 1..4096>
type Embedding = Dim<symbol: "D", value: 768>

let q: tensor<[Batch, Embedding], f32, normalized>
let out = q |> matmul(w) |> layer_norm |> dropout(0.1)
```

### 2. Automatic Differentiation
```aurelia
@differentiable
fn loss(pred: tensor<[N], f32>, target: tensor<[N], f32>) -> f32 {
    return sum((pred - target)^2) / N
}

# Compiler automatically generates gradient function
let grad = autodiff(loss, wrt: [pred])
```

### 3. Predictive Memory Allocation
```aurelia
fn process_stream(mut pool: MemoryPool, input: Stream<tensor<[N], f32>>) {
    for chunk in input {
        predict_next(chunk.next_window())  # L1/NPU prefetch
        let view = chunk.borrow()          # Zero-alias borrow
        compute(view)
    }
}
```

### 4. Native Parallel Execution
```aurelia
@parallel for i in 0..batch_size {
    async { model.infer(fetch_sample(i))? }
}
```

### 5. Paper-First Verification
```aurelia
@paper { title: "Sparse Attention", version: "0.2.0" }

@invariant("softmax_mass")
fn softmax_preserves_mass(logits: tensor<[N], f32>) -> bool {
    sum(softmax(logits, axis=-1)) ≈ 1.0
}
```

## 🏗️ Architecture

```
.aul source → Lexer/Parser → AST
                 ↓
    Type Checker + Borrow Analyzer + Shape Solver
                 ↓
       MLIR Lowering (Tensor, Linalg, Autodiff)
                 ↓
     Optimization: Fusion → Prefetch → Tiling
                 ↓
       LLVM Codegen + GPU/NPU Backend
                 ↓
          Aurelia Runtime (Zero-copy, Deterministic)
```

## 📖 Documentation

- [Language Specification](./docs/specification.md)
- [Standard Library Reference](./docs/stdlib.md)
- [Compiler Internals](./docs/compiler.md)
- [Examples Gallery](./examples/)

## 🛣️ Roadmap

| Phase | Milestone | Target |
|-------|-----------|--------|
| Q4 2026 | Alpha Compiler | Lexer, Parser, Basic Type Checker |
| Q1 2027 | MLIR Integration | Tensor Dialect, Autodiff Graph |
| Q2 2027 | GPU Codegen | CUDA/SYCL Backend |
| Q3 2027 | Beta Release | REPL, LSP, Standard Library |
| Q4 2027 | Production Ready | NPU Support, Optimization Passes |

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md) for details.

## 📄 License

MIT License - see [LICENSE](LICENSE) for details.

## 🌌 Part of Deepcomet AI's Vertical Stack

Aurelia is Phase 1 of Deepcomet AI Inc.'s vertical AI ecosystem:
- **Phase 1**: Aurelia Language (this project)
- **Phase 2**: Zenith Probabilistic Kernel
- **Phase 3**: SkyOS Generative Operating System
- **Phase 4**: DeepComet AI Model Family
- **Phase 5**: Enterprise Infrastructure & Cloud

---

*Built with ❤️ for the future of AI-native systems*
