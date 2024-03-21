<h1 align="center">
	🚀 42 FT_IRC
</h1>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/Tomuald/ft_irc?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/Tomuald/ft_irc?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/Tomuald/ft_irc?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/Tomuald/ft_irc?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/Tomuald/ft_irc?color=green" />
</p>

<p> Internet is ruled by solid standards protocols that allow connected computers to interact
with each other. It’s always a good thing to know.
</p>

## 💡 About the project

    🚀 TLDR: Create your own IRC server, following Internet RFC standards.
    You will learn a lot about processes and file descriptors.

## Screenshots

<img src="img/ft_irc.gif" width="800"/>

## Skills:

- Rigor
- Unix.
- Teamwork.
- Sockets.
- CPP
- OPP

## 🎯 Objectives:

- Implement a server that handles multiple clients efficiently using I/O multiplexing within a single thread.
- The server receives messages from clients and forwards them to the channel(s)/client(s) currently connected to the server.
- It should be accessed and utilized with various compliant IRC clients, adhering to the IRC RFC documentation.

## ✔️ Getting Started

```Bash
	make
	./ircserv <port> <password>
```

## ✨ Usage

| Commande | description                        |
| -------- | ---------------------------------- |
| PASS     | To set a 'connection password'     |
| NICK     | To assign a nickname to the user or change an existing one.|
| USER     | used at the beginning of connection to specify the username, hostname and realname of a new user    |
| JOIN     | used by a user to request to start listening to the specific channel.          |
| PRIVMSG  |  |
| KICK     |                |
| PART     |                |
| QUIT     | A client session is terminated with a quit message.              |

## 🛠️ Team

- @LeonMoreno
- @Tomuald