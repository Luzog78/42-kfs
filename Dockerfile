FROM gcc:15.2

RUN	apt-get update -y
RUN	apt-get install -y curl
RUN	apt-get install -y wget
RUN	apt-get install -y vim
RUN	apt-get install -y build-essential
RUN	apt-get install -y bison
RUN	apt-get install -y flex
RUN	apt-get install -y libgmp3-dev
RUN	apt-get install -y libmpc-dev
RUN	apt-get install -y libmpfr-dev
RUN	apt-get install -y texinfo
RUN	apt-get install -y libisl-dev
RUN	apt-get install -y gdb
RUN	apt-get install -y nasm
RUN	apt-get install -y grub-pc-bin
RUN	apt-get install -y grub-common
RUN	apt-get install -y binutils
RUN	apt-get install -y xorriso

COPY	./dist /workspace/dist
COPY	./src /workspace/src

WORKDIR	/workspace/src

CMD ["bash"]
