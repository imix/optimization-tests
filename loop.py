import hashlib
import os
import time

LOOP_ITERATIONS = 1_000_000

def loop_not_unrolled():
    for i in range(4*LOOP_ITERATIONS):
        data = os.urandom(1024)
        hashlib.sha256(data).hexdigest()

def loop_unrolled():
    for i in range(LOOP_ITERATIONS):
        data = os.urandom(1024)
        hashlib.sha256(data).hexdigest()

        data = os.urandom(1024)
        hashlib.sha256(data).hexdigest()

        data = os.urandom(1024)
        hashlib.sha256(data).hexdigest()

        data = os.urandom(1024)
        hashlib.sha256(data).hexdigest()


if __name__ == "__main__":
    start = time.time()
    print(time.strftime("%H:%M:%S", time.gmtime(start)))
    loop_not_unrolled()
    elapsed = time.time() - start
    print(f"elapsed: {elapsed}")
    start = time.time()
    loop_unrolled()
    elapsed = time.time() - start
    print(f"elapsed: {elapsed}")
