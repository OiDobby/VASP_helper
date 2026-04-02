# procar_anal

## Overview
This code is a VASP post-processing utility for analyzing band structure, DOS, and projected band information using `EIGENVAL`, `DOSCAR`, and `PROCAR`.

The program performs the following tasks:

- reads band information from `EIGENVAL`
- reads total and atomic DOS from `DOSCAR`
- reads projected band weights from `PROCAR`
- separates spin-up and spin-down band data
- writes atom-resolved projected band data
- organizes DOS-related and projected-band-related output files into subdirectories

This code is intended for band/DOS/projection analysis after a VASP calculation.

---

## Required Files
Prepare the following files in the same directory:

- `EIGENVAL`
- `DOSCAR`
- `PROCAR`

## Notes
- The code automatically checks whether the calculation is spin-polarized.
- The code also tries to detect whether the projected DOS/orbital format corresponds to `d` or `f` orbitals.
- The number of ions in `DOSCAR` and `PROCAR` should be the same.
- The code recommends using a `DOSCAR` generated from a gamma-centered k-mesh.
- Temporary intermediate files are created during execution and then removed or reorganized.

---

## Compile
Compile the source code with:

    gcc procar_anal.c -lm -o procar_anal.x

You may change the executable name freely. For example:

    gcc procar_anal.c -lm -o mycode.x

---

## Usage
Run the executable in the directory containing `EIGENVAL`, `DOSCAR`, and `PROCAR`:

    ./procar_anal.x

---

## What This Code Does

### 1. Band analysis from `EIGENVAL`
The program reads `EIGENVAL` and extracts band energies along the k-point path.

Generated files include:

- `up-eigenval`
- `down-eigenval`
- `up_band`
- `dn_band`
- `kpnt-path`

### 2. DOS analysis from `DOSCAR`
The program reads `DOSCAR` and separates:

- total DOS
- atom-resolved DOS

Generated files include:

- `DOSCAR_tot`
- `DOSCAR_atom#1`, `DOSCAR_atom#2`, ...

### 3. Projected band analysis from `PROCAR`
The program reads `PROCAR`, separates projection data, and writes atom-resolved projected band files.

Generated files include:

- `up_proband-atom#1`, `up_proband-atom#2`, ...
- `dn_proband-atom#1`, `dn_proband-atom#2`, ...

Depending on the PROCAR format, the output columns may correspond to:

- non-decomposed `s p d tot`
- non-decomposed `s p d f tot`
- decomposed `s, p_y, p_z, p_x, d... , tot`
- decomposed `s, p..., d..., f..., tot`

---

## Output Files

### Band-related files
- `up-eigenval`  
  band data in matrix form for one spin channel

- `down-eigenval`  
  band data in matrix form for the second spin channel

- `up_band`  
  band data written band-by-band for spin up

- `dn_band`  
  band data written band-by-band for spin down

- `kpnt-path`  
  accumulated k-point path information

### DOS-related files
- `DOSCAR_tot`  
  total DOS extracted from `DOSCAR`

- `DOSCAR_atom#N`  
  atom-resolved DOS for atom index `N`

### PROCAR-related files
- `up_proband-atom#N`  
  atom-resolved projected band data for spin up

- `dn_proband-atom#N`  
  atom-resolved projected band data for spin down

---

## Output Organization
After execution, the code automatically organizes files into subdirectories.

### `DOS_files`
This directory stores DOS-related outputs such as:

- `DOSCAR_tot`
- `DOSCAR_atom#N`

### `pband_files`
This directory stores projected-band-related outputs such as:

- `up_proband-atom#N`
- `dn_proband-atom#N`
- `up_band`
- `dn_band`

---

## Typical Workflow
1. Prepare `EIGENVAL`, `DOSCAR`, and `PROCAR`
2. Compile `procar_anal.c`
3. Run the executable
4. Check the generated band, DOS, and projected band files
5. Inspect `DOS_files/` and `pband_files/` for organized results

---

## Example Compile and Run

    gcc procar_anal.c -lm -o procar_anal.x
    ./procar_anal.x

---

## Caution
- Make sure `EIGENVAL`, `DOSCAR`, and `PROCAR` come from consistent calculations.
- Make sure the number of atoms is consistent between `DOSCAR` and `PROCAR`.
- The code assumes a VASP output structure compatible with the parsing logic in this file.
- Different PROCAR formatting may affect the decomposition labels.

---
