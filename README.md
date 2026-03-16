*This project has been created as part of the 42 curriculum by tvithara.*

# 📡 Minitalk

A small client-server communication program that uses only UNIX signals to transmit data — one bit at a time.

---

## Description

Minitalk is a 42 school project where two programs communicate using only two UNIX signals: `SIGUSR1` and `SIGUSR2`.

The idea is simple: the **server** starts up and prints its PID. The **client** takes that PID and a string as arguments, then encodes each character bit by bit and sends it to the server using signals. The server receives the bits, rebuilds the characters, and prints the full message.

It's basically Morse code, but with signals instead of dots and dashes.

**How does bit encoding work?**
Each character is 8 bits. For every bit:
- `SIGUSR1` = bit is `0`
- `SIGUSR2` = bit is `1`

The client sends all 8 bits of each character in order. The server collects them, reconstructs the byte, and once all bits of a character are received, it prints the character.

---

## Instructions

### Compilation

```bash
make
```

This will compile both `server` and `client` executables.

To clean object files:
```bash
make clean
```

To remove all compiled files:
```bash
make fclean
```

To recompile from scratch:
```bash
make re
```

### Usage

**Step 1 — Start the server** (it will print its PID):
```bash
./server
```
Output example:
```
Server PID: 12345
```

**Step 2 — Run the client** with the server PID and a message:
```bash
./client 12345 "Hello, World!"
```

The server will print the received message.

The server stays alive after receiving a message and can handle multiple clients in a row without restarting.

---

## Project Structure

```
minitalk/
├── include/        # Header files
├── libft/          # Custom C library
├── src/            # Source files (client.c, server.c)
└── Makefile
```

---

## Resources

### Documentation & References
- [UNIX Signals — man 7 signal](https://man7.org/linux/man-pages/man7/signal.7.html)
- [sigaction — man 2 sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [kill — man 2 kill](https://man7.org/linux/man-pages/man2/kill.2.html)
- [Bitwise operations in C — GeeksForGeeks](https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/)
- [ASCII Table](https://www.asciitable.com/)

### AI Usage

Claude (claude.ai) was used during this project for the following:
- Understanding how UNIX signals work and the difference between `signal()` and `sigaction()`
- Learning how bit manipulation can be used to encode/decode characters
- Getting explanations of why `sigaction` is preferred over `signal` for reliability
- Generating this README
