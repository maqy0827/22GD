# 诗云

本项目是来自哈工大威海校区某弱鸡的毕业设计，题目为`基于迈克尔逊干涉仪的位移测量系统`。如希望了解该毕设可以参考[迈克尔逊干涉仪调节实验](https://www.bilibili.com/video/BV1gW411y7Xq)。

# 详细介绍

如果你想看最详细的介绍，我推荐直接看[毕业设计论文](/Book/Thesis/Thesis.pdf)。在写论文的过程中拍摄了实验现象的视频，如有需要可以联系我(邮箱15876781@qq.com，应该不会有吧hhhh)

## 硬件与软件

如果你想复现此项目，你需要准备如下硬件与软件

> 软件
>
> - 绘制电路板使用`Altium Designer 22`
> - 程序设计使用`Keil_v5 (MDK536)`
> - 毕业论文书写~~Texlive2021~~`Word`
> - 推荐使用`VScode`阅读本项目

> 硬件（实物
>
> - 搭建迈克尔逊干涉仪所需的全部光学组件
>> - He-Ne 激光器一个（或其他激光器，但不要使用半导体激光器
>> - 扩束镜一个（或凸透镜 / 凹透镜等可以扩束的光学仪器）
>> - 50/50 分光棱镜（分光片也行但不推荐）
>> - 反光镜两个（均配合二维调整架使用）
>> - 最好有一个光学平台
> - 电路部分所需概要（详情查看原理图 / BOM 表
>> - STM32F103CxT6 最小系统板一块
>> - 12864 OLED 0.96寸 IIC通信 显示屏一块
>> - USB 转串口一个
>> - 电路板所需的其他元器件（包括运放，阻容，光电传感器

## 文件夹

- `.vscode` VScode 配置文件
- `Book` 中期报告与论文
  - `Image` README 与实验记录图片/视频
  - `Midterm` 中期报告
  - `Open` 开题报告
  - `Thesis` 毕业论文与数据处理
- `PCB` 电路板与原理图
  - `Libraries` 原理图库和元件库
  - `22GD` 毕设使用电路板
  - `Test1` 首次测试使用电路板
- `Project` 单片机程序
  - `MDK` **MDK工程入口**
  - 其余文件夹均为程序库

# 感谢

> 感谢以下项目作者
>
> - [dustincys/hithesis: 嗨！thesis！哈尔滨工业大学毕业论文LaTeX模板 (github.com)](https://github.com/dustincys/hithesis)
