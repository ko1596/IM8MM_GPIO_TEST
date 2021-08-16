docker: 192.168.1.200  advt advt
filezilla: 192.168.1.200 user 123456789
docker ps -a
user@git-u1664:~$ docker ps -a
CONTAINER ID        IMAGE                     COMMAND             CREATED             STATUS                     PORTS               NAMES
3742ca706c83        ubuntu:18.04              "/bin/bash"         2 months ago        Exited (0) 2 months ago                        hardcore_elbakyan
ded14a49880c        advrisc/u18.04-imx8lbv1   "/bin/bash"         3 months ago        Up 3 days                                      imx8mm-sdk
507bbace5351        advrisc/u18.04-imx8lbv1   "/bin/bash"         3 months ago        Exited (255) 3 weeks ago                       imx8mm-image
1c25897e25d6        advrisc/u16.04-imx8lbv1   "/bin/bash"         14 months ago       Exited (0) 2 months ago                        greenidea-imx8lbv1-sdk
3d37c0891304        advrisc/u16.04-imx8lbv1   "/bin/bash"         15 months ago       Exited (0) 14 months ago                       imx8mm02


docker start imx8mm-sdk
docker exec -it imx8mm-sdk /bin/bash

cd /home/adv/adv-release-bsp  (cd /home/user/yocto_imx8/sdk)

mkdir  user-DIR

source /home/adv/adv-release-bsp/build_sdk/tmp/work/aarch64-poky-linux/meta-toolchain/1.0-r7/sdk/image/opt/fsl-imx-xwayland/4.14-sumo/environment-setup-aarch64-poky-linux

cd /home/adv/adv-release-bsp/D88SDK-M0/Ta5320H_G