FROM debian

RUN apt-get update

RUN apt-get -y install \
    apt-utils \
    bash \
    build-essential \
    curl \
    gedit \
    nano

# TODO below fixuid version as some variable

RUN groupadd -g 1000 user && \
    useradd -g user -u 1000 --no-create-home user && \
    mkdir -p /home/user && \
    chown user:user /home/user && \
    curl -SsL https://github.com/boxboat/fixuid/releases/download/v0.5.1/fixuid-0.5.1-linux-amd64.tar.gz | tar -C /usr/local/bin -xzf - && \
    cd /usr/local/bin && \
    chmod 4755 /usr/local/bin/fixuid && \
    mkdir -p /etc/fixuid && \
    printf 'user: user\ngroup: user\npaths: []\n' > /etc/fixuid/config.yml

USER user:user
ENTRYPOINT ["fixuid", "-q"]
