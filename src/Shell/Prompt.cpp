/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** Prompt
*/

#include "Prompt.hpp"

#include <cerrno>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <unistd.h>

#include "TerminalGuard.hpp"

namespace shell {

Prompt::Prompt(std::string promptStr, std::function<void()> onIdle)
    : _prompt_str{std::move(promptStr)}, _on_idle{std::move(onIdle)}
{
}

// ── TTY helpers ──────────────────────────────────────────────────────────────

void Prompt::eraseLine() const
{
    write(STDOUT_FILENO, "\r\x1b[K", 4);
}

void Prompt::redraw() const
{
    write(STDOUT_FILENO, "\r", 1);
    write(STDOUT_FILENO, _prompt_str.c_str(), _prompt_str.size());

    const std::string &text = _buffer.text();
    write(STDOUT_FILENO, text.c_str(), text.size());

    if (!_buffer.atEnd()) {
        const std::size_t n   = text.size() - _buffer.cursor();
        const std::string esc = "\x1b[" + std::to_string(n) + "D";
        write(STDOUT_FILENO, esc.c_str(), esc.size());
    }
}

std::string Prompt::readSequence()
{
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) <= 0)
        return "";

    if (c != '\x1b')
        return std::string(1, c);

    // ESC: greedily read up to 2 more bytes within 5 ms
    std::string seq = "\x1b";
    for (int i = 0; i < 2; ++i) {
        pollfd pfd = {.fd = STDIN_FILENO, .events = POLLIN, .revents = 0};
        if (poll(&pfd, 1, 5) <= 0)
            break;
        char next = 0;
        if (read(STDIN_FILENO, &next, 1) <= 0)
            break;
        seq += next;
    }
    return seq;
}

// ── Main entry point ─────────────────────────────────────────────────────────

std::optional<std::string> Prompt::getline()
{
    if (!isatty(STDIN_FILENO)) {
        std::cout << _prompt_str << std::flush;
        std::string line;
        if (!std::getline(std::cin, line))
            return std::nullopt;
        return line;
    }

    TerminalGuard guard;
    _buffer.clear();
    eraseLine();
    write(STDOUT_FILENO, _prompt_str.c_str(), _prompt_str.size());

    while (true) {
        pollfd pfd = {.fd = STDIN_FILENO, .events = POLLIN, .revents = 0};
        const int ready = poll(&pfd, 1, 100);

        if (ready == -1) {
            std::cerr << strerror(errno) << std::endl;
            continue;
        }

        if (ready == 0) {
            eraseLine();
            if (_on_idle)
                _on_idle();
            redraw();
            continue;
        }

        const std::string seq = readSequence();

        if (seq == "\n" || seq == "\r") {
            write(STDOUT_FILENO, "\n", 1);
            return _buffer.text();
        }

        if (seq == "\x04") {
            if (_buffer.atStart() && _buffer.atEnd()) {
                guard.disable();
                write(STDOUT_FILENO, "\n", 1);
                return std::nullopt;
            }
            continue; // Ctrl+D on non-empty line: ignore (bash behaviour)
        }

        if (seq.empty())
            continue;

        if (!_dispatcher.dispatch(seq, _buffer)) {
            if (seq.size() == 1 && seq[0] >= 32 && seq[0] <= 126)
                _buffer.insert(seq[0]);
        }
        redraw();
    }
}

// ── Public interface ─────────────────────────────────────────────────────────

void Prompt::setPrompt(std::string promptStr) noexcept
{
    _prompt_str = std::move(promptStr);
}

const std::string &Prompt::getPrompt() const noexcept
{
    return _prompt_str;
}

void Prompt::print(const std::string &message)
{
    eraseLine();
    write(STDOUT_FILENO, message.c_str(), message.size());
    write(STDOUT_FILENO, "\n", 1);
    redraw();
}

} // namespace shell