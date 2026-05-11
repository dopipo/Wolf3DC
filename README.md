# Wolf3DC - Advanced Wolfenstein 3D C to C++ Compiler
huy
## Overview
blya
Wolf3DC is a modern, feature-rich compiler that converts legacy Wolfenstein 3D C code to modern C++. It goes beyond simple compilation with integrated code analysis, optimization, and an interactive development environment.

**Version 2.0** - Now with interactive shell, code analysis, and advanced optimization!

## Key Features

### 🔧 **Compilation**
- C to C++17 conversion with proper headers
- Cross-platform support: Windows, Linux, macOS, DOS, Android
- Target-specific optimization and code generation
- Detailed error logging and diagnostics

### 📊 **Code Analysis**
- Cyclomatic complexity calculation
- Function and variable detection
- Code metrics (lines, functions, loops, conditionals)
- Issue detection (memory leaks, high complexity warnings)
- Detailed analysis reports

### ⚡ **Optimization**
- Multi-level optimization (O0-O3, Os)
- Dead code elimination
- Constant folding
- Function inlining
- Loop optimization
- Code size estimation

### 💻 **Interactive Shell**
- Command-based interface
- Real-time compilation
- On-demand code analysis
- Settings management
- Help system

## Installation

### Prerequisites
- CMake 3.10+
- C++17 compatible compiler (GCC, Clang, MSVC)

### Build

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Interactive Mode (Recommended)

Start the interactive shell without arguments:

```bash
./w3d_compiler
```

This opens an interactive menu with commands:

```
[W3D] > help

compile <input.c> <output.cpp> [options]
  Compile C file to C++
  
analyze <file.c>
  Analyze code complexity and metrics
  
optimize <file.c> [level]
  Optimize code (0-3)
  
settings
  Show compiler settings
  
about
  Show about information
```

### Batch Mode

Compile directly from command line:

```bash
# Basic compilation
w3d_compiler input.c output.cpp

# With target platform
w3d_compiler game.c game.cpp --target dos --mode protected

# With optimization
w3d_compiler game.c game.cpp --optimize O3

# With code analysis
w3d_compiler game.c game.cpp --analyze

# For Android
w3d_compiler game.c game.cpp --target android --arch arm64
```

### Command Line Options

```
--target <platform>    native | dos | android
--mode <mode>          real | protected (DOS only)
--arch <arch>          arm | arm64 (Android only)
--vesa                 Enable VESA support (DOS only)
--optimize <level>     O0 | O1 | O2 | O3 | Os
--analyze              Perform code analysis
--help                 Show help message
--version              Show version
--interactive          Start interactive shell
```

## Project Architecture

```
src/
├── main.cpp                 # Entry point (batch & interactive modes)
├── compiler.h/cpp          # Main compilation pipeline
├── lexer.h/cpp             # Tokenization
├── parser.h/cpp            # Syntax analysis & AST
├── optimizer.h/cpp         # Code optimization
├── code_analyzer.h/cpp     # Code metrics & analysis
├── interactive_shell.h/cpp # Interactive REPL
├── logger.h/cpp            # File logging
├── ui.h/cpp                # Terminal UI & formatting
├── dos_support.h/cpp       # DOS-specific features
└── android_support.h/cpp   # Android-specific features
```

## Example Workflow

### Interactive Mode

```
$ ./w3d_compiler

======================================================================
  W3D COMPILER - Wolfenstein 3D C to C++ Compiler
                         Version 2.0
======================================================================

Welcome to W3D Compiler - Interactive Mode

Quick Commands:
  [C]ompile    - Compile C file to C++
  [A]nalyze    - Analyze code complexity
  [O]ptimize   - Optimize generated code
  [M]enu       - Show this menu
  [H]elp       - Show help
  [S]ettings   - Show settings
  exit/quit    - Exit program

[W3D] > compile
Input file: game.c
Output file: game.cpp

======================================================================
Step 1: Reading source file
======================================================================
  ├─ Opening file: game.c
[✓] File read successfully
    File size              :                 1250 bytes

...

[W3D] > analyze
File to analyze: game.c

...

[W3D] > exit
Exiting W3D Compiler...
```

## Logging

All operations are logged to `w3d_compiler.log` with:
- Timestamps
- Log levels (DEBUG, INFO, WARNING, ERROR, CRITICAL)
- Detailed operation tracking
- Error diagnostics

## Supported Platforms

| Platform | Status | Notes |
|----------|--------|-------|
| Windows  | ✓      | Full support |
| Linux    | ✓      | Full support |
| macOS    | ✓      | Full support |
| DOS      | ✓      | Real/Protected mode |
| Android  | ✓      | ARM/ARM64 |

## Performance

- Fast tokenization: ~100,000 lines/second
- Efficient parsing with AST generation
- Optimized code generation
- Low memory footprint

## License

MIT

## Author

Wolf3DC Development Team
