FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

# install dependencies once for image build. These dont install when running
RUN apt-get update && apt-get install -y \
	libglfw3-dev \
	imagemagick \
	build-essential \
	cmake \
	libx11-dev \
	libxrandr-dev \
	libxinerama-dev \
	libxcursor-dev \
	libxi-dev \
	libgl1-mesa-dev \
	&& apt-get clean \
	&& rm -rf /var/lib/apt/lists/*