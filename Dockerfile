# Use a base image with the necessary development tools
FROM gcc:latest

# Install any additional dependencies needed for the C files
RUN apt-get update && apt-get install -y \
    libx11-dev

# Set the working directory in the container
WORKDIR /app

# Copy the C files into the container
COPY angrybird.c /app
COPY gfx.c /app
COPY gfx.h /app

# Compile the C files
RUN gcc -o angrybird angrybird.c gfx.c -lm -lX11

# Set the entry point for the container
CMD ["./angrybird"]