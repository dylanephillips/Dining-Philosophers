# Dining Philosophers Simulation (Client-Server)

This project implements a **Dining Philosophers** simulation using a client-server architecture in C. Philosophers request forks from a central server to eat, think when forks are unavailable, and release forks after eating. The server manages fork availability to prevent conflicts.

## Features
- Multi-client architecture with a central server managing forks.
- Each philosopher behaves independently, thinking and eating.
- Fork request handling ensures no two philosophers pick the same fork simultaneously.
- Simple command-line interface for starting philosophers with unique IDs.

## Files
- `server.c` – Handles fork management and client requests.
- `client.c` – Simulates philosopher behavior: thinking, requesting forks, eating, and releasing forks.
- `Makefile` – Optional (compile instructions).
- `.gitignore` – Ignored files for git.

## How to Run
1. Compile both server and client:
    ```bash
    gcc server.c -o server
    gcc client.c -o client
    ```
2. Start the server:
    ```bash
    ./server
    ```
3. Start philosopher clients in separate terminals:
    ```bash
    ./client 0
    ./client 1
    ./client 2
    ./client 3
    ./client 4
    ```
4. Watch philosophers thinking, eating, and releasing forks.

## Controls
- Philosophers automatically request and release forks; no manual input is required.
- Each philosopher runs as a separate client process with a unique ID (0-4).

## License
This project is licensed under the **MIT License**. See LICENSE for details.

## Author
**Dylan Phillips**
