# 🍽️ Philosophers

A multithreaded implementation of the classic dining philosophers problem using POSIX threads and mutexes in C.

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)](https://42.fr/)
[![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Threads](https://img.shields.io/badge/POSIX-Threads-orange)](https://en.wikipedia.org/wiki/POSIX_Threads)

## 📚 Table of Contents

- [About](#about)
- [The Problem](#the-problem)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Arguments](#arguments)
- [Implementation](#implementation)
- [Project Structure](#project-structure)
- [Examples](#examples)
- [Learning Objectives](#learning-objectives)
- [Author](#author)

## 🧠 About

The **Philosophers** project is a solution to the famous dining philosophers problem, a classic synchronization challenge in computer science. This implementation demonstrates key concepts in concurrent programming including:

- Thread management and synchronization
- Mutex usage and deadlock prevention
- Race condition handling
- Resource sharing between threads

## 🤔 The Problem

The dining philosophers problem involves `N` philosophers sitting around a circular table:

```
       🧔 Philosopher 1
          🍴
🧔 Phil 5      🧔 Phil 2
    🍴            🍴
🧔 Phil 4      🧔 Phil 3
          🍴
```

### Rules:
- Philosophers alternate between **thinking**, **eating**, and **sleeping**
- To eat, a philosopher needs **two forks** (left and right)
- Forks are shared between adjacent philosophers
- A philosopher dies if they don't eat within `time_to_die` milliseconds
- The simulation ends when a philosopher dies or all have eaten enough times

### Challenges:
- **Deadlock**: All philosophers pick up their left fork simultaneously
- **Race conditions**: Multiple threads accessing shared resources
- **Starvation**: Some philosophers never get to eat

## ✨ Features

- ✅ **Thread-safe implementation** using mutexes
- ✅ **Deadlock prevention** through proper resource ordering
- ✅ **Real-time monitoring** of philosopher states
- ✅ **Configurable parameters** for flexible testing
- ✅ **Death detection** with precise timing
- ✅ **Optional meal counting** for automatic termination
- ✅ **Memory management** with proper cleanup
- ✅ **Error handling** for invalid inputs

## 🛠️ Installation

### Prerequisites

- **GCC** or compatible C compiler
- **POSIX-compliant system** (Linux, macOS, WSL)
- **Make** utility
- **pthread** library support

### Build

```bash
# Clone the repository
git clone https://github.com/sobouriic/philosophers.git
cd philosophers

# Compile the project
make

# Clean build files (optional)
make clean
```

## 🚀 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Quick Start

```bash
# Basic example: 4 philosophers
./philo 4 410 200 200

# With meal limit: stop after each philosopher eats 5 times
./philo 4 410 200 200 5
```

## 📋 Arguments

| Position | Argument | Description | Required | Range |
|----------|----------|-------------|----------|-------|
| 1 | `number_of_philosophers` | Number of philosophers (and forks) | ✅ | 1-200 |
| 2 | `time_to_die` | Time in ms until death without eating | ✅ | ≥ 60 |
| 3 | `time_to_eat` | Time in ms spent eating | ✅ | ≥ 60 |
| 4 | `time_to_sleep` | Time in ms spent sleeping | ✅ | ≥ 60 |
| 5 | `number_of_times_each_philosopher_must_eat` | Max meals per philosopher | ❌ | ≥ 1 |

### Input Validation

- ✅ Only positive integers accepted
- ✅ Leading whitespace and `+` signs handled
- ✅ Integer overflow protection
- ✅ Comprehensive error messages

## 🔧 Implementation

### Core Structures

```c
typedef struct s_arg {
    int             number_of_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    unsigned long   start;
    pthread_mutex_t *forks;         // Fork mutexes
    pthread_mutex_t eat;            // Eating state protection
    pthread_mutex_t meal;           // Meal counting protection
    pthread_mutex_t print;          // Output synchronization
} t_arg;

typedef struct s_philo {
    int             id;             // Philosopher ID (1-N)
    int             eat_num;        // Remaining meals (-1 = unlimited)
    int             end;            // Termination flag
    unsigned long   last_time_eat;  // Last meal timestamp
    pthread_t       thread;         // Thread handle
    t_arg          *arg;            // Shared arguments
} t_philo;
```

### Synchronization Strategy

#### 🔒 Mutex Types
- **Fork mutexes**: One per fork, prevents concurrent access
- **Eating mutex**: Protects `last_time_eat` updates
- **Meal mutex**: Protects meal counting operations
- **Print mutex**: Ensures atomic message output

#### 🚫 Deadlock Prevention
- Consistent fork acquisition order
- Proper unlock sequence (reverse of lock order)
- Time-based monitoring for death detection

#### ⚡ Race Condition Prevention
- All shared data protected by appropriate mutexes
- Atomic operations for critical state changes
- Careful ordering of lock/unlock operations

### Thread Model

```c
// Main thread responsibilities:
- Argument parsing and validation
- Thread creation and management
- Death monitoring (infinite loop)
- Cleanup and termination

// Philosopher thread responsibilities:
- Eating cycle (take forks → eat → release forks)
- Sleeping period
- Thinking state
- Meal counting (if applicable)
```

## 📁 Project Structure

```
philosophers/
├── 📄 Makefile              # Build configuration
├── 📄 philosophers.h        # Header with structures and prototypes
├── 📄 main.c               # Entry point and main monitoring loop
├── 📄 parse.c              # Argument parsing and validation
├── 📄 parse_utils.c        # Utility functions (atoi, putstr, etc.)
├── 📄 thread.c             # Threading logic and philosopher routines
├── 📄 utils.c              # Time functions and utilities
└── 📄 README.md            # This documentation
```

### Key Functions

| File | Function | Purpose |
|------|----------|---------|
| `main.c` | `main()` | Program entry point and death monitoring |
| `parse.c` | `check_args()` | Validate and parse command line arguments |
| `parse.c` | `ft_init_arguments()` | Initialize philosopher and argument structures |
| `thread.c` | `create_threads()` | Create and start philosopher threads |
| `thread.c` | `routine()` | Main philosopher thread function |
| `thread.c` | `philosopher()` | Single eating cycle implementation |
| `thread.c` | `check_death()` | Monitor for death conditions |

## 💡 Examples

### Example 1: Basic Simulation
```bash
./philo 5 800 200 200
```
**Output:**
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
200 1 is sleeping
200 3 is sleeping
200 2 has taken a fork
200 4 has taken a fork
...
```

### Example 2: Death Scenario
```bash
./philo 4 310 200 100
```
**Output:**
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
...
310 2 is dead
```

### Example 3: Meal Limit
```bash
./philo 4 410 200 200 3
```
The simulation stops when all philosophers have eaten 3 times.

### Example 4: Edge Cases
```bash
# Single philosopher (should die - only one fork)
./philo 1 800 200 200

# Large number of philosophers
./philo 100 800 200 200
```

## 🎯 Learning Objectives

This project teaches:

### Threading Concepts
- ✅ **Thread creation** and management with `pthread_create()`
- ✅ **Thread synchronization** using mutexes
- ✅ **Shared memory** access patterns
- ✅ **Thread lifecycle** management and cleanup

### Concurrency Problems
- ✅ **Deadlock detection** and prevention strategies
- ✅ **Race condition** identification and resolution
- ✅ **Starvation** prevention techniques
- ✅ **Resource contention** management

### System Programming
- ✅ **Time management** and precision timing
- ✅ **Error handling** in multithreaded environments
- ✅ **Memory management** with dynamic allocation
- ✅ **Process monitoring** and state tracking

## 🏗️ Compilation

### Makefile Targets

```bash
make        # Build the executable
make clean  # Remove object files
make fclean # Remove all generated files
make re     # Clean rebuild
```

### Manual Compilation

```bash
gcc -Wall -Wextra -Werror -pthread \
    main.c parse.c parse_utils.c thread.c utils.c \
    -o philo
```

### Compiler Flags

- `-Wall -Wextra -Werror`: Strict error checking
- `-pthread`: Enable POSIX thread support
- Optimization flags can be added for performance testing

## 🧪 Testing

### Test Cases

```bash
# Normal cases
./philo 5 800 200 200        # Should run indefinitely
./philo 5 800 200 200 7      # Should stop after 7 meals each
./philo 4 410 200 200        # Should run without death

# Edge cases  
./philo 1 800 200 200        # Should die (impossible to eat)
./philo 2 800 200 200        # Minimal viable case

# Death cases
./philo 4 310 200 100        # Should die quickly
```

### Expected Behaviors

- **No deaths**: Philosophers continue eating indefinitely
- **Meal completion**: Simulation stops when all reach meal limit
- **Death detection**: Immediate termination with death message
- **Clean output**: No mixed or corrupted messages

## 🐛 Common Issues

### Deadlock Symptoms
- Program hangs indefinitely
- No output after initial messages
- All philosophers waiting for forks

### Race Condition Symptoms  
- Corrupted output messages
- Inconsistent death timing
- Unexpected philosopher states

### Memory Issues
- Segmentation faults
- Memory leaks (check with `valgrind`)
- Double-free errors

## 📈 Performance Considerations

- **Thread creation overhead**: Consider thread pooling for large N
- **Mutex contention**: Monitor lock contention with profiling tools
- **Memory usage**: Scales linearly with number of philosophers
- **Timing precision**: System-dependent, affects death detection accuracy

## 🤝 Contributing

While this is a school project, suggestions for improvements are welcome:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 👨‍💻 Author

**Sobouric** - *42 School Student*
- GitHub: [@sobouriic](https://github.com/sobouriic)
- Project completed: July 2023

## 📜 License

This project is part of the 42 School curriculum. Feel free to study the code for educational purposes.


---

*"The dining philosophers problem is a classic multi-process synchronization problem. It illustrates the challenges of coordinating shared resources among multiple processes or threads."* - Edsger Dijkstra

