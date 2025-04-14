# 项目介绍
<font style="color:rgb(64, 64, 64);">本系统采用QT框架开发跨平台音乐播放器，集成QMediaPlayer实现音频解码与播放控制，结合QPropertyAnimation打造流畅的交互体验。系统支持主流音频格式播放，具备完善的播放控制功能和可视化的播放列表管理。</font>

## <font style="color:rgb(64, 64, 64);">功能特性矩阵</font>
| **<font style="color:rgb(64, 64, 64);">功能模块</font>** | **<font style="color:rgb(64, 64, 64);">技术实现</font>** |
| --- | --- |
| <font style="color:rgb(64, 64, 64);">核心播放控制</font> | <font style="color:rgb(64, 64, 64);">QMediaPlayer状态机管理 + 自定义播放队列算法</font> |
| <font style="color:rgb(64, 64, 64);">播放模式切换</font> | <font style="color:rgb(64, 64, 64);">枚举策略模式实现(顺序/随机/单曲循环)</font> |
| <font style="color:rgb(64, 64, 64);">音频进度控制</font> | <font style="color:rgb(64, 64, 64);">QSlider双向绑定媒体进度 + 异步位置更新</font> |
| <font style="color:rgb(64, 64, 64);">动态播放列表</font> | <font style="color:rgb(64, 64, 64);">QListView自定义Delegate + 滑动动画控制器</font> |
| <font style="color:rgb(64, 64, 64);">可视化过渡动画</font> | <font style="color:rgb(64, 64, 64);">QPropertyAnimation组合动画链(位移+透明度)</font> |


 

# 项目界面
![](https://cdn.nlark.com/yuque/0/2025/png/55420051/1744638397006-b812e51d-93d8-4426-93fd-ee9f8cbed2c6.png)





