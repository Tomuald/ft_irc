<h1 align="center">
	🚀 42 FT_IRC
</h1>

<p align="center">
	<img alt="GitHub repo size" src="https://img.shields.io/github/repo-size/Tomuald/ft_irc?style=plastic&logo=linux&logoColor=yellow">
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/Tomuald/ft_irc?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/Tomuald/ft_irc?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/Tomuald/ft_irc?color=yellow" />
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
| PRIVMSG  | Sends <message> to <msgtarget>, which is usually a user or channel |
| KICK     | Used to kick a user from a channel with an optional message               |
| PART     | command logs you off and disconnects you from a channel                |
| QUIT     | A client session is terminated with a quit message.              |
| DIE     | Instructs the server to shut down. This command may only be issued by IRC server operators.              |
| MODE     | The MODE command is dual-purpose. It can be used to set both user and channel modes.             |
| OPER     |  Authenticates a user as an IRC operator on that server.            |
| PONG     |  This command is a reply to the PING command and works in much the same way.            |
| TOPIC     | Allows the client to query or set the channel topic on <channel>.             |
| WHO     | Returns a list of users who match <name>             |

## 🛠️ Team

- @LeonMoreno
- @Tomuald