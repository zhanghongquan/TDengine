# This is a sample Image
FROM centos
MAINTAINER kjdaun@taosdata.com
RUN yum -y group install "Development Tools"
RUN yum -y install cmake.x86_64
RUN yum -y install net-tools
RUN yum -y install tmux
RUN yum -y tcpdump
RUN yum -y vim
WORKDIR /dkj
COPY ./ /dkj/
COPY ./tmux.conf /root/.tmux.conf 
VOLUME [ "/sys/fs/cgroup" ]
CMD ["/usr/sbin/init","/dkj/init.sh"]
