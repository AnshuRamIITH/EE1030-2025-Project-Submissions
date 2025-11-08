
# 🧮 SoftwareAssignment: SVD Image Compression using C

This project implements **Singular Value Decomposition (SVD)** from scratch in **C** to perform **image compression**.  
The implementation includes complete matrix operations, image I/O (JPG, PNG, PGM), and SVD computation via the **Power Iteration** method — all without external linear algebra libraries.

---

## 📂 Project Directory Structure
SoftwareAssignment/
│
├── codes/ # Source code directory
│ ├── c_libs/ # C headers and libraries
│ │ ├── matrixOps.c
│ │ ├── matrixOps.h
│ │ ├── svd.c
│ │ ├── svd.h
│ │ ├── imageTake.c
│ │ ├── imageTake.h
│ │
│ ├── c_main/ # C main programs
│ │ └── main.c
│ │
├── figs/ # Original and reconstructed images
│ ├── input.jpg
│ ├── reconstructed_k20.jpg
│ ├── reconstructed_k50.jpg
├── report.pdf # Main project report
│
└── README.md # Project overview


---

## 🚀 Features
- Reads **.jpg** and **.pgm** grayscale images  
- Computes SVD using a **Power Iteration** (no external math libraries)  
- Allows **variable compression levels** (`k` values)  
- Outputs compressed images as **.jpg** or **.pgm**  
- Displays compression ratio and execution time  

---

## 🧮 How It Works
The algorithm compresses an image matrix \( A \) into:

\[
A \approx U_k \Sigma_k V_k^T
\]

Only the top `k` singular values are kept.  
- Smaller `k` → higher compression, lower quality  
- Larger `k` → better quality, less compression  

---

## ⚙️ Build Instructions
Make sure you have a C compiler (like `gcc`)
then compile
gcc -o compress main.c matrixOps.c svd.c imageTake.c -lm

execute
./compress <input.ext> <outputName>

this generates multiple compressed images 
outputName_k5.jpg
outputName_k20.jpg
outputName_k50.jpg
outputName_k100.jpg