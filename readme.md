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

eMMC
ls -l /run/media/mmcblk2p1
SD
ls -l /run/media/mmcblk1p1


unsigned char   dev_SPI_ML22[] = "/dev/spidev1.0";


 // SPI port Open  ------------------------------------------------
 fd_ml22_spi = open( dev_SPI_ML22, O_RDWR );
 if( fd_ml22_spi < 0 )   {
  printf("    XXXXX XXXXX  ERR: Open [%s] error.\n", dev_SPI_ML22);
  return -1;
 }
 printf( "    [%s] Open success  ========== \n", dev_SPI_ML22 );


 uint32_t   spi_modeW = 0x00;
 spi_modeW |= SPI_MODE_3;
 if( ioctl( fd_ml22_spi, SPI_IOC_WR_MODE, &spi_modeW) < 0 )  {
  printf("    XXXXX ERR: SPI_IOC_WR_MODE error.\n" );
  close( fd_ml22_spi );
  return -1;
 }

 P112    GPIO4  498
P113    GPIO5   133
P114    GPIO6   499
P115    GPIO7   500
P116    GPIO8   501
P117    GPIO9   502
P118    GPIO10  503
P119    GPIO11  131

ROM-5721 SMARC 
ROM-DB5901-SWA1

Jems.Cheng<Jems.Cheng@advantech.com.tw>

編輯i.mx 8mm kernel

從米爾的github上下載內核
git clone https://github.com/MYiR-Dev/myir-imx-linux.git -b develop

安裝相關的libery
sudo apt-get install libncurses5-dev
sudo apt-get install lib32ncurses5-dev
sudo apt-get install libncursesw5-dev

進入kernel設定中
make ARCH=arm menuconfig
Device Drivers->SPI support->User mode SPI device driver support[*](這邊案'Y'可以啟用)

進入myir-imx-linux\arch\arm64\boot\dts\myir\

下面這些是i.mx 8mm相關的設備樹檔案
Kernel arch\arm64\configs\mys_iot_defconfig 內核配置表
arch\arm64\boot\dts\myir\myb-imx8mm.dtsi 資源設備樹
arch\arm64\boot\dts\myir\mys-imx8mm-evk.dts 無顯示配置
arch\arm64\boot\dts\myir mys-imx8mm-evk-rpmsg.dts M4 設備樹
arch\arm64\boot\dts\myir\mys-imx8mm-lt8912-hontron-7.dts 7 吋螢幕顯示
arch\arm64\boot\dts\myir\mys-imx8mm-lt8912-atk-10-1.dts 10 吋螢幕顯示

回到 myir-imx-linux 資料夾下輸入下列指令就可以編譯dtb檔
make mys_iot_defconfig
make dtbs

生成的 dtb 文件在 arch/arm64/boot/dts/myir/mys*.dtb

編譯kernel遇到：“error : openssl/bio.h :No such file or folder”
安裝sudo apt install libssl-dev

------------------------------------------------------------------------------------------------

device/imx8m/evk_8mm/BoardConfig.mk	
新增

TARGET_BOARD_DTS_CONFIG += imx8mm-mipi-epson:fsl-imx8mm-evk-s1d13c00.dtb

指定產出 imx8mm-mipi-epson.img,之後用fastboot flash dtbo_a imx8mm-mipi-epson.img 更新到 evk上
/kernel_imx/arch/arm64/boot/dts/freescale/Makefile	
新增

fsl-imx8mm-evk-s1d13c00.dtb \   fo imx8mm

 
/kernel_imx/arch/arm64/boot/dts/freescale/fsl-imx8mm-evk.dts	
新增 pinctrl 到pinctrl_fec1: fec1grp { 裡面，因為 SPI driver dtsi會用到
        pinctrl_ecspi2: ecspi2grp {
            fsl,pins = <
                MX8MN_IOMUXC_ECSPI2_SCLK_ECSPI2_SCLK        0x82
                MX8MN_IOMUXC_ECSPI2_MOSI_ECSPI2_MOSI        0x82
                MX8MN_IOMUXC_ECSPI2_MISO_ECSPI2_MISO        0x82
            >;
        };

        pinctrl_ecspi2_cs: ecspi2cs {
            fsl,pins = <
                MX8MN_IOMUXC_ECSPI2_SS0_GPIO5_IO13        0x40000
            >;
        };

 
/kernel_imx/arch/arm64/configs/android_defconfig	
新增

add CONFIG_DRM_PANEL_EPSON_S1D13C00=y

 
/kernel_imx/arch/arm64/configs/defconfig	
新增

add CONFIG_DRM_PANEL_EPSON_S1D13C00=y

 
/kernel_imx/drivers/gpu/drm/panel/Kconfig	加上以下內容
 config DRM_PANEL_EPSON_S1D13C00
    tristate "Epson S1D12C00 MDC with MIP panel"
    depends on OF
    depends on DRM_MIPI_DSI
    depends on BACKLIGHT_CLASS_DEVICE
    help
      Say Y here if you want to enable support for Epson S1D12C00 MDC with MIP panel
      (240x320) panel.	 
/kernel_imx/drivers/gpu/drm/panel/Makefile	加上
obj-$(CONFIG_DRM_PANEL_EPSON_S1D13C00) += panel-epson-s1d13c00.o	 
/kernel_imx/arch/arm64/boot/dts/freescale/fsl-imx8mm-evk-s1d13c00.dts	
#include "fsl-imx8mm-evk.dts"

&ecspi2 {
    #address-cells = <1>;
    #size-cells = <0>;
    fsl,spi-num-chipselects = <1>;
    pinctrl-names = "default";
    pinctrl-0 = <&pinctrl_ecspi2 &pinctrl_ecspi2_cs>;
    cs-gpios = <&gpio5 13 GPIO_ACTIVE_LOW>;
    status = "okay";

    spidev0: spi@0 {
        reg = <0>;
        compatible = "epson,s1d13c00";
        spi-max-frequency = <500000>;
    };
};

 
/kernel_imx/drivers/gpu/drm/panel/panel-epson-s1d13c00.c	請根據spi driver去建立一個空殼的driver，並吐出 debug message(附在文章最後面)