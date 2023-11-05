# ft_strace

![image](https://github.com/tmatis/ft_strace/assets/54767855/9323b904-f566-45e6-8460-d38dd6f3994f)

## Description

ft_strace is a simple implementation of the strace command. It allows you to trace the execution of a program and the system calls it makes.

## Build

```bash
make
```

> :warning: **This project only works on Linux**

### build with debug symbols

```bash
make debug
```

> This will generate a binary with debug symbols (./ft_strace_debug)

## Run unit tests

```bash
make unit
```

> This will run test for libft and ft_strace

## Usage

```bash
./ft_strace -h
```

## Examples

```bash
./ft_strace ls
```

```bash
./ft_strace -c ls
```
