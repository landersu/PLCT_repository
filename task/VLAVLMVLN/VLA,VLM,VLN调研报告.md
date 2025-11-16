# VLA,VLM,VLN调研报告

vla
[OpenVLA](http://127.0.0.1:63305/#20251116132021-ooraa5x)：开放式视觉-语言-动作模型，用于机器人操纵任务
[Gato](http://127.0.0.1:63305/#20251116135204-v5l05d7)：DeepMind的多任务多模态智能体
[RT-2](http://127.0.0.1:63305/#20251116141842-jrxcorf)：RT-1升级版，支持VLM
[Mobile ALOHA](http://127.0.0.1:63305/#20251116143605-1k1p9g4)：移动双臂操纵平台
[Vlaser](http://127.0.0.1:63305/#20251116162637-zl6jvot)：强化“推理 + 控制”能力的 VLA 架构
[Evo‑1](http://127.0.0.1:63305/#20251116163426-tkge19q)：轻量化 VLA 模型，参数较少，部署性强
[CogACT](http://127.0.0.1:63305/#20251116164509-o09n3m5)：机器人操作为目标的 VLA 模型
[Octo](http://127.0.0.1:63305/#20251116173609-6n1yms5)：能够处理多种机器人任务

vlm
[LLaVA-NeXT](http://127.0.0.1:63305/#20251116150753-9ibdjzr)：大规模视觉-语言助手，开源VLM代表作LLaVA的改进版，支持高分辨率图像
[Qwen-VL](http://127.0.0.1:63305/#20251116152213-kytsbqx)：阿里巴巴的通用视觉语言模型
[InternVL](http://127.0.0.1:63305/#20251116171030-0tf1c9p)：商汤科技的高效VLM
[CogVLM](http://127.0.0.1:63305/#20251116172026-omukm6s)：清华大学的VLM

vln
[Habitat 3.0](http://127.0.0.1:63305/#20251116151708-yqukpu5)：最新版本，支持多智能体
[VLN-CE](http://127.0.0.1:63305/#20251116152209-deg8g3o)：持续体现化学习
[SOON](http://127.0.0.1:63305/#20251116154145-6lkbdq8)：语义导向导航
[Dynam3D](http://127.0.0.1:63305/#20251116155327-f19s0br)：引入 3D 表示改善导航模型
[COSMO](http://127.0.0.1:63305/#20251116165706-gmf1176)：聚焦低成本、选择性记忆机制的导航模型
[BERT-based](http://127.0.0.1:63305/#20251116173845-ca4f3bg)：基于BERT的早期VLN方法
[ViLBERT](http://127.0.0.1:63305/#20251116173858-ic9cuja)：双流视觉语言预训练模型
[LANA](http://127.0.0.1:63305/#20251116173858-xndj48u)：专门用于导航任务
[Recurrent VLN Agent](http://127.0.0.1:63305/#20251116173859-6uxluzm)：使用循环结构处理序列化的导航指令

------

## VLA类

### 1.OpenVLA

项目链接：<https://github.com/openvla/openvla>
参考论文：<https://arxiv.org/html/2406.09246v1?utm_source=chatgpt.com>

#### 简介

基于互联网规模的视觉-语言数据和多样化的机器人演示预训练的大型策略有潜力改变我们教机器人新技能的方式：我们可以通过微调这些视觉-语言-动作（VLA）模型，而不是从头开始训练新的行为，从而获得强大且具有泛化能力的视觉运动控制策略。然而，VLA在机器人学中的广泛应用面临挑战：1）现有的VLA模型大多是闭源的，无法公开访问；2）以往的研究未能探索出有效的微调方法来为新任务调整VLA模型，而这正是VLA模型广泛应用的关键。为了解决这些挑战，我们推出了OpenVLA，一个7B参数的开源VLA模型，它是在多样化的97万条真实世界机器人演示数据上训练的。OpenVLA基于Llama 2语言模型，结合了融合了DINOv2和SigLIP预训练特征的视觉编码器。由于增加了数据多样性和新的模型组件，OpenVLA在通用操作任务中表现出色，在29个任务和多个机器人平台上，任务成功率比闭源模型（如RT-2-X 55B）高出16.5%，且参数量少了7倍。我们还展示了如何有效地对OpenVLA进行微调，在涉及多个物体和强语言理解能力的多任务环境中，取得了特别强的泛化能力，并且比从零开始的模仿学习方法（如Diffusion Policy）高出了20.4%。我们还探索了计算效率；作为单独的贡献，我们展示了OpenVLA可以通过现代低秩适应方法在消费者级GPU上进行微调，并通过量化高效部署，而不会影响下游任务的成功率。最后，我们发布了模型检查点、微调笔记本和我们的PyTorch代码库，支持在Open X-Embodiment数据集上大规模训练VLA模型。

#### 设备

机器人平台／品牌／型号：至少两种具体平台（WidowX + Google Robot RT‑series）被用于评估／训练。

显卡／硬件型号：训练阶段使用 64 × NVIDIA A100 GPUs。微调／部署阶段提到支持只用一块 NVIDIA A100 GPU或消费者显卡推理（但未官方完全详列）。

### 2.Gato

开源复刻仓库（非官方）： <https://github.com/OrigamiDream/gato>
官方论文：<https://arxiv.org/abs/2205.06175>

#### 简介

Gato 是一款 “通用智能代理”（Generalist Agent）模型，旨在用一个统一网络、统一权重来处理多模态、多任务、多体现（multi‑embodiment）的问题。该模型采用 Transformer 核心结构，将来自文本、图像、强化控制、机器人臂动作、按键操作、关节力矩、离散/连续动作等多种模态的数据都序列化为 token 流，然后在同一个网络中训练与推理。训练完成后，Gato 同一份权重即可应对例如：下棋／玩 Atari 游戏、进行图像描述、进行对话、控制真实机器人臂去堆叠积木等任务。Gato 的参数规模约 12 B参数，其训练覆盖了 600 多个任务。Gato 的设计理念是：通过数据、计算与模型参数规模的扩展，朝向“通用代理”方向迈进，而不仅仅是为每个专门任务训练一个模型。它在论文中提出：当下可实时控制机器人臂的操作点大约在 1.2 B 参数；未来随着硬件与架构提升，可继续扩大。

#### 设备

机器人臂实验中，有提及使用 “ robot arm with 3‑DoF cartesian velocity control, an additional DoF for velocity, and a discrete gripper action” 的配置。

关于显卡/具体 GPU 型号，论文中并未明确列出。

### 3.RT-2

项目链接：<https://github.com/google-research/robotics_transformer>

#### 简介

我们研究了如何将训练于互联网规模数据上的视觉-语言模型直接融入端到端的机器人控制中，以增强模型的泛化能力并启发语义推理的涌现。我们的目标是使一个单一的端到端训练模型，既能学习将机器人观察映射为动作，又能享受到在网络上的语言和视觉-语言数据进行大规模预训练的好处。为此，我们提出了将最先进的视觉-语言模型与机器人轨迹数据以及互联网规模的视觉-语言任务（如视觉问答）共同微调。与其他方法不同，我们提出了一种简单而通用的方法来实现这一目标：为了将自然语言响应和机器人动作适配到相同的格式中，我们将动作表示为文本标记，并将其直接纳入模型的训练集，就像自然语言标记一样。我们将这类模型称为视觉-语言-动作模型（VLA），并实例化了一个名为 RT-2 的模型。我们广泛的评估（6千次评测）表明，我们的方法能带来高效的机器人策略，并使 RT-2 从互联网规模的训练中获得一系列涌现能力。这些能力包括显著提高了对新物体的泛化能力，能够理解机器人训练数据中没有出现过的指令（例如将物体放置到特定的数字或图标上），以及能够根据用户指令进行基本的推理（例如捡起最小的或最大的物体，或捡起离其他物体最近的物体）。我们还进一步展示了，结合思维链推理可以使 RT-2 执行多阶段的语义推理，例如确定哪个物体可以作为临时锤子（石头），或者哪个饮品最适合疲劳的人（能量饮料）。

#### 设备

机器人平台：Everyday Robots 的移动操控机器人（Google/Alphabet X 部门研发的移动底座+机械臂平台，官方论文与博客以“Everyday Robots”平台名称出现）。

训练/计算设备：官方仓库与论文未在公开页面中详细列出具体显卡型号。

传感与模型骨干：视觉传感来自机载相机；模型为 Transformer 架构的策略网络。

### 4.Mobile ALOHA

主页：<https://mobile-aloha.github.io/>
官方论文：[mobile-aloha.pdf](https://mobile-aloha.github.io/resources/mobile-aloha.pdf)
代码仓库：[github.com/MarkFzp/mobile-aloha](https://github.com/MarkFzp/mobile-aloha)

#### 简介

模仿学习从人类示范中获得了在机器人领域的显著表现。然而，大多数研究主要集中在桌面操作上，缺乏实现广泛应用任务所需的机动性和灵活性。在本研究中，我们开发了一种系统，用于模仿需要双臂协调和全身控制的移动操作任务。我们首先提出了Mobile ALOHA，这是一种低成本的全身遥操作系统，用于数据收集。它通过增加移动底座和全身遥操作界面来扩展ALOHA系统。利用Mobile ALOHA收集的数据，我们进行了监督行为克隆，并发现与现有的静态ALOHA数据集共同训练能提高移动操作任务的性能。每个任务50次示范后，联合训练可以将成功率提高最多90%，使Mobile ALOHA能够自主完成复杂的移动操作任务，如翻炒并上菜、打开双门壁橱储存重型炊具、呼叫并进入电梯，以及用厨房水龙头轻轻冲洗脏锅。

#### 设备

移动底座：论文中提及使用 “Tracer” 移动底盘用于承载双臂系统与遥操作装置。
双臂系统：平台扩展自 ALOHA 系统，具备双臂、多自由度操作能力。
臂可达范围：其硬件规格提到“臂从地面约 65 cm 到 200 cm 的垂直高度”“从基座向外可延伸约 100 cm”。
拖拽力、负载能力：规格中提到可提升拉力至 100 N（在1.5 m高度）或类似指标。

### ５.Vlaser

论文：[Vlaser: Vision-Language-Action Model with Synergistic Embodied Reasoning](https://arxiv.org/pdf/2510.11027)
代码：[github.com/OpenGVLab/Vlaser/](https://github.com/OpenGVLab/Vlaser/)

#### 简介

Vlaser 是一个开源的视觉-语言-动作（Vision-Language-Action, VLA）基础模型，旨在将高层次的语言推理能力（embodied reasoning）与低层次的机器人控制（action policy）结合起来。该模型建立在一个名为 Vlaser-6M 的大规模数据集之上，这个数据集专注于具身 (embodied) 场景的数据。通过这种训练，Vlaser 在多个具身推理基准 (benchmark) 上取得非常强的性能，包括空间推理 (spatial reasoning)、具身定位 (embodied grounding)、具身问答 (embodied QA) 以及任务规划 (task planning) 等。团队还系统地研究了不同视觉-语言模型 (VLM) 的初始化方式对下游 VLA 微调 (fine-tuning) 的影响，发现与机器人交互更贴近 (in-domain) 的数据比互联网规模 (web-scale) 的预训练数据更有助于提升 VLA 的收敛速度和任务成功率。最终，在机器人基准测试中，Vlaser 在 WidowX 机器人任务上达到了 SOTA（state-of-the-art）表现，在 Google Robot 基准上也表现竞争力。项目公开了模型权重 (VLM 和 VLA)、训练 & 推理代码、Vlaser-6M 数据生成流程等。

基于高质量的 Vlaser-6M 数据集，该模型在多种体现化推理基准测试中达到了 最新的性能水平（state-of-the-art），包括空间推理、体现化语义对齐（embodied grounding）、体现化问答（embodied QA）以及任务规划（task planning）。此外，我们系统性地研究了不同的 VLM 初始化方式如何影响监督式的 VLA 微调过程，并据此提出了缓解网络规模预训练数据与体现化策略学习数据之间领域偏移（domain shift）的新见解。

#### 设备

在基准测试中，Vlaser 在 WidowX 机器人上进行了评估 (WidowX benchmark)。
也在 “Google Robot” 基准 (Google Robot benchmark) 上进行了测试。
论文中使用的是离线 /模拟策略 (policy)，并不一定说明真实物理硬件训练时使用了具体型号的 “机械臂品牌 +型号” 来收集训练数据 (至少在公开论文里没有详列真实机器人硬件进行大规模训练的细节)。
使用 Vlaser-6M 数据集

### 6.Evo‑1

代码仓库：[GitHub - EO-Robotics/EO1: EO: Open-source Unified Embodied Foundation Model Series](https://github.com/EO-Robotics/EO1?utm_source=chatgpt.com)
论文：[EO-1: Interleaved Vision-Text-Action Pretraining for General Robot Control](https://arxiv.org/html/2508.21112v3?utm_source=chatgpt.com)

#### 简介

EO‑1 是由 联合 等单位推出的开源“统一化具身基础模型”（embodied foundation model），

人类在开放世界中无缝执行多模态推理和物理互动的能力是通用具身智能系统的核心目标。近期的视觉-语言-动作（VLA）模型，通过在大规模机器人和视觉-文本数据上共同训练，已在通用机器人控制方面取得了显著进展。然而，这些模型仍未能在交替推理和互动方面达到人类级别的灵活性。本文介绍了EO-Robotics，包含EO-1模型和EO-Data1.5M数据集。EO-1是一个统一的具身基础模型，通过交替的视觉-文本-动作预训练，在多模态具身推理和机器人控制中取得了卓越的表现。EO-1的发展基于两个关键支柱：（i）一个统一的架构，能够不加区分地处理多模态输入（图像、文本、视频和动作）；（ii）一个庞大且高质量的多模态具身推理数据集EO-Data1.5M，其中包含超过150万条样本，重点关注交替的视觉-文本-动作理解。EO-1通过自动回归解码和流匹配去噪的协同作用，在EO-Data1.5M数据集上进行训练，从而实现无缝的机器人动作生成和多模态具身推理。大量实验验证了交替视觉-文本-动作学习在开放世界理解和泛化中的有效性，并通过多种具身平台上的长时程、精细操作任务得到了验证。旨在让机器人系统能够像人类一样，实现视觉、语言、动作三模态（vision‑text‑action）之间的无缝交互。这一模型采用约 3 B 参数 的解码器‑仅（decoder‑only）Transformer 架构，训练数据主要来自一个自建叉视觉‑文本‑动作”数据集 （包含超过1.5百万条样本）以及网络多模态（image/video/text）数据和真实机器人控制数据。在数据上，EO‑Data1.5M 聚合了 “物理常识理解”、 “空间／任务规划问答”、 “跨模态（视觉‑语言‑动作）” 操作序列等多种类型，通过将图像帧、语言说明／问答、机器人状态／动作序列交错（interleaved）组合，使模型能够同时学习“看–思–做”流程。

在架构与训练机制上，EO‑1 模型采用一个统一的 Transformer 作为主干，其输入包括图像（或视频帧）、语言指令、机器人状态、动作指令；输出既可能是自然语言，也可能是机器人动作命令。训练上使用两种关键机制：一是 自动回归解码（autoregressive decoding） 用于语言／文本输出；二是 流匹配（flow‑matching）去噪机制 用于连续机器人动作输出。模型在整序列上采用因果注意力（usal attention），处理视觉‑语言‑动作的时间性和因果关系。

#### 设备

训练建议使用 “flash‑attn 3 from source with H100 / H800 GPU, CUDA 12.8 for best performance”。
模型可在“仅约 6 GB GPU 内存”上做推理
机器人平台品牌／型号：Widow X（桌面机器人）、Franka Panda（工业机器人臂）、AgiBot G‑1（双臂人形机器人）

### 7.CogACT

代码仓库：<https://github.com/microsoft/CogACT?utm_source=chatgpt.com>
论文：<https://arxiv.org/abs/2411.19650?utm_source=chatgpt.com>
预训练模型：<https://huggingface.co/CogACT/CogACT-Base?utm_source=chatgpt.com>
项目主页：<https://cogact.github.io/?utm_source=chatgpt.com>

#### 简介

CogACT 是一个先进的视觉-语言-动作（VLA, Vision-Language-Action）模型，其设计目标是将强大的视觉语言模型（VLM）与专门的动作模块结合，以用于机器人操作（manipulation）任务。与以前简单通过量化将 VLM 用于动作预测的方法不同，CogACT 采用组件化结构：视觉模块、语言模块和动作模块彼此分离但协同工作。视觉模块使用 DINOv2 (ViT-L/14) 和 SigLIP (ViT-So400M/14) 提取视觉特征；语言模块基于Llama-2，负责语言理解与认知推理；动作模块则采用 Diffusion Transformer (DiT) 来建模时间相关的连续动作序列。CogACT 在 Open X-Embodiment (OXE) 数据集上预训练了约 0.4 百万 (0.4M) 轨迹，并在训练中支持扩展。推理时采用一种 Adaptive Action Ensemble (AAE) 策略，通过对多个预测动作序列进行加权集成来提高稳定性和准确性。

在模拟和真实机器人上都进行了广泛评估：在 SIMPLER 模拟环境中（包括 Google robot 和 WidowX 机器人设置）表现显著优于先前的 VLA 模型；在真实世界中，也使用 Realman 机械臂（7-DoF, 带 1-DoF gripper）以及 Franka 机械臂完成多个任务（如抓取、堆放、放置），表现出对新物体、新背景和未见任务的强泛化能力。与 OpenVLA（7B 参数）相比，其在模拟中成功率提升约35%，在真实机器人实验中提升约55%；与更大的 RT-2-X（55B 参数）相比，在仿真中绝对成功率也高出约18%。

#### 设备

训练硬件：16 × NVIDIA A100 GPU。
推理硬件：单块 NVIDIA A6000 GPU（使用 bfloat16 ）。
机器人臂 / 机器人平台：Realman 机械臂：7 DoF + 1-DoF gripper。Franka 机械臂 (Franka robot) 用于真实世界测试。
模拟环境：Google robot 和 WidowX robot（在 SIMPLER 模拟平台中）。

### 8.Octo

GitHub: <https://github.com/octo-models/octo>
官方网站: <https://octo-models.github.io/>

#### 简介

Octo是一个基于Transformer架构的扩散策略（diffusion policy）通用机器人模型，由伯克利RAIL实验室开发。该模型在开放具身体验（Open X-Embodiment）数据集的800,000条机器人轨迹数据上进行了预训练。Octo提供两个版本：Octo-Small（2,700万参数）和Octo-Base（9,300万参数）。模型设计强调灵活性和可扩展性，支持多种常见机器人、传感器配置和动作空间。Octo同时支持自然语言指令和目标图像条件化，支持观测历史和通过扩散解码的多模态动作分布。预训练数据来自25个不同数据集的混合，涵盖多种机器人类型、场景和任务。在零样本评估中，Octo在WidowX任务上达到0.50成功率，在UR5任务上达到0.70成功率，在RT-1机器人上达到0.80成功率，性能与RT-2-X（550亿参数模型）相当。在微调评估中，Octo在六个评估任务上平均超过次优基线52%的性能提升，每个任务仅需约100条演示数据即可完成微调。该模型支持高效的微调功能，可适应不同动作空间、新观测类型（如力-扭矩信息）和新机器人形态。评估涵盖多种机器人设置：WidowX BridgeV2（长任务地平线）、Stanford Coffee（复杂任务）、Berkeley Peg Insert（精密操作，新增力-扭矩输入）、Berkeley Pick-Up（新的关节位置控制动作空间）、Berkeley Bi-Manual（双臂机器人）和Berkeley Coke（新型机器人形态）。

#### 设备

推理硬件: 支持NVIDIA 4090等单GPU推理
机器人硬件: WidowX机械臂、UR5工业机械臂、RT-1/RT-2机器人系统、Berkeley双臂机器人系统

------

## VLM类

### 1.LLaVA-NeXT

链接：[github.com/LLaVA-VL/LLaVA-NeXT](https://github.com/LLaVA-VL/LLaVA-NeXT)
模型文档：<https://huggingface.co/docs/transformers/v4.50.0/en/model_doc/llava_next>

#### 简介

LLaVA‑NeXT 是由 LLaVA 团队于 2024 年左右公开推出的一款大型多模态（视觉＋语言）模型框架。它与LLaVA-1.5 相比，将输入图像分辨率提高到 4 倍的像素数。这使得它能够捕捉更多的视觉细节。它支持三种宽高比，最高可达 672x672、336x1344、1344x336 分辨率。通过改进的视觉指令调优数据混合，实现了更好的视觉推理和 OCR 能力。支持更多场景的视觉对话，涵盖不同的应用。具备更好的世界知识和逻辑推理能力。使用 SGLang 实现高效的部署和推理。除了性能提升外，LLaVA-NeXT 仍保持了 LLaVA-1.5 的极简设计和数据效率。它重用了 LLaVA-1.5 的预训练连接器，并且仍然使用少于 100 万个视觉指令调优样本。最大的 34B 版本使用 32 个 A100 在约 1 天内完成训练。

#### 设备

显卡：训练使用的是 NVIDIA A100 GPU（80 GB 版本）集群。
机器人臂／物理设备：在公开资料中，我未能查到该项目明确使用了 “机器人臂” 或物理 robot arm 硬件。

### ２.Qwen-VL

代码仓库：[github.com/QwenLM/Qwen-VL?utm_source=chatgpt.com](https://github.com/QwenLM/Qwen-VL?utm_source=chatgpt.com)
论文：[[2308.12966\] Qwen-VL: 一种用于理解、定位、文本阅读及更广泛领域的通用视觉语言模型 --- [2308.12966] Qwen-VL: A Versatile Vision-Language Model for Understanding, Localization, Text Reading, and Beyond](https://arxiv.org/abs/2308.12966?utm_source=chatgpt.com)

#### 简介

Qwen‑VL 是由 （阿里云）开发、基于其大语言模型系列 “通义千问（Qwen）” 拓展出来的视觉‑语言模型（Vision‑Language Model, VLM）系列。该系列模型可同时处理图像、文本、检测框（bounding box）作为输入，并输出文本及检测框结果，具备多模态理解、视觉定位、文字识别、对话能力等功能。其训练采用三阶段流程：首先视觉编码器预训练、然后联合视觉‑语言联合训练、最后做任务微调。模型支持中英双语及多语言，能够理解图像中的细粒度内容（如图片中的文字、场景物体、图表、文档）并进行描述、问答、定位与对话交互。开源版本提供预训练模型及聊天对话模型（Qwen‑VL 和 Qwen‑VL‑Chat），用户可通过 GitHub 或 Hugging Face 获取。该系列在诸多视觉‑语言基准任务（如 captioning、VQA、文档 VQA、视觉 grounding）上实现了领先水平，显著超越此前开源同类模型。

以 Qwen-LM 为基础，通过精心设计的（i）视觉接收器，（ii）输入输出接口，（iii）三阶段训练流程，以及（iv）多语言多模态清洗语料库，赋予其视觉能力。除了传统的图像描述和问答功能外，通过对齐图像-标题-框三元组，实现了 Qwen-VL 的接地和文本阅读能力。这些模型，包括 Qwen-VL 和 Qwen-VL-Chat，在一系列以视觉为中心的基准测试（例如，图像描述、问答、视觉接地）和不同设置（例如，零样本、少样本）中，以相似模型规模创造了通用模型的记录。此外，真实世界对话基准测试中，指令微调 Qwen-VL-Chat 也显示出优于现有视觉语言聊天机器人的性能。代码、演示和模型可在该 https URL 获取。

#### 设备

模型运行推理（inference）推荐使用 CUDA 11.4 及以上版本。
关于模型运行（而非训练）所需显存／VRAM，有资料指出例如   Qwen‑2.5‑VL 系列在部署时，72B 参数版本推荐使用 80 GB 显存以上。

### 3.InternVL

代码仓库：<https://github.com/OpenGVLab/InternVL?utm_source=chatgpt.com>
论文:<https://openaccess.thecvf.com/content/CVPR2024/papers/Chen_InternVL_Scaling_up_Vision_Foundation_Models_and_Aligning_for_Generic_CVPR_2024_paper.pdf?utm_source=chatgpt.com>
官方网站 /项目主页：<https://internvl.github.io/?utm_source=chatgpt.com>
最新 InternVL3.5 (开放源代码) 技术报告 (arXiv)：https://arxiv.org/abs/2508.18265?utm_source=chatgpt.com

#### 简介

InternVL 是由 OpenGVLab 等单位提出的一系列开源视觉–语言基础模型 (vision–language foundation models)，其关键创新在于将视觉编码器大幅扩展到 约 6 十亿参数 (InternViT-6B)，并通过渐进 (progressive) 对齐策略与语言模型 (LLM) 协同训练，以支持多种通用视觉语言任务。InternVL 的训练流程分三个阶段：首先使用 web-scale 噪声图文 (image-text) 对进行对比学习 (contrastive learning)，对齐视觉与语言表示；然后进行生成 (generative) 训练，通过 QLLaMA（中间层 LLM）和可学习查询 (cross-attention) 层进一步对齐；最后是监督微调 (supervised fine-tuning)，使用高质量指令数据 (~ 400 万样本) 构建多模态对话。InternVL 在 32 个通用视觉-语言基准 (包括图像分类、图像/视频—文本检索、VQA、多模态对话等) 上取得强劲表现。根据官方资料，其 web-scale 图文训练数据包含 6.03 十亿原始对，清洗后约 4.98 十亿。

开源方面，InternVL 发布了 GitHub 代码 (OpenGVLab/InternVL)，同样提供不同规模 (从 1 B 到几十 B) 的模型，例如 InternVL2.5、Mini-InternVL 等。官网还介绍了 Mini-InternVL (1B–4B 参数) 系列可在较低资源 (edge / consumer GPU) 上部署，其参数仅为原模型 5% 但能保留近 90% 性能。 最新版本 (如 InternVL2.5) 已覆盖 1B–78B 参数模型，InternVL2.5-78B 在 MMMU 基准上达到了 超过 70%，与部分闭源商用模型接近。

#### 设备

训练硬件：根据 InternVL 的补充材料 (CVPR supplementary)，在 Stage 1 使用了 640 × NVIDIA A100 GPU 进行训练，训练迭代约 175K 步，总计处理约 28.7 十亿 (billion) 图像-文本样本。
训练超参数 (部分)：使用 AdamW 优化器 (β1=0.9, β2=0.95)，cosine 学习率调度，第 1 阶段学习率分别为 1e-3 和 1e-4 (视觉 / 语言)；drop path rate = 0.2。
精度 &计算：第一次训练阶段使用 bf16 (bfloat16)。根据补充材料，还使用 PyTorch + FlashAttention。
训练阶段二 (视觉-语言生成训练)：固定视觉编码器与 QLLaMA，仅训练 cross-attention + learnable queries；使用 160 A100 GPU (160 × A100)，batch size = 20K，共训练 80K 步。
推理 /部署：GitHub 发布说明 (Reproduce InternVL-Chat V1.2) 中指出 Fine-tune (聊天模型) 使用 32 或 64 GPU。例如若使用 64 GPU，则训练大约需要 18 小时。
精度 /输入分辨率：InternVL 支持 “动态高分辨率 (Dynamic High-Resolution)” 输入 —— 将图像切分成多个 448×448 的瓦片 (tiles)，根据输入图像比例动态决定块数 (1–40 块)，支持高达 4K 分辨率。
视觉 token 压缩：在某种版本中 (如 InternVL 1.x)，使用 pixel-unshuffle (即 space2depth) 来减少视觉 token 数目 (原始视觉 token 数可达 1024，然后压缩为四分之一) 以提升效率。

### 4.CogVLM

代码仓库：<https://github.com/zai-org/CogVLM?utm_source=chatgpt.com>
论文：<https://arxiv.org/abs/2311.03079?utm_source=chatgpt.com>

#### 简介

CogVLM 是由清华 KEG（Knowledge Engineering Group）与智谱 AI (ZhipuAI) 联合开发的开源视觉-语言基础模型 (VLM)，其核心创新在于引入 视觉专家模块 (visual expert module)，将图像特征深度融合进大型语言模型 (LLM) 的注意力 (attention) 层和前馈网络 (FFN) 层，以实现对视觉-语言特征的深度融合，而不损失原语言模型在 NLP 任务上的性能。CogVLM-17B（17 B规模）版本包含约 100 亿 (10B) 视觉参数 和 70 亿 (7B) 语言参数（具体为 10B 视觉 + 7B 语言）。在多个视觉-语言基准测试 (10 项经典跨模态 benchmark) 中表现出色，包括 NoCaps、Flickr30k Captioning、RefCOCO / RefCOCO+ / RefCOCOg、Visual7W、GQA、ScienceQA、VizWiz VQA、TDIUC 等 。此外，在 VQAv2、OKVQA、TextVQA、COCO captioning 等任务中也取得非常强的排名 (例如第二名)，其性能已与 PaLI-X (55B) 相当或优于部分任务。模型公开在 GitHub (Apache-2.0 许可证)，并提供若干预训练 checkpoint (如 chat、grounding/generalist 版本)，支持量化 (4-bit) 推理，在较常见硬件 (例如单张 RTX 3090) 上也可运行。

#### 设备

使用 INT4 (4-bit) 量化 时，只需 1 × RTX 3090 (24GB) 即可运行 CogVLM。
使用 FP16 模式时，建议 1 × A100 (80GB)，或 2 × RTX 3090 (24GB)。
模型架构：根据论文 (Wisdom model PDF)：CogVLM 17B 使用 EVA2-CLIP-E 作为视觉编码器 (ViT)，语言模型采用 Vicuna-7B-v1.5。视觉专家模块 (visual expert) 插入 LLM 每层的 attention 和 FFN：在每层 attention 模块中有一个可训练的 QKV 矩阵 (与 LLM 相同形状)，在 FFN 层有对应的 MLP。

------

## VLN类

### １.Habitat 3.0

主页：[aihabitat.org/habitat3/](https://aihabitat.org/habitat3/)
官方论文：[[2310.13724\] Habitat 3.0: A Co-Habitat for Humans, Avatars and Robots](https://arxiv.org/abs/2310.13724)
代码仓库：[github.com/facebookresearch/habitat-lab](https://github.com/facebookresearch/habitat-lab)

#### 简介

我们提出 Habitat 3.0：一个用于研究家庭环境中人机协作任务的仿真平台。Habitat 3.0 在三个维度上做出了贡献：（1）精确的人形仿真：解决复杂可变形体建模、外观和运动多样性的挑战，同时保证高仿真速度。（2）人在环基础设施：支持真实人类通过鼠标/键盘或 VR 接口与模拟机器人交互，便于在人类参与的情况下评估机器人策略。（3）协作任务：研究两项协作任务——社交导航和社交重排。社交导航研究机器人在未知环境中定位和跟随人形化身的能力，而社交重排则涉及人形化身与机器人在场景重排过程中的协作。这些贡献使我们能够深入研究人机协作的端到端学习和启发式基线方法，并通过人在环评估进行验证。我们的实验表明，当与未见过的人形代理和可能表现出机器人未曾见过行为的人类伙伴协作时，学习得到的机器人策略能够高效地完成任务。此外，我们观察到协作任务执行过程中出现的涌现行为，例如当机器人阻挡人形代理时会主动让出空间，从而使人形代理能够有效完成任务。此外，我们使用人在环工具进行的实验表明，使用人形化身进行的自动化评估可以预示不同策略与真实人类协作者进行评估时的相对排序。Habitat 3.0 为具身智能仿真器解锁了有趣的新功能，我们希望它能为具身人机交互能力的新前沿铺平道路。

#### 设备

显卡：适配于NVIDIA GPU设备

### ２.VLN-CE

主页：[VLN-CE](https://jacobkrantz.github.io/vlnce/)
论文：[[2004.02857\] 超越导航图：连续环境中的视觉语言导航 --- [2004.02857] Beyond the Nav-Graph: Vision-and-Language Navigation in Continuous Environments](https://arxiv.org/abs/2004.02857?utm_source=chatgpt.com)
代码仓库：[GitHub - jacobkrantz/VLN-CE: Vision-and-Language Navigation in Continuous Environments using Habitat](https://github.com/jacobkrantz/VLN-CE)

#### 简介

一个语言引导的导航任务集，该任务集设置在一个连续的 3D 环境中，其中智能体必须执行低级动作来遵循自然语言的导航指令。由于置身于连续环境中，这一设置消除了先前工作中将环境表示为稀疏的视景图（panoramas）的图模型所隐含的若干假设，其中边对应于可通行性。具体而言，我们的设置摒弃了已知环境拓扑结构、短程预言导航和完美智能体定位的假设。为了使这一新任务更具背景，我们开发了能够反映先前设置中的许多进展以及单模态基线的模型。尽管其中一些技术可以迁移，但我们发现在连续设置中的绝对性能显著较低——这表明先前`导航图'设置中的性能可能因强烈的隐含假设而被夸大。

#### 设备

该模型最初以 0.30 SPL 的 val_unseen 性能被提出，但排行榜将其同一模型评估为 0.27 SPL。该模型在硬件+Habitat 构建上进行训练和评估，结果略有不同，其他论文实验也是如此。
如果可用，Cuda 将默认使用。模拟器和 torch 代码无需在同一个设备上运行。为了更快地训练和评估，建议在 GPU 上运行尽可能多的 NUM_ENVIRONMENTS ，同时假设每个环境使用 1 个 CPU 核心。
在 “Waypoint Models for Instruction‑guided Navigation in Continuous Environments” (ICCV 2021) 中提到，“训练使用了 DDPPO 方式、64 GPU”配合 config 文件。
其他硬件具体信息没有提及

### ３.SOON

代码仓库：[github.com/ZhuFengdaaa/SOON](https://github.com/ZhuFengdaaa/SOON)

#### 简介

SOON（Scenario Oriented Object Navigation）提出了一种更贴近现实的语言引导导航任务：智能体从任意位置进入三维室内环境中，仅依据对目标对象场景的自然语言描述（包括对象属性、对象关系、所属区域、附近区域等语义信息），自主导航并定位目标，而不是从固定起点或按步骤指令出发。该任务旨在缩小传统语言‑视觉导航（VLN）中“从已知起点+精确路径指令”与现实中“从未知起点+大致描述目标”之间的差距。为此，SOON 还构建了一个名为 From Anywhere to Object (FAO) 的大规模基准数据集，专为该任务设计，并提出了一种图结构探索策略（Graph‑Based Exploration，GBE）——将导航状态建模为图，学习探索模块以稳定训练与增强策略学习。实验表明，在 FAO 及经典 R2R 数据集上，GBE 方法优于多项先前算法。

#### 设备

需要 python3.6（因为移除了 allennlp 依赖，所以 python 3.5 应该也可以）
未提及GPU 型号、机器人臂品牌或型号

### 4.Dynam3D

代码仓库：<https://github.com/microsoft/CogACT?utm_source=chatgpt.com>
项目主页：<https://cogact.github.io/?utm_source=chatgpt.com>
预训练模型：<https://huggingface.co/CogACT/CogACT-Base?utm_source=chatgpt.com>
论文：<https://arxiv.org/abs/2411.19650?utm_source=chatgpt.com>

#### 简介

CogACT 是一个先进的视觉-语言-动作（VLA, Vision-Language-Action）模型，其设计目标是将强大的视觉语言模型（VLM）与专门的动作模块结合，以用于机器人操作（manipulation）任务。与以前简单通过量化将 VLM 用于动作预测的方法不同，CogACT 采用组件化结构：视觉模块、语言模块和动作模块彼此分离但协同工作。视觉模块使用 DINOv2 (ViT-L/14) 和 SigLIP (ViT-So400M/14) 提取视觉特征；语言模块基于Llama-2，负责语言理解与认知推理；动作模块则采用 Diffusion Transformer (DiT) 来建模时间相关的连续动作序列。CogACT 在 Open X-Embodiment (OXE) 数据集上预训练了约0.4M 轨迹，并在训练中支持扩展。推理时采用一种 Adaptive Action Ensemble (AAE) 策略，通过对多个预测动作序列进行加权集成来提高稳定性和准确性。

在模拟和真实机器人上都进行了广泛评估：在 SIMPLER 模拟环境中（包括 Google robot 和 WidowX 机器人设置）表现显著优于先前的 VLA 模型；在真实世界中，也使用 Realman 机械臂（7-DoF, 带 1-DoF gripper）以及 Franka 机械臂完成多个任务（如抓取、堆放、放置），表现出对新物体、新背景和未见任务的强泛化能力。与 OpenVLA（7B 参数）相比，其在模拟中成功率提升约35%，在真实机器人实验中提升约55%；与更大的 RT-2-X（55B 参数）相比，在仿真中绝对成功率也高出约18%。

#### 设备

根据官方论文，他们使用 16 块 NVIDIA A100 GPU 进行训练，采用 PyTorch 的 Fully Sharded Data Parallel (FSDP)，总训练时间约为 5 天。训练批量为 256，每样本 diffusion 步数为 8。学习率设置为 ，训练约 135,000 次迭代。模型默认使用 DiT-Base 作为动作模块。

在推理阶段，他们使用 单块 NVIDIA A6000 GPU（bfloat16 模式）运行 CogACT-Base，并且在 100 次连续推理中，平均每次大约 181 ms，约 5.5 Hz 的动作生成频率。使用 adaptive action ensemble 后，如果进行 action chunking（一次输出多步动作，最多 16 步），频率可提升，但随着 k 增大，精度会有下降。

CogACT 支持零样本（zero-shot）控制训练中见过的机器人（即与预训练数据中相同构型）。但也支持在新的机器人或任务上用少量示范（几百条轨迹）微调（fine-tune）；微调时建议采用全量 fine-tuning 而不是 LoRA，因为他们经验上全量 fine-tune 在较短时间内可达到更好效果。

### 5.COSMO

论文：<https://arxiv.org/abs/2503.24065?utm_source=chatgpt.com>
代码仓库：<https://github.com/hms-dbmi/COSMO?utm_source=chatgpt.com>

#### 简介

COSMO 是一个为视觉-语言导航 (VLN) 任务设计的高效模型，其目标是在不牺牲导航性能的前提下，显著降低计算成本。作者提出了一个混合架构，将 状态-空间模型 (state-space modules) 和 Transformer 模块 结合起来，并专为 VLN 设计了两种选择性状态空间模块：（1Round Selective Scan (RSS)，用于一次扫描中高效捕捉视觉观察之间的空间交互；（2Cross-modal Selective State Space Module (CS3)，采用双流设计来加强视觉 (vision) 和语言 (language) 之间的跨模态交互。通过“选择性记忆 (selective memorization)”，COSMO 能够过滤掉与导航指令无关的视觉信息，仅保留关键观察，从而减少不必要的计算。作者在三个主流 VLN 基准 (REVERIE、R2R、R2R-CE) 上进行了大规模实验证明：COSMO 的导航性能非常具有竞争力，同时计算成本显著降低。

具体数据上，在REVERIE 验证 unseen 集，COSMO 的 SR（成功率）和 SPL（路径效率）相比 DUET baseline 提升显著；同时其模型参数量约为 DUET 的 15.5%FLOPs 约为 DUET 的 9.3%，非常节省算力。该方法为资源受限环境 (如边缘设备、低功耗机器人) 上部署 VLN 提供了可行路径。

#### 设备

Python 3.10+
CUDA 11.8+ (for GPU support)
16GB+ GPU memory (recommended)

### 6.BERT-based

代码仓库: <https://github.com/google-research/bert>
论文链接: <https://arxiv.org/abs/1810.04805>

#### 简介

BERT是谷歌于2018年发布的自然语言处理预训练模型，实现了双向编码变换器（Bidirectional Encoder Representations from Transformers）。该模型使用无监督学习方法在纯文本语料库上进行预训练，采用掩码语言模型（Masked Language Model）和下一句预测（Next Sentence Prediction）两个任务。BERT-Base模型配置为12层、768隐层维度、12个注意头，共1.1亿参数；BERT-Large模型配置为24层、1024隐层维度、16个注意头，共3.4亿参数。模型在SQuAD、MultiNLI、MRPC等多项基准测试中达到了当时的最先进性能。提供英文、中文、多语言等多种预训练版本，支持大小写和未大小写两种模式。BERT在文本分类、问答系统、命名实体识别、语义相似度等下游任务中均表现出强大的迁移学习能力。

#### 设备

16GB是微调BERT-Large的最低GPU显存需求
12GB可以微调BERT-Base
预训练需要TPU或多GPU集群

### 7.ViLBERT

GitHub (Facebook官方多任务版本):[ https://github.com/facebookresearch/vilbert-multi-task](https://github.com/facebookresearch/vilbert-multi-task)
GitHub (原始beta版本): <https://github.com/jiasenlu/vilbert_beta>
论文链接: <https://arxiv.org/abs/1908.02265>

#### 简介

ViLBERT（Vision-and-Language BERT）是Facebook Research开发的视觉-语言联合预训练模型，出现在2019年。模型采用双流架构，使用分离的Transformer编码器分别处理视觉和文本信息，通过co-attention机制进行跨模态交互。ViLBERT在Conceptual Captions数据集上进行预训练，支持多种视觉-语言任务，包括图像文本检索、VQA（视觉问答）、VCR（视觉常识推理）和RefCOCO+指代表达理解。模型采用6层或12层Transformer堆叠，支持多任务学习框架（12-in-1多任务学习）。该模型在数据集RefCOCO+（包含19,992张图像、49,856个目标对象、141,565条指代表达）上进行了评估和微调。ViLBERT采用预提取的bottom-up Faster R-CNN特征进行视觉编码，提供了完整的数据处理和模型训练代码。

#### 设备

官方未说明，不过GPU显存要求(≥12GB)来自用户GitHub Issue反馈

### 8.LANA

GitHub: <https://github.com/wxh1996/LANA-VLN>

#### 简介

LANA（Language-capable Navigation Agent）是一个在CVPR 2023发表的视觉-语言导航模型，由多个研究机构合作开发。LANA是一个能够同时执行指令跟随和路线描述生成的导航智能体，通过共享的编码-解码架构进行端到端的多任务学习。模型包含两个编码器（用于路线和语言编码）和两个解码器（分别用于动作预测和指令生成），在Matterport3D模拟环境中进行测试，使用CLIP-ViT-B-16视觉特征。LANA在指令跟随和路线描述两项任务上都超越了近期的任务特定解决方案，同时模型复杂度仅为它们的一半。该模型在R2R（Room-to-Room）导航数据集上进行了评估，可以让机器人代理解释其行为并帮助人类实现寻路。

#### 设备

Python版本3.8
模拟器Matterport3D Simulator v0.1J
视觉特征CLIP-ViT-B-16

### 9.Recurrent VLN Agent

GitHub: <https://github.com/YicongHong/Recurrent-VLN-BERT>

#### 简介

Recurrent VLN Agent是指2021年CVPR会议上发表的"VLN⤴BERT: A Recurrent Vision-and-Language BERT for Navigation"模型，由澳大利亚国立大学和南澳大学的研究人员开发。该模型通过在标准BERT架构中集成递归单元来应对视觉-语言导航（VLN）中的部分可观察马尔可夫决策过程（POMDP）。递归函数维护代理的跨模态状态信息，使模型能够进行历史感知的注意力和决策。该模型使用时间感知的BERT架构，支持基于OSCAR或PREVALENT预训练模型的初始化。在R2R和REVERIE数据集上的实验表明，该模型能够同时解决导航和指称表达任务。在R2R测试集上，该模型达到57%的加权路径长度成功率（SPL），在REVERIE远程指称任务中获得23.99%导航SPL和13.51%远程接地SPL。该递归结构能够有效地处理长序列导航任务中的历史信息压缩问题，相比单层编码器-解码器架构实现了显著的性能改进。

#### 设备

框架PyTorch
模拟器Matterport3D Simulator v0.1
模拟器升级支持v1.0
多GPU评估支持
预训练权重2.5GB

‍