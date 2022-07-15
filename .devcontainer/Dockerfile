FROM python:3.8
# ARG USERNAME=vscode
# ARG USER_UID=1000
# ARG USER_GID=$USER_UID


# RUN apt-get update \
#     && apt-get -y install --no-install-recommends apt-utils dialog 2>&1 \
#     && apt-get -y install git iproute2 procps lsb-release gdb clang-format libboost-all-dev libtinfo5\
#     && groupadd --gid $USER_GID $USERNAME \
#     && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
#     && apt-get install -y sudo \
#     && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME\
#     && chmod 0440 /etc/sudoers.d/$USERNAME \ 
#     && apt-get autoremove -y \
#     && apt-get clean
RUN apt-get update \
    && apt-get -y install --no-install-recommends apt-utils dialog 2>&1 \
    && apt-get -y install git iproute2 procps lsb-release gdb clang-format libboost-all-dev libtinfo5 cmake\
    && apt-get autoremove -y \
    && apt-get clean
RUN git clone https://github.com/atcoder/ac-library.git /lib/ac-library
ENV CPLUS_INCLUDE_PATH /lib/ac-library

RUN wget https://downloads.python.org/pypy/pypy3.6-v7.2.0-linux64.tar.bz2 && \
    mkdir -p /opt/ && \
    tar jxvf pypy3.6-v7.2.0-linux64.tar.bz2 -C /opt/ && \
    ln -s /opt/pypy3.6-v7.2.0-linux64/bin/pypy3 /bin/pypy3

# USER $USERNAME
# ENV PATH /home/vscode/.local/bin:$PATH
ENV PATH /root/.local/bin:$PATH
ENV PATH /workspaces/atc-env/scripts/atcoder_scripts:$PATH
# ENV NVM_DIR /home/vscode/.nvm
ENV NVM_DIR /root/.nvm
RUN mkdir -p ${NVM_DIR}
ENV CPLUS_INCLUDE_PATH $CPLUS_INCLUDE_PATH:/usr/include/python3.7
ENV CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:~/.cache/cxxpch/
#http://tatamo.81.la/blog/2018/12/07/atcoder-cli-installation-guide/
RUN curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.38.0/install.sh | bash && \
    . $NVM_DIR/nvm.sh && \
    nvm install node && \
    npm install -g npm && \
    npm install -g atcoder-cli
WORKDIR /workspaces/