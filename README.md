# Function Plotter

A mathematical function plotting library developed as part of the Johns Hopkins University course:
**EN.601.220 Intermediate Programming (Summer 2022)**

## Course Project Overview

This project implements a function plotter that demonstrates key concepts from Intermediate Programming including:
- Object-oriented design
- Data structures and algorithms
- File I/O
- Graphics programming
- Error handling

## Features

- Parse and plot mathematical expressions
- Support for multiple mathematical functions:
  - Trigonometric functions (sin, cos)
  - Basic arithmetic operations (+, -, *, /)
- Customizable plot bounds and dimensions
- Fill options:
  - Fill above function
  - Fill below function
  - Fill between functions
- Custom color support for functions and fills
- PNG output generation

## Components

### Core Components

- **Expression Parser**: Parses mathematical expressions into evaluatable trees
- **Function Handler**: Manages mathematical functions and their properties
- **Plot Manager**: Controls plot settings, functions, and fills
- **Renderer**: Generates the final image output

### Expression Support

- Variables (x)
- Constants (π)
- Literals (numbers)
- Functions:
  - Trigonometric (sin, cos)
  - Arithmetic operations (+, -, *, /)

### Visualization Features

- Customizable bounds (xmin, xmax, ymin, ymax)
- Adjustable image dimensions (width, height)
- Color customization for functions
- Fill opacity control
- PNG image output

## File Structure

### Core Files
```
├── main.cpp           - Program entry point
├── Makefile          - Build configuration
├── README.md         - Project documentation
├── UMLDiagram.pdf    - Class design documentation
├── gitlog.txt        - Version control log
```

### Expression System
```
├── expr/
│   ├── expr.h        - Base expression interface
│   ├── expr.cpp      - Expression implementation
│   ├── expr_parser.h - Expression parsing interface
│   └── expr_parser.cpp - Expression parser implementation
```

### Plot Components
```
├── plot/
│   ├── plot.h        - Plot management interface
│   ├── plot.cpp      - Plot implementation
│   ├── bounds.h      - Boundary handling interface
│   ├── bounds.cpp    - Boundary implementation
│   ├── fill.h        - Fill area interface
│   ├── fill.cpp      - Fill implementation
│   ├── func.h        - Function interface
│   └── func.cpp      - Function implementation
```

### Rendering System
```
├── render/
│   ├── renderer.h    - Renderer interface
│   ├── renderer.cpp  - Renderer implementation
│   ├── image.h       - Image handling interface
│   ├── image.cpp     - Image implementation
│   ├── pnglite.h     - PNG library interface
│   └── pnglite.c     - PNG library implementation
```

### Utility Components
```
├── util/
│   ├── color.h       - Color definitions
│   ├── exception.h   - Exception handling interface
│   ├── exception.cpp - Exception implementation
│   ├── reader.h      - Input reading interface
│   └── reader.cpp    - Input reading implementation
```
## Building

Use the included Makefile:

```bash
make
```

## Academic Integrity

This code is part of the JHU EN.601.220 Intermediate Programming course. Please follow your institution's academic integrity guidelines when viewing or using this code.

## License

Course Material - Johns Hopkins University EN.601.220 Intermediate Programming (Summer 2022)
