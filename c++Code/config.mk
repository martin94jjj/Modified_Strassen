# C++ compiler
cxx=g++-7 -fopenmp  #-std=c++11 
#cxx=clang++  -std=c++11

# Compilation flags
cflags=-Wall -ansi -pedantic -O3 #-Wc++11-extensions -std=c++14

# BLAS/LAPACK flags for linear algebra
lp_lflags=-framework Accelerate

# FFTW flags (installed via Homebrew)
fftw_iflags=
fftw_lflags=-lfftw3

# libpng flags (installed via Homebrew)
png_iflags=
png_lflags=-lpng
