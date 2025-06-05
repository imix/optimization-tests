# ---- Stage 1: Build binaries ----
FROM gcc:13 AS builder

WORKDIR /src

# Copy C source
COPY main.c .

# Build unoptimized binary
RUN gcc -o hash_unoptimized main.c -lcrypto

# Build optimized binary
RUN gcc -O3 -o hash_optimized main.c -lcrypto

# ---- Stage 2: Runtime container ----
FROM python:3.11-slim

WORKDIR /app

# Copy Python script
COPY loop.py .

# Copy built binaries from the builder stage
COPY --from=builder /src/hash_unoptimized .
COPY --from=builder /src/hash_optimized .

# Install OpenSSL runtime (needed for C binaries)
RUN apt-get update && apt-get install -y libssl3 && rm -rf /var/lib/apt/lists/*

# Default command (can override in docker run)
CMD ["bash"]

