# My Physics Engine

## Overview

This project is a simple physics engine that simulates the motion of a bullet fired from a gun towards a target. The engine calculates the trajectory of the bullet under the influence of gravity and displays the coordinates of the bullet's path. The results are visualized using a Python script that generates a graph of the coordinates.

## Features

- Simulates bullet motion with gravity
- Calculates and displays bullet trajectory
- Detects hit or miss based on target coordinates
- Generates a graph of the bullet's path using Matplotlib

## Files

- `my_Physics_Engine.c`: The main C file containing the physics simulation logic.
- `chartGenarator.py`: A Python script that reads the coordinates from a file and generates a graph.
- `coordinates.txt`: A temporary file used to store the coordinates of the bullet's path.

## How to Run

1. Compile the C code:
    ```sh
    gcc my_Physics_Engine.c -o my_Physics_Engine -lm
    ```

2. Run the compiled program:
    ```sh
    ./my_Physics_Engine
    ```

3. The program will generate a `coordinates.txt` file and call the Python script to generate a graph.

4. Ensure you have Python and Matplotlib installed to run the Python script:
    ```sh
    pip install matplotlib
    ```

## Example Output

The program will display the bullet's trajectory in the console and generate a graph showing the path of the bullet. If the bullet hits the target, it will display "HIT!" in the console; otherwise, it will display "MISS!".

## Dependencies

- GCC (for compiling the C code)
- Python 3.x
- Matplotlib (Python library for plotting)

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Author

Dimat
