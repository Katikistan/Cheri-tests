# Cheri-tests
Testing CHERI functionality

## Docker container
We use a docker container containing the cheri toolchain, that includes an sdk, quemu and cheribsd.

To pull the container run the following command:
```
docker pull ctsrd/cheribsd-sdk-qemu-riscv64-purecap
```
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
``
docker start cheribsd-riscv
``

## Compiling cheri programs
To compile a program using the cheri enabled compiler, use clang compiler found in the docker container in `/opt/cheri/output/sdk/bin/clang`. 
We set the following compile flags:
- ``-g``:
- ``-O2``:
- ``--sysroot=/opt/cheri/output/rootfs-riscv64-purecap``:
- ``-target riscv64-unknown-freebsd``:
- ``-static``:
- ``-fuse-ld=lld``:
- ``-mno-relax``:
- ``-march=rv64gcxcheri``:
- ``-mabi=l64pc128d``:
- ``-Wall``:
- ``-Wcheri``: 
- ``-G0``:
