CONTAINER_NAME=cheribsd-riscv
DOCKER_IMAGE=ctsrd/cheribsd-sdk-qemu-riscv64-purecap
CLANG=/opt/cheri/output/sdk/bin/clang
SYSROOT=/opt/cheri/output/rootfs-riscv64-purecap
TARGET=riscv64-unknown-freebsd
MOUNT_PATH=/opt/cheri/programs
VM_COMMAND="python3 /opt/cheri/cheribuild/cheribuild.py run-riscv64-purecap"

CFLAGS=-g -O2 --sysroot=$(SYSROOT) -target $(TARGET) -static -fuse-ld=lld \
       -mno-relax -march=rv64gcxcheri -mabi=l64pc128d -Wall -Wcheri -G0

PROGRAM?=hello_world
SRC=$(PROGRAM).c
OUT=$(PROGRAM)

.PHONY: all run clean start-container stop-container

all: start-container transfer compile 

start-container:
	docker start $(CONTAINER_NAME) || docker run -ti -d --name $(CONTAINER_NAME) $(DOCKER_IMAGE)

stop-container:
	docker stop $(CONTAINER_NAME)

transfer:
	docker cp $(SRC) $(CONTAINER_NAME):$(MOUNT_PATH)/$(SRC)

compile:
	docker exec $(CONTAINER_NAME) $(CLANG) $(CFLAGS) $(MOUNT_PATH)/$(SRC) -o $(MOUNT_PATH)/$(OUT)

transfer-vm:
	docker exec $(CONTAINER_NAME) mkdir -p $(MOUNT_PATH)

run-vm:
	docker exec -ti $(CONTAINER_NAME) sh -c $(VM_COMMAND) 

clean:
	rm -f $(OUT)
	docker exec $(CONTAINER_NAME) rm -f $(MOUNT_PATH)/$(OUT)
