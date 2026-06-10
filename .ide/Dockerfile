# =============================================================================
# Cloud Development Environment for Unit 1: C Fundamentals
#
# Everything in Dockerfile.ci + code-server + VSCode extensions
# Used by CNB "云原生开发" for student WebIDE
# =============================================================================

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# ===== Mirror acceleration =====
RUN sed -Ei "s@(security|ports|archive).ubuntu.com@mirrors.cloud.tencent.com@g" /etc/apt/sources.list.d/ubuntu.sources

# ===== System packages =====
RUN apt-get -o Acquire::Retries=5 update \
    && apt-get -o Acquire::Retries=5 install -y --no-install-recommends \
        build-essential \
        python3 python3-pip python3-venv \
        jq \
        git curl wget vim less file \
        ca-certificates \
        clangd \
        openssh-server \
    && rm -rf /var/lib/apt/lists/*

# ===== Install clings from PyPI =====
RUN pip install --break-system-packages clings

# ===== code-server =====
RUN curl -fsSL https://code-server.dev/install.sh | sh

# ===== VSCode extensions =====
RUN code-server --install-extension aixy.cnb-welcome \
    && code-server --install-extension llvm-vs-code-extensions.vscode-clangd \
    && code-server --install-extension formulahendry.code-runner \
    && code-server --install-extension redhat.vscode-yaml \
    && code-server --install-extension mhutchie.git-graph \
    && code-server --install-extension waderyan.gitblame

# ===== Verify toolchain =====
RUN gcc --version | head -n1 \
    && python3 --version \
    && clings -v \
    && echo "✅ Development environment ready"

ENV LANG=C.UTF-8
ENV LANGUAGE=C.UTF-8

WORKDIR /workspace
