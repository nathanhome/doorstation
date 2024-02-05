#RUN \
#    curl https://www.linux-projects.org/listing/uv4l_repo/lpkey.asc  | tee /etc/apt/trusted.gpg.d/uv4l_repo.asc && \
#    echo "deb https://www.linux-projects.org/listing/uv4l_repo/raspbian/stretch stretch main" | \
#            tee /etc/apt/sources.list.d/uv4l.list && \
#    apt-get update

RUN \
    apt-get update && \
    apt-get install -y --no-install-recommends ca-certificates nodejs npm && \