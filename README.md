# Wolf3DC - Wolfenstein 3D C to C++ Compiler

A C-to-C++ compiler for Wolfenstein 3D with support for DOS, Android, and modern platforms.

## Features

- **Lexical Analysis**: Tokenizes C source code
- **Syntax Parsing**: Generates Abstract Syntax Tree (AST)
- **Code Generation**: Converts to modern C++ with proper includes
- **Cross-platform Support**: Windows, Linux, macOS, DOS, Android
- **Error Logging**: Comprehensive file-based error logging
- **Target Support**:
  - DOS (16-bit real mode / 32-bit protected mode)
  - Android (ARM / ARM64)
  - Modern platforms (x86/x64)

## Build

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

```bash
w3d_compiler <input.c> <output.cpp> [options]
```

### Options

- `--target dos` - Compile for DOS
- `--target android` - Compile for Android
- `--mode real` - DOS real mode (16-bit)
- `--mode protected` - DOS protected mode (32-bit)
- `--vesa` - Enable VESA video support (DOS)
- `--arch arm` - Android ARM architecture
- `--arch arm64` - Android ARM64 architecture
- `--optimize O2` - Optimization level (O0-O3, Os)

## Example

```bash
# Compile for native platform
w3d_compiler test/example.c test/example_out.cpp

# Compile for DOS protected mode
w3d_compiler game.c game.cpp --target dos --mode protected

# Compile for Android ARM64
w3d_compiler game.c game.cpp --target android --arch arm64
```

## Logging

All compilation operations are logged to `w3d_compiler.log` with timestamps and severity levels:
- DEBUG
- INFO
- WARNING
- ERROR
- CRITICAL

## Architecture

- **Lexer** (`lexer.h/cpp`): Tokenization of C source
- **Parser** (`parser.h/cpp`): Syntax analysis and AST generation
- **Compiler** (`compiler.h/cpp`): Code generation and compilation pipeline
- **Logger** (`logger.h/cpp`): Error logging to file
- **Platform Support** (`dos_support.h/cpp`, `android_support.h/cpp`)

## License

MIT
