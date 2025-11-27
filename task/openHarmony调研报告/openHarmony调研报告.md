# openHarmony调研报告

OpenHarmony 是由开放原子开源基金会（OpenAtom Foundation）孵化并运营的开源分布式操作系统框架，目标是提供一个覆盖“全场景、全连接、全智能”的设备操作系统基础设施，面向 IoT / 智能终端（从超小内存 MCU 类到手机、平板、智能屏、车机等多类设备）。项目采用分层架构（从内核到系统服务、框架到应用），并包含分布式总线（DSoftBus）等跨设备协同能力，强调可裁剪与跨设备协同。有关项目定位与官方英文概述可参见 OpenHarmony 的官方文档与主页。

## 链接

- **OpenHarmony 官网:**  [openharmony.cn](https://www.openharmony.cn/)
- **开放原子开源基金会:**  [openatom.org](https://www.openatom.org/)
- **代码仓库 (Gitee):**  [gitee.com/openharmony](https://gitee.com/openharmony)
- **官方文档中心:**  [docs.openharmony.cn](https://docs.openharmony.cn/)
- **开发者社区 (开发者论坛):**  [developer.huawei.com/consumer/cn/forum/block/openharmony](https://www.google.com/search?q=https://developer.huawei.com/consumer/cn/forum/block/openharmony)
- ​**Robot SIG地址**​：[OpenHarmony Robot SIG](https://gitee.com/openharmony/community/tree/master/sig/sig_robotics)

## 技术架构

OpenHarmony整体遵从分层设计，从下向上依次为：内核层、系统服务层、框架层和应用层。系统功能按照“系统 \> 子系统 \> 组件”逐级展开，在多设备部署场景下，支持根据实际需求裁剪某些非必要的组件。OpenHarmony技术架构如下所示：

![](images/1.png)

**内核层**

- 内核子系统：采用多内核（Linux内核或者LiteOS）设计，支持针对不同资源受限设备选用适合的OS内核。内核抽象层（KAL，Kernel Abstract Layer）通过屏蔽多内核差异，对上层提供基础的内核能力，包括进程/线程管理、内存管理、文件系统、网络管理和外设管理等。
- 驱动子系统：驱动框架（HDF）是系统硬件生态开放的基础，提供统一外设访问能力和驱动开发、管理框架。

**系统服务层**

系统服务层是OpenHarmony的核心能力集合，通过框架层对应用程序提供服务。该层包含以下几个部分：

- 系统基本能力子系统集：为分布式应用在多设备上的运行、调度、迁移等操作提供了基础能力，由分布式软总线、分布式数据管理、分布式任务调度、公共基础库、多模输入、图形、安全、AI等子系统组成。
- 基础软件服务子系统集：提供公共的、通用的软件服务，由事件通知、电话、多媒体、DFX（Design For X） 等子系统组成。
- 增强软件服务子系统集：提供针对不同设备的、差异化的能力增强型软件服务，由智慧屏专有业务、穿戴专有业务、IoT专有业务等子系统组成。
- 硬件服务子系统集：提供硬件服务，由位置服务、用户IAM、穿戴专有硬件服务、IoT专有硬件服务等子系统组成。

根据不同设备形态的部署环境，基础软件服务子系统集、增强软件服务子系统集、硬件服务子系统集内部可以按子系统粒度裁剪，每个子系统内部又可以按功能粒度裁剪。

**框架层**

框架层为应用开发提供了C/C++/JS等多语言的用户程序框架和Ability框架，适用于JS语言的ArkUI框架，以及各种软硬件服务对外开放的多语言框架API。根据系统的组件化裁剪程度，设备支持的API也会有所不同。

**应用层**

应用层包括系统应用和第三方非系统应用。应用由一个或多个FA（Feature Ability）或PA（Particle Ability）组成。其中，FA有UI界面，提供与用户交互的能力；而PA无UI界面，提供后台运行任务的能力以及统一的数据访问抽象。基于FA/PA开发的应用，能够实现特定的业务功能，支持跨设备调度与分发，为用户提供一致、高效的应用体验。

## 内核架构

OpenHarmony 并不是单一内核：项目采用“多内核/内核子系统”策略（Kernel Subsystem / Kernel Abstraction Layer），根据设备资源选择不同内核实现。常见组合包括：

- ​**LiteOS 系列（LiteOS-A / LiteOS-Cortex-A / LiteOS-M）** ​：面向资源受限或嵌入式设备的轻量实时内核，OpenHarmony 对 LiteOS 做了衍生与适配（kernel\_liteos\_a 等仓库）。
- ​**Linux（Linux 内核 / AOSP 层）** ：面向资源更丰富的设备（如手机、平板、PC）时采用 Linux 内核/兼容层。
- ​**微内核/其他方案**​：社区与厂商在更高版本与商业分支中（例如 HarmonyOS Next / Huawei 的演进）也涉及微内核设计或混合内核策略。  
  因此，OpenHarmony 的“内核”实际上是可替换/可适配的：对低资源设备用 LiteOS，对复杂设备使用 Linux。官方 kernel 仓库（如 kernel\_liteos\_a）与项目文档都明确了这一路线。该点对理解设备分层与移植策略极重要。

## 系统类型及其适配的设备

OpenHarmony支持如下几种系统类型：

- 轻量系统（mini system）  
  面向MCU类处理器例如Arm Cortex-M、RISC-V 32位的设备，硬件资源极其有限，支持的设备最小内存为128KiB，可以提供多种轻量级网络协议，轻量级的图形框架，以及丰富的IOT总线读写部件等。可支撑的产品如智能家居领域的连接类模组、传感器设备、穿戴类设备等。
- 小型系统（small system）  
  面向应用处理器例如Arm Cortex-A的设备，支持的设备最小内存为1MiB，可以提供更高的安全能力、标准的图形框架、视频编解码的多媒体能力。可支撑的产品如智能家居领域的IP Camera、电子猫眼、路由器以及智慧出行领域的行车记录仪等。
- 标准系统（standard system）  
  面向应用处理器例如Arm Cortex-A的设备，支持的设备最小内存为128MiB，可以提供增强的交互能力、3D GPU以及硬件合成能力、更多控件以及动效更丰富的图形能力、完整的应用框架。可支撑的产品如高端的冰箱显示屏。

‍

## 机器人相关的应用 / 产业落地（现状与案例）

在官方层面，目前没有看到一个官方命名的机器人 “SIG”在 docs 页明确列出；不过产业与公司层面已经有基于 OpenHarmony 的机器人项目/产品与商业化探索：Chinasoft 等公司发布了基于 OpenHarmony 的机器人操作系统（M-Robots OS），明确将 OpenHarmony 用作机器人操作系统的基础以实现多机协作、低延迟控制与较宽的硬件兼容性。此外，社区中有将 OpenHarmony 移植到开发板 / 智能硬件，并在第三方项目中结合 AI 与机器人控制套件的案例。

[https://www.tipranks.com/news/company-announcements/chinasoft-launches-openharmony-based-robotic-os-to-revolutionize-robotics-industry?utm_source=chatgpt.com](https://www.tipranks.com/news/company-announcements/chinasoft-launches-openharmony-based-robotic-os-to-revolutionize-robotics-industry?utm_source=chatgpt.com)

OpenHarmony 上的 机器狗（robot dog）示例应用 / Demo——这是一个基于 ArkUI / eTS 的机器狗控制示例，说明了如何用 OpenHarmony 开发控制类机器人应用、如何通过 NAPI 发送控制命令并在特定开发板（示例中为润和大禹 HH-SCDAYU200）上部署运行。对想要做机器人控制应用的人非常有参考价值。  
[https://gitee.com/zhoushufang/knowledge_demo_temp/blob/master/docs/robot_dog_Dev/readme.md](https://gitee.com/zhoushufang/knowledge_demo_temp/blob/master/docs/robot_dog_Dev/readme.md?utm_source=chatgpt.com)

Gitee / 开源平台上与 “OpenHarmony + 机器人” 相关的仓库与探索页——在 Gitee 的“机器人”话题页与 OpenHarmony 仓库列表里可以检索到与机器人相关的 demo、桥接、驱动和工具仓库（例如机器人操作示例、ROS 桥接示例、硬件板级支持等），适合批量筛选并把感兴趣的仓库 fork / clone。下面是 Gitee 机器人话题入口：

[机器人 - 热门项目 - Gitee.com](https://gitee.com/explore/robot?page=3&utm_source=chatgpt.com)  
[https://gitee.com/openharmony](https://gitee.com/openharmony?utm_source=chatgpt.com)

## 在虚拟机 / 仿真环境中的可用性与开发方式

官方文档与社区实践表明，OpenHarmony 的开发流程经常在 **Docker + 容器化构建环境** 中进行（官方 docs 给出了获取镜像与在容器中构建的说明）；对于设备系统镜像的调试/运行，常见做法包括在 QEMU 等仿真器中运行（或用开发板/实体板）。也就是说：​**可以使用虚拟化/仿真（例如 QEMU）配合容器（Docker）来做交叉构建与早期测试，但对手机/复杂设备的完整功能测试通常仍需要真实硬件或专用模拟器/镜像**。官方 docs 的“get-code / gettools”与“Docker 环境”章节，以及社区教程中有 QEMU / 虚拟化的典型说明与示例。实务上：若想在 PC 上试运行 OpenHarmony，常见路径是用官方/第三方提供的开发板镜像或把系统移植到像 Raspberry Pi / RK 芯片的开发板上，或者使用 QEMU 做特定平台的仿真。

## 在虚拟机上安装

参考文案：[基于Ubuntu 20.04配置OpenHarmony开发环境OpenHarmony镜像以及SDK的编译需要基于Ubun - 掘金](https://juejin.cn/post/7257553293889634363)

更改软件源

```
sudo vim /etc/apt/sources.list # 使用vim打开文件，写入如下内容
```

ubuntu 20.04

```undefined
deb http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
```

ubuntu 18.04

```
deb http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
```

更新系统软件

```undefined
sudo apt update
sudo apt upgrade
```

执行如下命令即可安装编译OpenHarmony需要的所有工具。

```undefined
sudo apt install binutils git git-lfs gnupg flex bison gperf build-essential zip curl zlib1g-dev gcc-multilib g++-multilib libc6-dev-i386 lib32ncurses5-dev x11proto-core-dev libx11-dev lib32z1-dev ccache libgl1-mesa-dev libxml2-utils xsltproc unzip m4 bc gnutls-bin python3.8 python3-pip ruby libncurses5 default-jre default-jdk genext2fs liblz4-tool libssl-dev libxinerama-dev libxcursor-dev libxrandr-dev libxi-dev
```

```undefined
#设置git用户名：
git config --global user.name "username"
#设置git签名邮箱：
git config --global user.email "youremail@example.com"
#设置git凭证存储方式：
git config --global credential.helper store
```

配置ssh公钥

```undefined
ssh-keygen -t rsa -C "youremail@example.com"
#查看并复制ssh公钥，并将其添加至gitee的个人账户中
cat ~/.ssh/id_rsa.pub
#验证公钥是否添加成功
ssh -T git@gitee.com
```

下载安装repo工具：需要超级用户状态执行，结束后可退出

```undefined
curl -s https://gitee.com/oschina/repo/raw/fork_flow/repo-py3 > /usr/local/bin/repo
chmod a+x /usr/local/bin/repo
#python安装requests库
pip3 install -i https://repo.huaweicloud.com/repository/pypi/simple requests
```

从服务器上下载repo源代码(轻量化)

```undefined
repo init -u git@gitee.com:openharmony/manifest.git -b OpenHarmony-3.2-Release --no-repo-verify
#代码同步
repo sync -c
repo forall -c 'git lfs pull'
#预编译
bash build/prebuilts_download.sh
#编译rk3568镜像
sudo ./build.sh --product-name rk3568
```

```undefined
#安装缺失的依赖工具
sudo apt-get install u-boot-tools mtd-utils scons \
  gcc-arm-none-eabi gcc-arm-linux-gnueabi
```

```undefined
#下载预构建
sudo bash build/prebuilts_download.sh
```

```undefined
ubuntu@ubuntu-virtual-machine:~$ ls out/rk3568/
ability                       distributedhardware  resourceschedule
account                       doc                  rockchip_products
ai                            exe.unstripped       rom_statistics_table.json
all_host_symlink.json         filemanagement       sa_profile
all_parts_host.json           gen                  sdk-native
all_parts_info.json           global               security
applications                  graphic              sensors
args.gn                       hdf                  settingsnapi
arkcompiler                   hiviewdfx            sorted_action_duration.txt
arkui                         images.tar.gz        src
barrierfree                   innerkits            src_installed_parts.json
binary_installed_parts.json   inputmethod          src_sa_infos_tmp.json
build.1763895525.1229148.log  lib.unstripped       startup
build_configs                 location             systemabilitymgr
build.log                     Makefile             telephony
build.ninja                   mingw_x86_64         test
build.ninja.d                 module_list_files    tests
build.trace.gz                msdp                 theme
bundlemanager                 multimedia           third_party
-c                            multimodalinput      thirdparty
clang_x64                     NOTICE_FILES         time
common                        notification         toolchain.ninja
commonlibrary                 obj                  updater
communication                 ohos_declaration     usb
customization                 override             useriam
developtools                  packages             validation.yaml
deviceprofile                 PCID.sc              web
device_rk3568                 powermgr             window
diff_libinput_mmi             qrcode               wpa_supplicant-2.9
distributeddatamgr            request              xts

```

images.tar.gz是rk3568 的最终镜像包

```undefined
cd out/rk3568/
tar -xzvf images.tar.gz
```

使用命令查看，以下输出表明镜像生成成功，可以在 RK3568 或者模拟器中刷入使用。它包含了系统的根文件系统，是可以启动设备的核心部分。

```undefined
ubuntu@ubuntu-virtual-machine:~/out/rk3568$ file ~/out/rk3568/packages/phone/images/system.img
/home/ubuntu/out/rk3568/packages/phone/images/system.img: Linux rev 1.0 ext2 filesystem data, UUID=65edcde2-0b49-4384-ac7f-109c7fb5947d (extents) (64bit) (large files) (huge files)
```

‍
