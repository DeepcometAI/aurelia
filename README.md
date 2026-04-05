
# 🌌 Aurelia Programming Language
> *The "Speed of Light" AI-Native Systems Language | Phase 1 of Deepcomet AI Inc.'s Vertical AI Stack*

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Version](https://img.shields.io/badge/version-0.1.0--alpha-orange.svg)](https://github.com/DeepcometAI/aurelia/releases)
[![Docs](https://img.shields.io/badge/docs-reference-green.svg)](./docs)
[![Status](https://img.shields.io/badge/status-Specification--First-lightgrey.svg)](#)
[![C++](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](#)
[![Go](https://img.shields.io/badge/Go-1.22%2B-00ADD8.svg)](#)

**Aurelia** is a next-generation systems programming language where neural computation is a **first-class compiler primitive**. Designed to eliminate legacy abstraction layers, it integrates tensor algebra, automatic differentiation, predictive memory allocation, and NPU targeting directly into the language runtime. Aurelia serves as the foundational layer of Deepcomet AI Inc.'s vertical AI ecosystem, enabling seamless progression from Language → Kernel → OS → AI Models.

Aurelia's implementation is powered by a **dual-language engineering strategy**: **C++23** for the performance-critical compiler core, runtime, and MLIR/LLVM integration, and **Go 1.22+** for the developer-facing toolchain — the CLI (`aulc`), LSP server, package manager, test harness, and build orchestration. This combination delivers both raw systems performance where it matters and developer ergonomics where it counts.

> ⚠️ **Transparency Notice**: This repository is in **early specification phase**. All core compiler, runtime, and tooling components are currently **not started**. This document serves as both technical reference and public development tracker.

---

## 📖 Table of Contents
1. [The Deepcomet AI Vision & Strategic Context](#1-the-deepcomet-ai-vision--strategic-context)
2. [Core Philosophy & Multi-Paradigm Design](#2-core-philosophy--multi-paradigm-design)
3. [Compiler Architecture & Technology Stack](#3-compiler-architecture--technology-stack)
4. [Dual-Language Strategy: C++23 & Go](#4-dual-language-strategy-c23--go)
5. [Language Features & Syntax Deep Dive](#5-language-features--syntax-deep-dive)
6. [Advanced Semantics & Formal Verification](#6-advanced-semantics--formal-verification)
7. [Component Progress Tracker & Development Status](#7-component-progress-tracker--development-status)
8. [Deepcomet AI Ecosystem Roadmap Alignment](#8-deepcomet-ai-ecosystem-roadmap-alignment)
9. [Engineering Standards, Tooling & CI/CD](#9-engineering-standards-tooling--cicd)
10. [Contributing Guidelines & Community](#10-contributing-guidelines--community)
11. [Licensing, Contact & Appendices](#11-licensing-contact--appendices)

---

## 1. The Deepcomet AI Vision & Strategic Context

Traditional software stacks bolt AI onto 30-year-old operating systems using library wrappers (`import torch`, `pip install tensorflow`). Deepcomet AI Inc. takes a fundamentally different approach: **Vertical AI Integration**. By building the language, kernel, OS, and models in-house, Deepcomet AI ensures that AI isn't running *on* the system — it *is* the system.

### 🔹 The Five-Phase Master Plan

| Phase | Objective | Deliverable | Status |
|-------|-----------|-------------|--------|
| **Phase 1** | AI-Native Systems Language | Aurelia Compiler & Runtime | 🔴 Specification |
| **Phase 2** | Probabilistic Microkernel | Zenith Kernel (10ms-ahead scheduler) | ⚪ Planned |
| **Phase 3** | Generative Operating System | SkyOS (LAM Interface, SFS) | ⚪ Planned |
| **Phase 4** | Tiered AI Model Family | DeepComet-Prime, Zenith, Code, Mobile | ⚪ Planned |
| **Phase 5** | Monetization & Infrastructure | Private Brain, Migration Forge, SkyCloud | ⚪ Planned |

Aurelia is the critical first step. It establishes the mathematical guarantees, hardware-aware execution model, and deterministic memory patterns required for every subsequent layer. Without a language designed for tensor algebra, predictive allocation, and formal verification, the Zenith Kernel's immune system and SkyOS's generative UI cannot achieve their latency or reliability targets.

> **Competitive Advantage**: By controlling the entire stack, Deepcomet AI bypasses legacy BIOS limitations, eliminates context-switch overhead between language/runtime/OS, and achieves true hardware-software synthesis. AI becomes the native execution model, not an external workload.

---

## 2. Core Philosophy & Multi-Paradigm Design

Traditional languages treat AI as an add-on. Aurelia integrates neural computation directly into the compiler, targeting **10× faster model training and inference** than Python/C++ wrappers while maintaining human-readable syntax and enterprise-grade safety.

| Design Pillar | Implementation Strategy | Target Benefit |
|---------------|------------------------|----------------|
| 🐍 **Python Readability** | Indentation-based blocks, minimal punctuation, implicit returns | Low cognitive overhead for researchers & engineers |
| ☕ **Java Robustness** | Strict static typing, `Option<T>`/`Result<T,E>`, zero `null`, exhaustive matching | Elimination of silent failures, NPEs, and unhandled errors |
| 🧮 **Multi-Paradigm Semantics** | Julia (multiple dispatch), R (broadcasting/formulas), Haskell (purity/type classes) | Expressive mathematical syntax without runtime penalty |
| 📖 **Paper-First Code** | `@paper`, `@invariant`, `@experiment` annotations | Self-documenting, formally verifiable, reproducibly benchmarked |
| 🤖 **AI-Native by Default** | Tensors, autodiff, NPU targeting, predictive prefetch as primitives | Zero library overhead, compile-time hardware awareness |
| 🔵 **Go-Powered Tooling** | CLI, LSP, package manager, test runner written in Go | Fast compilation, great concurrency, single-binary distribution |

### 🔹 Language Design Contract

1. **No Runtime Surprises**: All shape mismatches, ownership violations, and unhandled errors are caught at compile time.
2. **Zero-Cost Abstractions**: Safety checks, dispatch resolution, and memory pooling are monomorphized or inlined. No GC, no vtables unless explicitly requested via `dyn`.
3. **Deterministic Execution**: Pure functions parallelize automatically. `async`/`@parallel` map to structured concurrency with guaranteed completion.
4. **Hardware Transparency**: The compiler emits hardware-specific intrinsics (`prefetch`, `dma`, `npu_launch`) based on tensor metadata and access patterns.
5. **Ergonomic Toolchain**: All developer-facing tools ship as single, dependency-free Go binaries — no runtime installation, no `pip`, no CMake required by end users.

---

## 3. Compiler Architecture & Technology Stack

Aurelia uses a **split-layer architecture** cleanly dividing responsibilities between C++23 and Go. The performance-critical compiler core (parser, type system, borrow checker, MLIR/LLVM codegen, and runtime) is implemented in **C++23**. The developer-facing toolchain (CLI, LSP server, package manager, test harness, build orchestration, and documentation generator) is implemented in **Go 1.22+**.

### 🔹 Full Compilation Pipeline

```
.aul source
    │
    ▼
[Go] aulc CLI — argument parsing, source discovery, workspace resolution
    │
    ▼
[Go] Pre-processor — annotation extraction (@paper, @experiment), JSON-LD provenance tagging
    │
    ▼  IPC / C ABI bridge
[C++] Lexer/Parser (ANTLR4 / tree-sitter, C++23) → AST
    │
    ▼
[C++] Type Checker + Neuro-Linear Borrow Analyzer + Symbolic Shape Solver
    │
    ▼
[C++] MLIR Lowering (Tensor, Linalg, SCF, Autodiff dialects)
    │
    ▼
[C++] Optimization: Shape Inference → Kernel Fusion → Predictive Prefetch Insertion
    │
    ▼
[C++] LLVM Codegen (CPU) + MLIR GPU/NPU → .ptx / .spv / .elf
    │
    ▼
[C++] Aurelia Runtime (C++23 + CUDA Graphs + Deterministic Pools)
    │
    ▼
[Go] Post-build: test runner, benchmark harness, package registry push, LSP diagnostics relay
```

### 🔹 Technology Matrix

| Layer | Language | Toolchain | Responsibility | Status |
|-------|----------|-----------|----------------|--------|
| **CLI & Workspace** | **Go** | `cobra` + `urfave/cli` | `aulc build/run/test/fmt`, workspace discovery | 🔴 Not Started |
| **LSP Server** | **Go** | `gopls`-style + `jsonrpc2` | IDE integration, hover, diagnostics relay | 🔴 Not Started |
| **Package Manager** | **Go** | Custom resolver + HTTP | Dependency resolution, registry, lockfile | 🔴 Not Started |
| **Test & Bench Runner** | **Go** | Custom harness + `testing` | Property tests, benchmark regression, fuzzing | 🔴 Not Started |
| **Annotation Pre-processor** | **Go** | Custom AST walker | `@paper`/`@experiment` extraction, JSON-LD emit | 🔴 Not Started |
| **C++/Go IPC Bridge** | **Go + C++** | `cgo` + C ABI / gRPC | Toolchain↔compiler communication | 🔴 Not Started |
| **Frontend (Lexer/Parser)** | **C++23** | ANTLR4 / tree-sitter | Indentation-aware parsing, AST generation | 🔴 Not Started |
| **Type System** | **C++23** | Custom Hindley-Milner + `std::expected` | Strict typing, error propagation, exhaustive matching | 🔴 Not Started |
| **Borrow Checker** | **C++23** | Region-based lifetime analysis | Linear/affine types, predictive prefetch validation | 🔴 Not Started |
| **IR** | **C++23** | MLIR (C++ API) | Tensor/autodiff/gpu dialects, fusion passes | 🔴 Not Started |
| **Codegen** | **C++23** | LLVM + MLIR GPU/NPU | CPU/GPU/NPU backend, auto-tuning | 🔴 Not Started |
| **Runtime** | **C++23** | `std::pmr`, CUDA Graphs, SYCL | Zero-copy tensors, structured concurrency | 🔴 Not Started |

### 🔹 Build Requirements

**For compiler core (C++23):**
- `clang++` ≥ 16 or `g++` ≥ 13 with C++23 support
- CMake ≥ 3.28
- LLVM ≥ 17, MLIR ≥ 17
- ANTLR4 C++ runtime or tree-sitter
- CUDA ≥ 12.0 / SYCL (optional, for GPU/NPU targets)
- Python ≥ 3.10 (build scripts only)

**For toolchain (Go):**
- Go ≥ 1.22
- `go build ./...` — all toolchain binaries compile with zero external dependencies
- No system packages required beyond the Go toolchain itself

---

## 4. Dual-Language Strategy: C++23 & Go

This section details the explicit engineering rationale for pairing C++23 and Go, the boundary between them, and how the two layers communicate.

### 🔹 Why C++23 for the Compiler Core?

The Aurelia compiler core must interface directly with LLVM and MLIR, which expose C++ APIs only. C++23 also provides the zero-cost abstractions, deterministic memory control (`std::pmr`), and compile-time computation (`consteval`, `constexpr`) required for the borrow checker, shape solver, and CUDA graph runtime. There is no viable substitute at this layer.

Key C++23 features used:
- `std::expected<T,E>` — value-based error propagation replacing exceptions throughout the compiler
- `std::mdspan` — zero-copy multi-dimensional tensor views in the runtime
- `std::flat_map` / `std::flat_set` — cache-friendly symbol tables in the type checker
- `std::generator` (coroutines) — lazy AST traversal and IR emission passes
- Deducing `this` — CRTP-free polymorphic pass infrastructure

### 🔹 Why Go for the Toolchain?

Go is purpose-built for exactly the problems that make language toolchains painful: fast compilation, excellent concurrency primitives, single-binary distribution, and a rich standard library covering HTTP, JSON, file I/O, and process management without external dependencies. The Go toolchain layer handles everything a developer interacts with before and after the compiler core runs.

Key Go advantages used:
- **`goroutines` + `channels`** — parallel source file watching in the LSP server and concurrent benchmark execution in the test harness
- **Single static binary** — `aulc` ships as one binary per platform. No LLVM, no CMake, no Python required for end users to build and test Aurelia programs
- **`net/http` + `encoding/json`** — package registry client and JSON-LD provenance API with zero third-party HTTP libraries
- **`go test` infrastructure** — property-based test runner reuses Go's testing conventions, familiar to contributors
- **Fast iteration** — Go's sub-second compile times make CLI and LSP development significantly faster than C++ for developer-facing features

### 🔹 Language Boundary & Communication

The boundary between C++23 and Go is a **clean, stable C ABI**. Go calls into the compiler core via `cgo` for embedded use cases (e.g., the REPL), and via a **local gRPC service** for the LSP server and build daemon. This design means:

1. The C++ compiler core can be developed, tested, and released independently of Go tooling.
2. The Go toolchain can be updated, swapped, or extended without recompiling the compiler.
3. Third-party editor integrations can speak directly to the LSP gRPC endpoint without depending on `cgo`.

```
┌─────────────────────────────────────┐
│          Go Toolchain Layer          │
│  aulc CLI │ LSP Server │ pkg manager │
└──────────────┬──────────────────────┘
               │  C ABI (cgo) for REPL
               │  gRPC for LSP / daemon
┌──────────────▼──────────────────────┐
│       C++23 Compiler Core            │
│  Lexer → Parser → TypeChecker →      │
│  BorrowChecker → MLIR → LLVM        │
└──────────────────────────────────────┘
               │
┌──────────────▼──────────────────────┐
│       C++23 Runtime                  │
│  std::pmr pools │ CUDA Graphs │ SYCL │
└──────────────────────────────────────┘
```

### 🔹 Go Module Layout

```
aurelia/
├── cmd/
│   ├── aulc/           # Main CLI entry point (cobra)
│   │   └── main.go
│   └── aul-lsp/        # LSP server entry point
│       └── main.go
├── internal/
│   ├── cli/            # Subcommands: build, run, test, fmt, doc
│   ├── lsp/            # JSON-RPC 2.0 server, diagnostics relay
│   ├── pkgmgr/         # Dependency resolver, lockfile, registry client
│   ├── testrunner/     # Property-based test harness, benchmark regression
│   ├── preproc/        # @paper/@experiment annotation extractor
│   ├── bridge/         # cgo + gRPC bridge to C++ compiler core
│   └── workspace/      # aul.toml parsing, source discovery
├── pkg/
│   └── protocol/       # LSP protocol types, JSON-LD schema, gRPC protobuf defs
├── go.mod
└── go.sum
```

### 🔹 Example: Go CLI Invoking the C++ Compiler Core

```go
// internal/bridge/compiler.go
package bridge

/*
#cgo LDFLAGS: -L../../build/lib -laurelia_core -lstdc++
#include "aurelia_core.h"
*/
import "C"
import (
    "fmt"
    "unsafe"
)

// CompileResult holds the output of a single compilation unit.
type CompileResult struct {
    Diagnostics []Diagnostic
    OutputPath  string
    Success     bool
}

// Compile invokes the C++23 compiler core via C ABI.
func Compile(sourcePath string, opts CompileOptions) (CompileResult, error) {
    cPath := C.CString(sourcePath)
    defer C.free(unsafe.Pointer(cPath))

    cOpts := opts.toCOptions()
    result := C.aurelia_compile(cPath, cOpts)

    if result.error_count > 0 {
        return CompileResult{}, fmt.Errorf("compilation failed with %d error(s)", result.error_count)
    }
    return parseCompileResult(result), nil
}
```

```go
// cmd/aulc/main.go
package main

import (
    "github.com/DeepcometAI/aurelia/internal/cli"
    "github.com/spf13/cobra"
    "os"
)

func main() {
    root := &cobra.Command{
        Use:   "aulc",
        Short: "Aurelia compiler & toolchain",
        Long:  "aulc is the unified CLI for compiling, testing, and managing Aurelia projects.",
    }
    root.AddCommand(
        cli.NewBuildCmd(),   // calls C++ core via bridge
        cli.NewRunCmd(),
        cli.NewTestCmd(),    // Go-native property test runner
        cli.NewFmtCmd(),     // Go-native formatter (source-level)
        cli.NewDocCmd(),     // JSON-LD provenance extractor
        cli.NewLspCmd(),     // spawns aul-lsp subprocess
    )
    if err := root.Execute(); err != nil {
        os.Exit(1)
    }
}
```

### 🔹 Example: Go LSP Server Relaying C++ Diagnostics

```go
// internal/lsp/server.go
package lsp

import (
    "context"
    "encoding/json"
    "github.com/DeepcometAI/aurelia/internal/bridge"
    "github.com/DeepcometAI/aurelia/pkg/protocol"
)

// Server implements the Language Server Protocol over JSON-RPC 2.0.
type Server struct {
    conn     *jsonrpc2.Conn
    compiler *bridge.CompilerDaemon  // long-lived gRPC connection to C++ daemon
}

// handleDidSave triggers incremental compilation on file save and pushes
// diagnostics back to the editor via publishDiagnostics.
func (s *Server) handleDidSave(ctx context.Context, params protocol.DidSaveParams) error {
    result, err := s.compiler.IncrementalCompile(ctx, params.TextDocument.URI)
    if err != nil {
        return err
    }
    diags := toLSPDiagnostics(result.Diagnostics)
    return s.conn.Notify(ctx, "textDocument/publishDiagnostics",
        protocol.PublishDiagnosticsParams{
            URI:         params.TextDocument.URI,
            Diagnostics: diags,
        })
}
```

---

## 5. Language Features & Syntax Deep Dive

Aurelia is engineered to read like a research paper but compile like production C++. Below are core language constructs with implementation intent.

### 🔹 First-Class Tensor Primitive

Unlike standard arrays, `tensor<T>` types carry compile-time metadata for shape, stride, data type, and differentiation state.

```aurelia
type Batch = Dim<symbol: "B", range: 1..4096>
let q: tensor<[Batch, 512, 768], f32, normalized>
let out = q |> matmul(w) |> layer_norm |> dropout(0.1)
```

- **Compile-time shape verification** prevents runtime dimension mismatches
- **Autodiff metadata** (`trainable`, `grad`) automatically constructs gradient graphs at IR level
- **Zero-cost fusion** eliminates intermediate tensor allocations via `|>` pipeline optimization

### 🔹 Neuro-Linear Types & Predictive Allocator

A hybrid memory model combining Rust-like ownership tracking with AI-guided cache management.

```aurelia
fn process_stream(mut pool: MemoryPool, input: Stream<tensor<[N], f32>>) {
    for chunk in input {
        predict_next(chunk.next_window())  # Compiler inserts L1/NPU prefetch
        let view = chunk.borrow()          # Scoped, zero-alias borrow
        compute(view)
    }
} # Deterministic drop → memory returned to predictive pool
```

- **Linear/Affine Types**: Enforce strict ownership, preventing data races & silent aliasing
- **Predictive Prefetch**: `predict_next()` intrinsics guide compile-time cache/NPU pre-warming
- **Deterministic Pools**: Zero GC pauses; memory returned to hardware-aligned arenas on scope exit

### 🔹 Native Async & Massively Parallel Execution

Designed for thousands of GPU/NPU cores without complex threading primitives.

```aurelia
@parallel for i in 0..batch_size {
    async { model.infer(fetch_sample(i))? }
}
```

- Compiler maps `@parallel`/`async` blocks directly to GPU workgroups & CUDA/SYCL streams
- **Structured Concurrency**: Dangling futures, unawaited tasks, and race conditions are compile-time errors
- Automatic workgroup tiling & warp/wavefront alignment based on tensor dimensions

### 🔹 Go-Backed Package System (`aul.toml`)

Aurelia's package manager — implemented entirely in Go — uses a declarative `aul.toml` manifest inspired by Cargo, resolved by the Go `pkgmgr` module.

```toml
# aul.toml — parsed and resolved by Go package manager
[package]
name    = "sparse-attention"
version = "0.2.0"
authors = ["Deepcomet AI Inc."]

[dependencies]
aurelia-std  = "0.1.0"
aurelia-math = { git = "https://github.com/DeepcometAI/aurelia-math", tag = "v0.3.1" }

[dev-dependencies]
aurelia-proptest = "0.1.0"   # Property-based test library

[profile.release]
opt-level    = 3
lto          = true
npu-target   = "auto"
```

---

## 6. Advanced Semantics & Formal Verification

Aurelia integrates mathematical rigor directly into the language syntax and compiler pipeline.

### 🔹 Multi-Paradigm Integration

| Paradigm | Syntax Example | Compiler Behavior |
|----------|----------------|-------------------|
| **Julia Dispatch** | `fn loss(pred: tensor<[N], f32>, target: tensor<[N], f32>) -> f32` | Compile-time monomorphization, zero vtable overhead |
| **R Vectorization** | `let residuals = y - model.predict(X)`<br>`let pipeline = y ~ x1 + log(x2) + bias` | Automatic broadcasting → SIMD/GPU loop fusion |
| **Haskell Purity** | `let` = immutable by default. `mut` + explicit borrow required. | Side-effect tracking, deterministic execution graphs |
| **Exhaustive Matching** | `match load("model.bin") { Ok(t) => ..., Err(e) => ... }` | Static analysis ensures all branches handled |

### 🔹 Paper-First Verification & Provenance

```aurelia
@paper { title: "Sparse Attention w/ Predictive Caching", version: "0.2.0" }

@invariant("softmax_mass")
fn softmax_preserves_mass(logits: tensor<[N], f32>) -> bool {
    sum(softmax(logits, axis=-1)) ≈ 1.0  # ≈ = epsilon-bounded compile check
}

@experiment("scaling_test")
fn benchmark_scaling() -> Result<Benchmark, IOError> {
    let times = [64, 128, 256] |> map(d => time(sparse_attention(d)))
    assert times ~ O(n log n)
    return Benchmark::from(times)
}
```

- **`@invariant`** desugars to property-based tests + formal verification hooks (Kani/Prusti). The Go test runner executes these harnesses and reports results in standard Go test output format.
- **`@experiment`** auto-generates benchmark harnesses. The Go benchmark runner tracks regression against stored baselines and emits `go test -bench`-compatible output for CI integration.
- **Provenance Metadata** compiles to JSON-LD embedded in binaries. The Go `preproc` module extracts and validates these at build time, publishing them to the registry.
- All annotations strip to **identical IR** in release builds. Zero runtime overhead.

---

## 7. Component Progress Tracker & Development Status

*Last Updated: April 2026 | Legend: ✅ Implemented | 🟡 In Progress | 🔴 Not Started | ⚪ Planned*

### 🔹 C++23 Compiler Core

| Component | Sub-Component | Status | Blockers & Notes |
|-----------|--------------|--------|------------------|
| **Frontend** | Lexer (indentation-aware) | 🔴 Not Started | ANTLR grammar definition pending |
| | Parser → AST | 🔴 Not Started | Block resolution, comment handling |
| | Symbol table & scope | 🔴 Not Started | Lifetime region tracking required |
| **Type System** | Basic inference (`let`, `fn`) | 🔴 Not Started | HM solver integration pending |
| | `Option<T>` / `Result<T,E>` | 🔴 Not Started | Exhaustive match enforcement pending |
| | Tensor type + shape algebra | 🔴 Not Started | Symbolic `Dim<symbol>` solver not built |
| **Memory** | Borrow checker skeleton | 🔴 Not Started | Region-based analysis not started |
| | `predict_next()` intrinsic | 🔴 Not Started | Prefetch lowering pass pending |
| | Deterministic pool runtime | 🔴 Not Started | `std::pmr` integration pending |
| **IR/Codegen** | MLIR tensor lowering | 🔴 Not Started | MLIR C++ API setup pending |
| | Autodiff graph gen | 🔴 Not Started | Reverse-mode pass not implemented |
| | Kernel fusion opt | 🔴 Not Started | Linalg → GPU dialect mapping pending |
| **Language** | `@parallel` / `async` | 🔴 Not Started | Structured concurrency validation pending |
| | Formula syntax (`~`) | 🔴 Not Started | AST desugaring pipeline not built |
| | Paper annotations | 🔴 Not Started | JSON-LD provenance embedder pending |

### 🔹 Go Toolchain Layer

| Component | Sub-Component | Status | Blockers & Notes |
|-----------|--------------|--------|------------------|
| **CLI (`aulc`)** | `build` / `run` subcommands | 🔴 Not Started | C++ bridge ABI not finalized |
| | `fmt` subcommand | 🔴 Not Started | Formatter operates on Go AST-of-source; lexer needed first |
| | `doc` subcommand | 🔴 Not Started | JSON-LD extractor pending |
| **LSP Server** | JSON-RPC 2.0 transport | 🔴 Not Started | Protocol types defined; server loop pending |
| | Diagnostics relay | 🔴 Not Started | gRPC bridge to C++ daemon pending |
| | Hover / completion | 🔴 Not Started | Symbol table API not exposed |
| **Package Manager** | `aul.toml` parser | 🔴 Not Started | Schema finalized, parser not written |
| | Dependency resolver | 🔴 Not Started | Version algebra pending |
| | Registry client | 🔴 Not Started | Registry API not designed |
| **Test Runner** | Property test harness | 🔴 Not Started | `@invariant` extraction pipeline pending |
| | Benchmark regression | 🔴 Not Started | Baseline storage format pending |
| | Sanitizer CI integration | 🔴 Not Started | CI pipeline not configured |
| **C++/Go Bridge** | C ABI (`cgo`) bindings | 🔴 Not Started | Compiler core header not stable |
| | gRPC daemon protocol | 🔴 Not Started | `.proto` definition pending |

> 🎯 **Immediate Priority**: C++ lexer/parser + Go `aulc` CLI skeleton + C ABI bridge stub. These three form the minimum viable compilation loop all subsequent work depends on.

---

## 8. Deepcomet AI Ecosystem Roadmap Alignment

Aurelia is not a standalone project. It is the mathematical and execution foundation for Deepcomet AI's entire vertical stack.

| Phase | Objective | Aurelia's Enabling Role | Go's Role | Delivery Horizon |
|-------|-----------|-------------------------|-----------|------------------|
| **Phase 1: Aurelia** | AI-native systems language | Tensor primitives, predictive allocator, paper-first syntax, formal verification | CLI, LSP, pkg manager, test harness in Go | Q4 2026 (Alpha) |
| **Phase 2: Zenith Kernel** | Probabilistic microkernel | Pure core + `@invariant` guarantees proven memory safety. Predictive allocator powers 10ms-ahead scheduler. | Go daemon manages kernel build pipeline & CI benchmarks | Q2 2027 |
| **Phase 3: SkyOS** | Generative LAM interface | Tensor-driven pipelines + `KnowledgeVector<T>` power dynamic UI & Semantic File System | Go powers SkyOS package registry & provisioning API | Q4 2027 |
| **Phase 4: DeepComet AI** | Tiered model family | Deterministic AST + theorem annotations = ideal training corpus for `DeepComet-Code` | Go orchestrates model training pipelines & data ingestion | Q2 2028 |
| **Phase 5: Monetization** | Enterprise/Consumer products | Strict typing + IR transparency enable `Migration Forge`. Zero-overhead async enables `SkyCloud`. | Go powers `SkyCloud` NPU scheduling API & `Private Brain` REST gateway | Q4 2028+ |

> **Strategic Imperative**: By controlling the Language → Kernel → OS → Model pipeline, Deepcomet AI eliminates legacy context-switch overhead, achieves hardware-software synthesis, and establishes true Vertical AI Integration. The C++23 core ensures zero-overhead execution at every layer; the Go toolchain ensures every developer on the stack has a fast, reliable, and portable development experience.

---

## 9. Engineering Standards, Tooling & CI/CD

### 🔹 C++23 Compiler Flags

```bash
-std=c++23 -Wall -Wextra -Werror -pedantic
-fsanitize=address,undefined,thread
-mlir-optimize -ffast-math -O3
-fno-exceptions -fno-rtti  # Aurelia handles errors via std::expected values
```

### 🔹 Go Toolchain Standards

```bash
# All Go code must pass:
go vet ./...
staticcheck ./...
go test -race ./...          # Race detector on all toolchain tests
go build -trimpath ./...     # Reproducible, path-stripped binaries

# Formatting enforced by CI:
gofmt -l .                   # Must produce zero output
goimports -l .               # Import organization enforced
```

### 🔹 Static Analysis & Safety Gates

| Tool | Language | Profile | Purpose |
|------|----------|---------|---------|
| Clang-Tidy | C++23 | `cert-*`, `cppcoreguidelines-*`, `modernize-*` | Catch UB, memory leaks, concurrency issues |
| Cppcheck | C++23 | `--enable=all` | Cross-compiler defect detection |
| AddressSanitizer | C++23 | Runtime | Heap/stack buffer overflow, use-after-free |
| ThreadSanitizer | C++23 | Runtime | Data race detection in async/runtime |
| `go vet` + `staticcheck` | Go | All packages | Correctness, style, dead code, shadow vars |
| `go test -race` | Go | All packages | Race condition detection in LSP/CLI concurrency |
| Kani/Prusti | C++23 (Future) | Formal | Prove invariants, ownership, shape correctness |

### 🔹 Testing Strategy

- **C++ Property-Based Testing**: Randomized tensor shapes, dtype permutations, and access patterns via compiler core test suite
- **Go Table-Driven Tests**: All CLI commands, package resolver logic, and LSP handlers covered by Go's `testing` package using table-driven patterns
- **Invariant Fuzzing**: `@invariant` blocks compiled to automated property tests; executed by the Go test runner via C ABI
- **Benchmark Regression**: Go benchmark runner tracks latency/throughput automatically against PyTorch/C++ baselines using stored JSON baselines
- **Shape Solver Tests**: Compile-time algebra validation for broadcasting, slicing, and fusion (C++ unit tests)
- **LSP Integration Tests**: Go-based end-to-end tests that spin up the LSP server and exercise hover, completion, and diagnostics via the JSON-RPC protocol

### 🔹 CI/CD Pipeline

```yaml
# .github/workflows/aurelia-ci.yml (outline)
jobs:
  go-lint:
    steps: [gofmt, goimports, staticcheck, go vet]

  go-test:
    steps: [go test -race -cover ./...]

  go-build:
    steps: [go build -trimpath ./cmd/aulc, go build ./cmd/aul-lsp]

  cpp-lint:
    steps: [clang-tidy, clang-format, cppcheck]

  cpp-build:
    steps: [cmake --preset release, cmake --build]

  cpp-test:
    steps: [ctest --sanitizers address,undefined,thread]

  integration:
    needs: [go-build, cpp-build]
    steps: [aulc build examples/, go test ./internal/bridge/...]

  benchmark:
    steps: [go test -bench=. ./..., compare vs PyTorch/TensorRT baseline]

  deploy:
    steps: [nightly release tag, provenance JSON-LD embed, registry push]
```

---

## 10. Contributing Guidelines & Community

We welcome contributions from systems programmers, AI researchers, compiler engineers, Go toolchain developers, and formal verification experts.

### 🔹 Repository Structure

```
aurelia/
├── compiler/           # C++23 compiler core (CMake)
│   ├── include/
│   ├── src/
│   │   ├── lexer/
│   │   ├── parser/
│   │   ├── typecheck/
│   │   ├── borrowck/
│   │   ├── mlir/
│   │   └── runtime/
│   └── CMakeLists.txt
├── toolchain/          # Go toolchain (go.mod)
│   ├── cmd/
│   │   ├── aulc/
│   │   └── aul-lsp/
│   ├── internal/
│   └── pkg/
├── stdlib/             # Aurelia standard library (.aul sources)
├── examples/           # Example Aurelia programs
├── docs/               # Reference documentation
└── .github/workflows/  # CI/CD pipelines
```

### 🔹 Contribution Workflow

1. Fork the repository & create a feature branch (`git checkout -b feat/your-feature`)
2. Implement changes with corresponding tests & documentation updates
3. For C++ changes: run `make lint test` (enforces Clang-Tidy, sanitizers, property checks)
4. For Go changes: run `go vet ./... && go test -race ./...`
5. Submit a Pull Request with:
   - Clear description & motivation
   - Benchmark results (if applicable)
   - CI pass confirmation
   - 2 maintainer approvals required for merge

### 🔹 Engineering Expectations

- **Zero Runtime Overhead** (C++): Language abstractions must compile to equivalent IR as manual C++
- **Single-Binary Distribution** (Go): All toolchain commands ship as one binary per platform with `go build`
- **Deterministic Behavior**: Pure functions, structured concurrency, predictable memory lifetimes
- **Formal Alignment**: All `@invariant` blocks must be provable or fail CI
- **Documentation First**: Public APIs require docstrings, usage examples, and complexity guarantees

### 🔹 Good First Issues *(All Pending)*

**C++23 Compiler Core:**
- [ ] 🔴 Implement indentation-aware lexer rules (ANTLR/tree-sitter)
- [ ] 🔴 Add `Option<T>`/`Result<T,E>` type checker stubs
- [ ] 🔴 Write MLIR lowering pass for `tensor` broadcast
- [ ] 🔴 Draft property-based tests for `softmax` & `matmul` invariants
- [ ] 🔴 Integrate `predict_next()` prefetch intrinsics into IR

**Go Toolchain:**
- [ ] 🔴 Build `aulc` CLI skeleton with `cobra` (build/run/test/fmt subcommands)
- [ ] 🔴 Implement `aul.toml` parser using Go's `encoding/toml`
- [ ] 🔴 Write JSON-RPC 2.0 transport layer for the LSP server
- [ ] 🔴 Design and implement C ABI header (`aurelia_core.h`) + `cgo` bindings
- [ ] 🔴 Build benchmark regression baseline storage (JSON + `go test -bench` integration)
- [ ] 🔴 Implement `@paper` / `@experiment` annotation extractor in Go pre-processor

> 💡 **Tip (C++)**: Start with the lexer/parser scaffold. All type checking, IR lowering, and runtime features depend on a correct AST.
> 💡 **Tip (Go)**: Start with the `aulc` CLI skeleton and C ABI stub. You can develop and test the toolchain before the compiler core is complete by returning mock diagnostics from the bridge.

---

## 11. Licensing, Contact & Appendices

### 🔹 License

This project is licensed under the **MIT License** for community, academic, and research use. Enterprise licensing for `Migration Forge`, `SkyCloud`, `Private Brain`, and `DeepComet` integrations is managed exclusively by Deepcomet AI Inc. See [LICENSE](LICENSE) for full terms.

### 🔹 Contact & Community

| Channel | Link | Purpose |
|---------|------|---------|
| 🌐 **Official Site** | [nehal-aditya.github.io](https://nehal-aditya.github.io/) | Roadmap updates, whitepapers, enterprise inquiries |
| 🐛 **Issues & RFCs** | [GitHub Issues](https://github.com/DeepcometAI/aurelia/issues) | Bug reports, feature proposals, compiler diagnostics |
| 📧 **Engineering** | [nehaladityaresearch@outlook.com](mailto:nehaladityaresearch@outlook.com) | Technical architecture, partnership, security disclosures |

### 🔹 Glossary & References

| Term | Definition |
|------|------------|
| **Neuro-Linear Types** | Ownership system combining affine types with AI-guided prefetch hints |
| **Predictive Allocator** | Memory pool manager using compile-time access-pattern modeling |
| **Paper-First Code** | Annotation-driven syntax for self-documenting, formally verifiable programs |
| **Vertical AI Integration** | Deepcomet AI strategy of co-designing Language, Kernel, OS, and Models |
| **Structured Concurrency** | Deterministic async execution where all tasks complete before scope exit |
| **C ABI Bridge** | Stable C-language interface between the Go toolchain and C++23 compiler core via `cgo` |
| **Go Toolchain Layer** | All developer-facing Aurelia tools (CLI, LSP, package manager, test runner) implemented in Go |
| **Compiler Daemon** | Long-lived C++23 process exposing incremental compilation via gRPC, consumed by the Go LSP server |

---

> *Built for researchers, engineered for production, optimized for the AI era.* 🌌
>
> **C++23** powers the compiler core — zero overhead, hardware-native, MLIR-integrated.
> **Go** powers the toolchain — fast builds, single binaries, first-class concurrency.
> Together they form the engineering foundation of Deepcomet AI's vertical stack.
>
> **Current State**: Specification-first repository. Compiler scaffold (C++) & toolchain skeleton (Go) implementation begins Q2 2026. Join us to build the foundation.
