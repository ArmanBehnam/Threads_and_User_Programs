# Threads and User Programs

A complete implementation of threading system and user program support for the Pintos operating system. This project extends the basic Pintos kernel with advanced thread management, priority scheduling, and user program execution capabilities.

## Overview

This project implements two major components of an operating system:

**Threads**: Advanced thread management including priority scheduling, priority donation, and multi-level feedback queue scheduler (MLFQS).

**User Programs**: Complete user program support with system calls, process management, argument passing, and file system operations.

## Features Implemented

### Threading System
- **Priority Scheduling**: Threads run based on priority levels with preemption
- **Priority Donation**: Higher-priority threads donate priority to avoid priority inversion
- **MLFQS**: Multi-level feedback queue scheduler for fair CPU allocation
- **Synchronization**: Semaphores, locks, and condition variables with priority awareness
- **Timer Sleep**: Efficient sleep implementation without busy waiting

### User Programs
- **Process Execution**: Load and execute user programs with argument passing
- **System Calls**: 
  - File operations: `create`, `remove`, `open`, `close`, `read`, `write`
  - Process management: `exec`, `wait`, `exit`
  - System operations: `halt`
- **Memory Management**: Safe user memory access and validation
- **File System Interface**: Complete file descriptor management
- **Argument Passing**: Command-line argument parsing and stack setup

## System Requirements

- GCC cross-compiler for 80x86
- Perl 5.8.0+ (for utilities and testing)
- QEMU 2.0+ or Bochs 2.6+ emulator
- Make build system
- Linux/Unix environment

## Installation

```bash
# Clone the repository
git clone https://github.com/ArmanBehnam/Threads_and_User_Programs.git
cd Threads_and_User_Programs

# Set up build environment
export PATH=/path/to/cross-compiler:$PATH
```

## Building and Running

### Building the Kernel

```bash
# Build threads kernel
cd src/threads
make

# Build user programs kernel
cd src/userprog
make

# Build example programs
cd src/examples
make
```

### Running Tests

```bash
# Run with QEMU (recommended)
cd src/threads
pintos --qemu -- run alarm-single

# Run user program
cd src/userprog
pintos --filesys-size=2 -p examples/echo -a echo -- -f -q run 'echo hello world'
```

## Testing

### Thread Tests
```bash
cd src/threads
make check                    # Run all thread tests
make tests/threads/alarm-multiple.result   # Run specific test
```

### User Program Tests
```bash
cd src/userprog
make check                    # Run all user program tests
make tests/userprog/args-single.result     # Run specific test
```

### Test Categories
- **Alarm Tests**: Timer sleep functionality
- **Priority Tests**: Priority scheduling and donation
- **MLFQS Tests**: Multi-level feedback queue scheduler
- **System Call Tests**: File operations and process management
- **Argument Tests**: Command-line argument handling
- **File Tests**: File system operations

## Project Structure

```
├── doc/                    # Documentation and specifications
│   ├── threads.texi       # Threading project documentation
│   └── userprog.texi      # User programs documentation
├── src/
│   ├── threads/           # Core threading implementation
│   │   ├── thread.c       # Thread management
│   │   ├── synch.c        # Synchronization primitives
│   │   └── interrupt.c    # Interrupt handling
│   ├── userprog/          # User program support
│   │   ├── process.c      # Process loading and management
│   │   ├── syscall.c      # System call implementation
│   │   └── exception.c    # Exception handling
│   ├── lib/               # Library functions
│   ├── devices/           # Hardware device drivers
│   ├── filesys/           # File system
│   ├── examples/          # Example user programs
│   └── tests/             # Test suites
├── specs/                 # Hardware specifications
└── utils/                 # Build utilities
```

## Key Implementation Details

### Thread Scheduling
- **Priority Range**: 0 (lowest) to 63 (highest)
- **Priority Donation**: Recursive donation through lock chains
- **MLFQS**: 64 priority queues with load average calculation

### System Calls
| System Call | Description |
|-------------|-------------|
| `halt()` | Shut down the system |
| `exit(status)` | Terminate current process |
| `exec(cmd_line)` | Execute new process |
| `wait(pid)` | Wait for child process |
| `create(file, size)` | Create new file |
| `remove(file)` | Delete file |
| `open(file)` | Open file |
| `filesize(fd)` | Get file size |
| `read(fd, buffer, size)` | Read from file |
| `write(fd, buffer, size)` | Write to file |
| `seek(fd, position)` | Change file position |
| `tell(fd)` | Get current file position |
| `close(fd)` | Close file |


## Development Notes

### Debugging
```bash
# Debug with GDB
pintos --gdb --qemu -- run program
# In another terminal:
pintos-gdb kernel.o
```

## Performance Metrics

- **Context Switch Time**: ~10-50 microseconds
- **System Call Overhead**: ~1-5 microseconds  
- **Priority Donation Depth**: Supports unlimited chains
- **File System**: Handles files up to 8MB


## Acknowledgments

- Stanford CS 140 Pintos project
- Operating Systems course materials
- Pintos documentation and community

---

**Author**: Arman Behnam  
**Course**: Operating Systems  
**Institution**: Illinois Institute of Technology