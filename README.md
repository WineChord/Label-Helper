# Label-Helper
图片标注小助手
## 文件说明
* 可执行文件请点击`release`，到`Assets`处进行下载（`release_v3.zip`）。
## 使用流程
* 点击`load index`，选择`index.json`进行加载。
* 点击`load pose`，选择`pose.json`进行加载。
* 点击`load images`，选择需要处理的图片目录`images/`。
* 此时图片可以正常显示，默认显示标记为"o"的图片组。通过点击"o"或者"x"可以进行切换。
* 在文本框中输入数字可以快速跳到指定的图片。
* 标注之前要确保焦点不在文本框处，可以按Tab键解决
* 标注时按键W为前，S为后，A为左，D为右。
* 若要返回上一张，按Q。查看下一张，按E。
* 上述两操作并不区分大小写，直接按键即可。
* 可以通过滑竿来在标注后以不同速度查看图片，显示的数字代表一秒钟翻过的图片数。
## 格式说明
* `index.json`的格式
```
{
    "00001197_00_0000.jpg": "o",
    "00001197_00_0001.jpg": "x",
    ...
}
```
* `pose.json`的格式（输出，1/2/3/4分别代表前/后/左/右）
```
{
   "00000023_02_0000.jpg" : 1,
   "00000023_03_0000.jpg" : 2,
   ...
}
```
## 源代码编译环境及依赖：
* Visual Studio 2017
* Qt5.6.3
* JsonCpp