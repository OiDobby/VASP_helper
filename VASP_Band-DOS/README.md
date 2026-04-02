# Band and DOS Analysis Utilities for VASP

## Overview
This directory contains C codes for analyzing VASP band structure and density of states (DOS) results.

The codes are designed to read `EIGENVAL` and/or `DOSCAR`, separate useful data into simpler text files, and in some cases generate gnuplot scripts and final EPS figures.

Included source files:

- `Band+DOS_Fin.c`
- `DOS_Fin.c`
- `decom-DOS_Fin.c`

---

## Files and Their Roles

### 1. `Band+DOS_Fin.c`
This program reads both `EIGENVAL` and `DOSCAR` and performs the following tasks:

- separates band structure data
- separates total DOS data
- separates atomic DOS data
- generates gnuplot scripts for band and DOS plots
- runs gnuplot automatically
- writes EPS output files

Main output files include:

- `up-eigenval`
- `down-eigenval`
- `kpnt-path`
- `DOSCAR_tot`
- `DOSCAR_atom#1`, `DOSCAR_atom#2`, ...
- `gnuband`
- `gnudos`
- `your_name-band.eps`
- `your_name-tdos.eps`

---

### 2. `DOS_Fin.c`
This program reads `DOSCAR` and splits DOS data into:

- total DOS
- atom-resolved DOS

Main output files include:

- `DOSCAR_tot`
- `DOSCAR_atom#1`, `DOSCAR_atom#2`, ...

This version is suitable when only DOS analysis is needed.

---

### 3. `decom-DOS_Fin.c`
This program also reads `DOSCAR` and splits DOS data, but it stores more detailed atomic DOS columns than `DOS_Fin.c`.

It is intended for more decomposed orbital DOS analysis.

Main output files include:

- `DOSCAR_tot`
- `DOSCAR_atom#1`, `DOSCAR_atom#2`, ...

---

## Required Files

### For `Band+DOS_Fin.c`
Prepare the following files in the same directory:

- `EIGENVAL`
- `DOSCAR`

### For `DOS_Fin.c`
Prepare the following file in the same directory:

- `DOSCAR`

### For `decom-DOS_Fin.c`
Prepare the following file in the same directory:

- `DOSCAR`

---

## Notes
- These codes automatically try to detect whether the calculation is spin-polarized.
- They also try to detect whether the DOS data corresponds to `d`-orbital or `f`-orbital projected DOS.
- `Band+DOS_Fin.c` requires `gnuplot` if you want to generate EPS figures automatically.
- `Band+DOS_Fin.c` asks the user to input the output figure name during execution.

---

## Compile

Compile each file with `gcc` and link the math library.

### Band + DOS
    gcc Band+DOS_Fin.c -lm -o banddos.x

### DOS only
    gcc DOS_Fin.c -lm -o dos.x

### Decomposed DOS
    gcc decom-DOS_Fin.c -lm -o decom_dos.x

---

## Usage

### 1. Band + DOS analysis
Run in the directory containing `EIGENVAL` and `DOSCAR`:

    ./banddos.x

During execution, the program asks for the output figure name.

Example:
    material1

Then the generated files will include:

    material1-band.eps
    material1-tdos.eps

---

### 2. DOS analysis only
Run in the directory containing `DOSCAR`:

    ./dos.x

---

### 3. Decomposed DOS analysis
Run in the directory containing `DOSCAR`:

    ./decom_dos.x

---

## Output Summary

### `Band+DOS_Fin.c`
Generated files:

- `up-eigenval`
- `down-eigenval`
- `kpnt-path`
- `DOSCAR_tot`
- `DOSCAR_atom#N`
- `gnuband`
- `gnudos`
- `*.eps`

### `DOS_Fin.c`
Generated files:

- `DOSCAR_tot`
- `DOSCAR_atom#N`

### `decom-DOS_Fin.c`
Generated files:

- `DOSCAR_tot`
- `DOSCAR_atom#N`

---

## What Each Output File Means

- `DOSCAR_tot`  
  total DOS data extracted from `DOSCAR`

- `DOSCAR_atom#N`  
  atom-resolved DOS for atom index `N`

- `up-eigenval`  
  separated band energies for one spin channel or the main band data

- `down-eigenval`  
  separated band energies for the second spin channel when spin is enabled

- `kpnt-path`  
  accumulated k-point path information for band plotting

- `gnuband`  
  gnuplot script for band structure plotting

- `gnudos`  
  gnuplot script for DOS plotting

---

## Typical Workflow

### For band + DOS plotting
1. Prepare `EIGENVAL` and `DOSCAR`
2. Compile `Band+DOS_Fin.c`
3. Run the executable
4. Enter the material name
5. Check the generated text files and EPS figures

### For DOS-only extraction
1. Prepare `DOSCAR`
2. Compile `DOS_Fin.c` or `decom-DOS_Fin.c`
3. Run the executable
4. Check `DOSCAR_tot` and `DOSCAR_atom#N`

---

## Source Summary
This README was written based on the behavior of:

- `Band+DOS_Fin.c`
- `DOS_Fin.c`
- `decom-DOS_Fin.c`
