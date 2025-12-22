
# to user


## cpp-tools 引用方式（推荐）
### 方式一：传统 sln
1. 在项目(ProjectDir) 创建libs 文件夹并放入 cpptools，
路径为 (ProjectDir)/libs/cpptools
2. 在 property manager 里放入 cpptools.props
3. 便可以在项目里使用
```
// 引入例子
#include <cpptools/framework>

```


# to editor cpp-tools
## 🔄 更新模块

进入主项目根目录执行：（上传子模块）

```bash
git submodule update --remote --merge
```

进入主项目根目录执行：（上传子模块和主模块）：

```bash
git submodule foreach --recursive "git add .; git commit -m 'auto update submodule'; git push"
git add .
git commit -m "update all"
git push
```

