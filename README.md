# Chrona

**Chrona** is a **node-based pipeline orchestrator** built with **Qt (C++)**.  
It lets you compose CI/CD-style workflows visually (as a graph) instead of writing scripts — useful for build automation, asset processing, packaging, and repeatable production tasks.

> Bachelor’s capstone project.  
> The core idea: **a visual “Jenkins-like” workflow**, but designed as a desktop app with a graph editor and an execution engine.

---

## Why Chrona

Classic CI/CD is powerful, but scripting quickly becomes:
- hard to read for non-programmers,
- painful to maintain as pipelines grow,
- easy to break with small changes.

Chrona focuses on:
- **visual clarity** (graph-based workflows),
- **repeatability** (defined steps, predictable execution),
- **extensibility** (new node types can be added over time),
- **production-minded tooling** (logs, execution status, error reporting).

---

## Key Features

- **Node graph editor**
  - Create and connect nodes to form a workflow DAG.
  - Validate graph connections (types / required inputs).
- **Execution engine**
  - Run workflow steps in a defined order.
  - Support for sequential execution (and optional parallel execution).
- **Workflow persistence**
  - Save/load graphs (e.g., JSON-based format or custom serialization).
- **Logging & diagnostics**
  - Per-node logs, overall run status, error propagation.
- **Extensible nodes**
  - Add custom nodes (e.g., “Run Process”, “Copy Files”, “Zip”, “Upload”, “HTTP Request”, etc.)

---

## What Can You Build With It

Example workflows:
- Build → Cook → Package (game build flow)
- Pull assets → Convert → Validate → Copy to workspace
- Run tests → Collect artifacts → Upload
- “One-click” automation for repeatable team tasks

---

## Architecture Overview (high-level)

Chrona is split into two layers:

### 1) Editor Layer (UI)
- Graph canvas + node widgets
- Connections / pins
- Selection, move, delete, context menu
- Graph validation feedback

### 2) Runtime Layer (Execution)
- Graph representation (nodes/edges + data)
- Scheduler (topological sorting, dependency resolution)
- Node executor interface (`INodeTask`-like concept)
- Execution context (shared variables, env, paths, artifacts)
- Logging/events (node started, progress, finished, failed)

> The important principle:  
> **UI graph == serialized model == executable graph** (same truth, no hidden state).

---

### Requirements
- **Qt 5/6** (depending on your project)
- C++ compiler (MSVC / clang / gcc)
- CMake or qmake (depending on your build system)
