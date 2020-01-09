# 数字图像处理课程设计-颜色量化

> *朱广锋*
>
> 2020/1/9
>
> https://github.com/thatboy-zero/Color-Quantization

```cpp
ColorCube::loadImage(源图像);
ColorCube::splitCube();
ColorCube::write8bIndexBmp(目标文件名);
```

目前基本完成算法的设计，并完善了许多细节，在性能上做了一些优化。可以对opencv支持的3/4通道图像进行中位切分。

但是实践中存在一些转换错误。如测试样本中的color3，转换后出现三到四条违和的色条。

![color3](.\颜色量化\测试样本\color3.png)

![color3r](.\颜色量化\测试样本\color3.bmp)