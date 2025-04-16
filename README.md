# ASCII85_encoder-decoder

**Author:** Steniahin Danil
**Contacts:** st128493@student.spbu.ru

---

## Description

This program is an **ASCII85 encoder/decoder**, similar to the Unix `base64` utility.  
It reads data from standard input (STDIN), processes it, and writes the result to standard output (STDOUT).

- Encoder and decoder are implemented in **C++**.
- Unit tests are written using **Google Test**.
- Functionality is additionally verified using Python's `base64` utility.

---

##  Build

To build the project:

```bash
make

```

To build and run tests:
```bash

make test

```

To clean:

```bash

make clean

```

##  Run

./ascii85 "-e" or "-d"

    -e (or no argument): run as encoder

    -d: run as decoder
    
##  Recommendation


echo -n "message" | ./ascii85 [-e | -d]


./ascii85 [-e | -d] < input.txt > output.txt


The program is fully compatible with terminal and can be used interactively via pipes or files.
