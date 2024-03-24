FROM ubuntu:latest

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    libsdl2-dev \
    libsdl2-image-dev \
    libsdl2-ttf-dev \
    libsdl2-mixer-dev \
    make \
    libjansson-dev \
    build-essential \
    # Add any other dependencies your SDL2 program may require
    && rm -rf /var/lib/apt/lists/*

# Copy your SDL2 program's source code into the container
COPY . /app

# Set working directory
WORKDIR /app

# Compile your SDL2 program (replace "make" with your actual build command)
RUN make all

# Run your SDL2 program when the container starts
CMD ["./bin/game"]

