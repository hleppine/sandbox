FROM debian

RUN apt-get update

RUN apt-get -y install \
    apt-utils \
    bash \
    build-essential \
    curl \
    gcc \
    nano

RUN USER=dockeruser && \
    GROUP=dockeruser && \
    groupadd -g 1000 dockeruser && \
    useradd -g dockeruser -u 1000 --no-create-home dockeruser && \
    mkdir -p /home/dockeruser && \
    chown dockeruser:dockeruser /home/dockeruser && \
    curl -SsL https://github.com/boxboat/fixuid/releases/download/v0.5.1/fixuid-0.5.1-linux-amd64.tar.gz | tar -C /usr/local/bin -xzf - && \
    cd /usr/local/bin && \
    chmod 4755 /usr/local/bin/fixuid && \
    mkdir -p /etc/fixuid && \
    printf 'user: dockeruser\ngroup: dockeruser\npaths: []\n' > /etc/fixuid/config.yml

USER dockeruser:dockeruser
ENTRYPOINT ["fixuid", "-q"]
