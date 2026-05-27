# network_lib

A C++20 TCP networking library with an event-loop based on `poll(2)`, bundled with a TCP server, a TCP client, and an interactive shell framework.

## What has been implemented

### `network` (static library)

The core networking primitives:

- **`IOContext`** — event loop built on `poll(2)`. Supports `run()` (blocking loop), `poll()` (single tick), `postRead`, and `postWrite` for scheduling async operations.
- **`ConnectedSocket`** — wraps a TCP socket file descriptor. Exposes both synchronous (`read`, `write`) and asynchronous (`asyncReadSome`, `asyncWrite`) operations.
- **`ListeningSocket`** — wraps a passive (server-side) socket.
- **`Acceptor`** — accepts incoming connections asynchronously via `asyncAccept`.
- **`Endpoint`** — holds an IP address and port, wraps `sockaddr_in`.
- **`Buffer`** — lightweight `ConstBuffer` / `MutableBuffer` view types and `network::buffer()` helpers.
- **`Serializer`** — base for serializing structured data over the wire.
- **`Router`** — base for dispatching incoming messages to handlers.
- **`ErrorCode`** — custom `std::error_code` values for socket operations.

### `server` binary

A TCP server (`TCPServer`) that:

- Listens on a configurable port.
- Accepts clients asynchronously.
- Greets each client with `Connection accepted.`
- Reads newline-terminated (`\r\n`) messages via `ClientSession` and replies with `Message received...`

### `client` binary

A TCP client (`TCPClient`) that:

- Connects to the server on startup and prints the welcome message.
- Launches an interactive shell (`tcp/client> ` prompt).
- Exposes a `send <message>` command that sends a message to the server and prints the response.

## Requirements

- CMake >= 3.28
- A C++20-capable compiler (GCC 12+ or Clang 16+)

## Build

```bash
cmake -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build cmake-build-debug
```

The `server` and `client` binaries are placed in the **project root** after a successful build.

## Run

Start the server on a port of your choice:

```bash
./server 8080
```

In a separate terminal, start the client:

```bash
./client
```

The client connects to `127.0.0.1:8080` by default. Once connected, use the interactive shell:

```
tcp/client> send hello
Message received...

tcp/client> help send
Usage: send <message>
  Send a command to the server

Arguments:
  message  (required)  Message to send to the server

tcp/client> exit
```

On the server side:



```shell
➜  bash> ./server 8080
[ACCEPTOR] Connection received ...
Connection accepted from: 127.0.0.1:56208
Hello from client

Connection closed
```