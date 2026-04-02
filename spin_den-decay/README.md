# VASP_CHGCAR-spin_anal

## Overview
This code reads a VASP `CHGCAR` file containing **spin density** data, extracts a 2D slice at a user-selected **c-axis coordinate**, and writes the spin-density plane to an output file.

The program is intended for simple analysis of spin-density distribution on a selected c-plane.

Main functions of the code:

- reads 3D grid data from `CHGCAR`
- detects the number of atoms and grid size
- reads lattice information
- asks the user for a c-axis position
- extracts the corresponding 2D spin-density plane
- writes the plane data to an output file
- additionally writes diagonal values for quick plotting/checking

---

## Required Files
Prepare the following file in the same directory:

- `CHGCAR`

## Notes
- The input `CHGCAR` must contain **spin density**, not total charge density.
- The program temporarily creates a `POSCAR` file from the header part of `CHGCAR` during execution.
- The selected plane is taken along the **c direction**.
- The code asks the user to enter the c coordinate manually.

---

## Compile
Compile the source code with:

    gcc VASP_CHGCAR-spin_anal.c -lm -o chgcar_spin.x

You may change the executable name freely. For example:

    gcc VASP_CHGCAR-spin_anal.c -lm -o mycode.x

---

## Usage
Run the executable in the directory containing `CHGCAR`:

    ./chgcar_spin.x

During execution, the program will ask:

    Please enter the c coordinate, which you want to check out.

Enter the real-space c coordinate value you want to analyze.

---

## Output
After execution, the following files are generated:

- `CHGCAR_spin-c`
- `diagonal`

### `CHGCAR_spin-c`
This file contains:

- grid size information
- 2D spin-density values on the selected c-plane

### `diagonal`
This file contains:

- diagonal values from the extracted 2D plane
- useful for quick plotting or checking the variation along the diagonal line

---

## What This Code Does
1. Reads the `CHGCAR` file
2. Determines the total number of atoms
3. Reads the 3D grid size (`NGX`, `NGY`, `NGZ`)
4. Extracts the 3D spin-density grid data
5. Reads lattice information from the structure header
6. Converts the input c coordinate into the nearest grid index
7. Extracts the corresponding 2D c-plane
8. Writes the 2D plane to `CHGCAR_spin-c`
9. Writes diagonal values of that plane to `diagonal`

---

## Typical Workflow
1. Prepare a spin-density `CHGCAR`
2. Compile `VASP_CHGCAR-spin_anal.c`
3. Run the executable
4. Enter the desired c coordinate
5. Check `CHGCAR_spin-c`
6. Optionally inspect `diagonal` for quick analysis

---

## Example Compile and Run

    gcc VASP_CHGCAR-spin_anal.c -lm -o chgcar_spin.x
    ./chgcar_spin.x

Example input during execution:

    10.5

This means the program will extract the spin-density plane closest to `c = 10.5` in real-space units.

---

## Caution
- Use a **spin-density CHGCAR** file, not a total charge-density file.
- The selected c coordinate should be within the lattice range.
- The program writes only a **single c-plane** per run.
- Temporary files created during execution are removed automatically at the end.

---
