FROM debian

RUN apt-get update

RUN apt-get -y install \
    apt-utils \
    bash \
    build-essential \
    cppcheck \
    curl \
    nano

RUN groupadd -g 1000 user && \
    useradd -g user -u 1000 --no-create-home user && \
    mkdir -p /home/user && \
    chown user:user /home/user && \
    curl -SsL https://github.com/boxboat/fixuid/releases/download/v0.5.1/fixuid-0.5.1-linux-amd64.tar.gz | tar -C /usr/local/bin -xzf - && \
    cd /usr/local/bin && \
    chmod 4755 /usr/local/bin/fixuid && \
    mkdir -p /etc/fixuid && \
    printf 'user: user\ngroup: user\npaths: []\n' > /etc/fixuid/config.yml

# ARG CPPCHECK_VERSION
# RUN --mount=type=bind,source=deps/cppcheck-2.10.tar.gz,target=/tmp/cppcheck-2.10.tar.gz \
#   mkdir -p /opt/cppcheck && \
#   cd /opt/cppcheck && \
#   tar xf /tmp/cppcheck-2.10.tar.gz --strip-components 1 --no-same-owner && \
#   make
#ENV PATH=/opt/cppcheck:${PATH}

USER user:user
ENTRYPOINT ["fixuid", "-q"]
