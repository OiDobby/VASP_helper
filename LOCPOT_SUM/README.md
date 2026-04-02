##USAGE
1. Prepare the Files, which are LOCPOT and POSCAR (or CONTCAR).  
    - POSCAR or CONTCAR should be required
2. complie VASP_LOCPOT-sum.c  
    - compling command as follow:
    ```shell
    gcc VASP_LOCPOT-sum.c -lm -o "excute_file_name.x"
    ```
    - "excute_file_name.x" can be changed, e.g. locpot.x
3. Run the excute file in target directory, which include LOCPOT and POSCAR (or CONTCAR)
