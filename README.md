# Game Artificial Intelligence: Maze AI Project

## Project Overview

Welcome to the Game Artificial Intelligence repository! This project is focused on developing an advanced Maze AI using C++.

## Objectives
- **Maze Generation**: Create a complex maze structure.
- **AI Development**: Develop an intelligent AI to navigate through the maze.

## Technologies
- **Language**: C++
- **AI Techniques**: [*List any specific algorithms or techniques you plan to use*]

## Development Plan
- **Phase 1**: Design and implement the maze structure.
- **Phase 2**: Develop the AI algorithm to solve the maze.
- **Phase 3**: Optimize and test the AI for various maze complexities.

## Contributing
Contributions to the project are welcome. Please refer to the contribution guidelines for more information.

# Grading

## Basis

- [x] **Useful and Correct Class**
  - **Explanation**: Your code effectively uses classes (`MazeElement`, `Wall`, `Path`, etc.) to represent various concepts in your maze game.
  - **Why It's Useful and Correct**: Each class encapsulates specific data and behavior related to a maze element, aligning with the OOP principle of modular design.

- [x] **Useful and Correct Abstraction**
  - **Explanation**: The `MazeElement` class is an abstract base class with pure virtual functions like `getDescription()` and `getSymbol()`.
  - **Why It's Useful and Correct**: This abstraction allows you to define a general interface for all maze elements without specifying their exact behavior. Derived classes provide specific implementations.

- [x] **Useful and Correct Encapsulation**
  - **Explanation**: Data members in your classes are private (e.g., `sizeMaze` in `Maze`), with manipulation done through public methods (e.g., `printMaze()`).
  - **Why It's Useful and Correct**: Encapsulation hides the internal state of an object, exposing only safe and relevant operations to the outside world.

- [x] **Useful and Correct Inheritance**
  - **Explanation**: Classes such as `Wall`, `Path`, `Start`, etc., inherit from `MazeElement`.
  - **Why It's Useful and Correct**: Inheritance enables these classes to acquire properties and methods from `MazeElement`, showcasing hierarchical classification and code reuse.

- [x] **Useful and Correct Polymorphism**
  - **Explanation**: Polymorphism is evident in how derived classes override the virtual functions of `MazeElement`.
  - **Why It's Useful and Correct**: It allows objects of different classes to be treated uniformly through a common interface, like using `MazeElement` pointers in the `Maze` class.

- [x] **Useful and Correct Object Composition**
  - **Explanation**: The `Maze` class uses object composition, utilizing objects of type `MazeElement*`.
  - **Why It's Useful and Correct**: Composition builds complex structures (the maze) from simpler objects (maze elements), illustrating a "has-a" relationship.

- [x] **Useful and Correct Base Class**
  - **Explanation**: `MazeElement` serves as a base class.
  - **Why It's Useful and Correct**: It provides a common interface for different maze element types.

- [x] **Useful and Correct Abstract Base Class**
  - **Explanation**: `MazeElement` is an abstract base class as it contains pure virtual functions.
  - **Why It's Useful and Correct**: It establishes a contract for derived classes, ensuring they implement specific behaviors.

- [x] **Useful and Correct Virtual Function**
  - **Explanation**: The `getDescription()` and `getSymbol()` functions are virtual and overridden in derived classes.
  - **Why It's Useful and Correct**: This is a fundamental aspect of implementing polymorphism, allowing different behaviors for the same function call on objects of various classes.

- [x] **No Mistake in Object-Oriented Programming**
  - **Explanation**: Your implementation appears to adhere well to OOP principles. However, comprehensive code review and testing are necessary to ensure there are no logical errors or misuse of OOP concepts.



## Aanvullend
### Algemeen
- [x] clean main (i.e. nothing in the main that should be in a class)
- [x] no globals, but statics if needed
- [ ] correct protections
- [ ] maintainability by clean uniform code style and good function naming and/or comments everywhere
- [ ] separate header files
- [ ] one complete project that compiles and does not crash
- [ ] fully working project
- [ ] sufficient git commits (+/- weekly)
- [x] Week 1 - 12/11/2023 Print idee + Allows dynamic modification of each cell types
- [x] Week 2 - 13/11/2023 Maze Generator Works + All Basic Done
- [ ] Week 3
- [ ] Week 4
- [ ] Week 5
- [ ] Week 6
- [ ] correct files on git
- [ ] working build manual as readme on GitHub (project must be possible to build from scratch on a clean PC)

### OOP
- [ ] at least 2 default constructors
- [ ] at least 2 parameterized constructors
- [ ] at least 2 copy constructors
- [ ] at least 2 destructors
- [ ] member initialization in constructors (the stuff behind a colon)
- [ ] constructor forwarding
- [ ] useful proven (dynamic) polymorphism
- [ ] useful usage of "this" (if the code does not work without it)
- [ ] useful member function
- [ ] default values in function definition
- [ ] useful member variabel
- [ ] useful getters and setters for member variables
- [ ] correct usage of inline function
- [ ] useful template function or class
- [ ] useful friend function or class

### C++
- [ ] everything in one or more self-made namespace(s)
- [ ] 2 useful unsigned chars or other better usage of memory efficient type
- [ ] at least 4 useful const references for variables
- [ ] at least 4 useful const references for functions
- [ ] at least 4 useful bool
- [x] dynamic memory allocation (new)
- [x] dynamic memory removing (delete)
- [ ] 2 useful (modern) call-by-references
- [ ] useful string class usage
- [ ] useful container class
- [x] useful usage of nullptr
- [ ] useful usage of (modern) file-I/O
- [ ] useful exception handling
- [ ] useful usage of lambda function
- [ ] useful usage of threads

### Uitbreiding
- [ ] useful Qt class
- [ ] useful usage of signals/slots
- [ ] test-driven development (= written test plan or unit tests)
- [ ] solve bug ticket (with pull request or commit message issue link and issue branch)
- [ ] report a bug ticket on another project
- [ ] usage of a GUI
- [ ] usage of OpenGL or other 3D engine
- [ ] useful usage of an external library (not Qt)
- [ ] project that communicates (e.g. UART, BT) with hardware
- [ ] a nice extra that you think that should deserve grading (stuff you put time in and is not rewarded by an item above)