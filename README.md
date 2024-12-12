"Eng. Ahmed Métwalli" Section 11

Review PDF File: Secion11_Threads_Metwalli.pdf

Let's contain GCC Using docker:
Step 1: docker pull gcc:latest
Step 2: Navigate to the directory 
Step 3: docker run --rm -it -v "$(pwd):/workspace" -w /workspace gcc:latest bash
Step 4: Navigate to relevant folder then 
Step 5: gcc 3-1.c -o 3-1
Step 6: ./3-1