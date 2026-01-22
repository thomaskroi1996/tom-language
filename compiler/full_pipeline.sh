# remove build dir if it exists
rm -rf build

# make build dir make build files
mkdir build && cd build
cmake ..

# build compiler
make

# compile with our compiler
./tom_compiler ../test.tom

# assemble the produced machine code
nasm -felf64 out.asm

# link to produce executable
ld out.o

# run output
./a.out

# echo last executed syscall
echo $?
