# Cheri-tests
Testing CHERI functionality
# How to use
We have provided a Makefile that compiles a program in the container. The simple way to use the Makefile is using the following command
````
make PROGRAM=name_of_your_file_without.c
````
then to run the program, start the VM. To start the vm make sure that the docker container is running, then in a new terminal run
````
docker exec -ti cheribsd-riscv /opt/cheri/cheribuild/cheribuild.py run-riscv64-purecap
````
Make folders opt/cheri to mirror the container (only do this one time)
````
mkdir -p /opt/cheri
````
First mount the containers opt folder 
````
mount_smbfs -I 10.0.2.4 -N //10.0.2.4/source_root /opt/cheri
````
This will mount the opt/cheri/ folder in the container to opt/cheri in the VM, meaning the programs can be found in that folder also

Make the program executable
````
chmod +x /opt/cheri/programs/hello_world
````
Run the program
````
./opt/cheri/programs/hello_world
````

**for an efficent workflow keep your VM running and use the Makefile to compile new programs that can be tested in the VM

## Docker container
We use a docker container containing the cheri toolchain, that includes an sdk, quemu and cheribsd.

To pull the container run the following command:
````
docker pull ctsrd/cheribsd-sdk-qemu-riscv64-purecap
````
Start the container
````
docker run -ti -d --name cheribsd-riscv ctsrd/cheribsd-sdk-qemu-riscv64-purecap:latest
````
This will start the container in detached mode. To attach to the container, run the following command:
````
docker attach cheribsd-riscv
````
This provides a shell that can be used to compile programmes.

To exit the container, type ``exit``.

This will stop the container. If we wan't to use the container again make sure to start the container agian.
````
docker start cheribsd-riscv
````
## Compiling cheri programs
To compile a program using the cheri enabled compiler, use clang compiler found in the docker container in `/opt/cheri/output/sdk/bin/clang`. 
We set the following compile flags:
- ``-g`` 
- ``-O2``
- ``--sysroot=/opt/cheri/output/rootfs-riscv64-purecap``: The sysroot folder needs to be specified, the compiler have trouble finding it otherwise
- ``-target riscv64-unknown-freebsd``: we are targeting riscv64 cheribsd
- ``-static``: Generates a statically linked binary 
- ``-fuse-ld=lld``: Uses LLVM's lld linker, which is needed for CHERI capability-aware linking
- ``-mno-relax``: Disables link-time relaxation optimizations, which seems to be problematic sometimes with CHERI.
- ``-march=rv64gcxcheri``: Targets 64-bit RISC-V with extensions and includes CHERI extensions.
- ``-mabi=l64pc128d``: pc tells the compiler to use 128-bit capabilities for pointers (CHERI Pure Capability mode, the VM is purecap).
- ``-Wall``
- ``-Wcheri``: CHERI-specific warnings
- ``-G0``
We have opted to cross compile our programs in the container, you can either install a text editor in the container or copy a program into the container.
````
docker cp path/to/file.c cheribsd-riscv:/opt/cheri//file.c
````
The VM we use to run programs has easy setup to mount the ``opt/cheri/`` folder to the VM, therefore it could be an idea to place programs in that folder, preferably in a new folder for programs:

````
mkdir cheri_programs
````
**Envoke the compiler:**
````
/opt/cheri/output/sdk/bin/clang -g -O2 \
    --sysroot=/opt/cheri/output/rootfs-riscv64-purecap \
    -target riscv64-unknown-freebsd \
    -static -fuse-ld=lld -mno-relax \
    -march=rv64gcxcheri -mabi=l64pc128d \
    -Wall -Wcheri -G0 \
    home/file.c -o hello_world
````
# QUEMU CHERIBSD VM
The CHERIBSD VM is very barebones and is quite slow when running it in a docker container, therefore we use it only for executing programs we have compiled. 

To start the vm make sure that the docker container is running, then in a new terminal run 
````
docker exec -ti cheribsd-riscv /opt/cheri/cheribuild/cheribuild.py run-riscv64-purecap
````
Make folders opt/cheri to mirror the container (only do this one time)
````
mkdir -p /opt/cheri
````
First mount the containers opt folder 
````
mount_smbfs -I 10.0.2.4 -N //10.0.2.4/source_root /opt/cheri
````
This will mount the opt/cheri/ folder in the container to opt/cheri in the VM, meaning the programs can be found in that folder also

Make the program executable
````
chmod +x /opt/cheri/programs/hello_world
````
Run the program
````
./opt/cheri/programs/hello_world
````
**If you exit the VM and want to start the VM again you have to also restart the docker container by exiting the container 





