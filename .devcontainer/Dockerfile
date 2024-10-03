FROM gcc

RUN apt update
RUN apt install -y gdb valgrind build-essential curl sed unzip git libssl-dev ca-certificates
RUN mkdir -p ~/tools

RUN apt install -y zsh
RUN apt install -y git zsh \
    && git clone https://github.com/ohmyzsh/ohmyzsh.git ~/.oh-my-zsh \
    && cp ~/.oh-my-zsh/templates/zshrc.zsh-template ~/.zshrc \
    && usermod -s /bin/zsh root

RUN apt install -y clangd

RUN apt autoremove -y \
    && apt clean -y \
    && rm -rf /var/lib/apt/lists/*