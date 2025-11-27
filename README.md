
# to user
## cpp-tools 文件夹架构介绍
```
project/                                    # 顶层仓库根目录
├── README.md                               # 项目说明（如何构建、如何贡献、模块说明） # 必备
├── LICENSE                                 # 许可证文件（MIT/Apache 等）                   # 必备
├── CMakeLists.txt                          # 顶层 CMake：定义项目名、option、子目录、安装规则
├── cmake/                                  # CMake 自定义模块（FindXXX.cmake, toolchain 等）  # 推荐：便于复用
│   └── Modules/                            # project 专用的 cmake 小模块
├── docs/                                   # 项目文档（架构、设计决策、接口规范、贡献指南等） # 推荐
│   ├── architecture.md
│   └── development.md
├── third_party/                            # 第三方库 / 子模块 / vendor（可选：或用 submodule） # 管理外部依赖
├── include/                                # 对外统一头文件入口（公开 API）                   # 保持对外稳定 ABI
│   └── cpptools/                           # 把所有对外头按照项目/命名空间组织，避免全局冲突
│       ├── cpptools.h                      # 顶层 umbrella header（仅用于简易引用）           # 可选
│       ├── framework/
│       │   ├── openmp/
│       │   │   ├── openmp.h                # 对外宏/配置/简单 API（不要放实现）              # header-only: 小心 inline
│       │   │   └── TOpenMP.h               # TOpenMP 接口声明（class/struct）               # 保持轻量
│       │   └── utils/
│       │       └── string/
│       │           └── string_utils.h      # 字符串工具声明（trim/split/format）            # 只放接口/inline
│       │
│       └── modules/
│           ├── report/
│           │   ├── domain/
│           │   │   ├── model/               # 实体定义（struct/class，尽量 POD 或小方法）  # 领域模型
│           │   │   ├── mapper/              # DTO <-> Domain 转换声明                         # 解耦边界
│           │   │   └── service/             # 领域服务接口声明（不依赖 infra）               # 纯契约
│           │   ├── interface/               # repository / api 接口声明（契约层）            # 明确为契约
│           │   └── presentation/            # view model / serializer 的对外声明             # 展示层契约
│           ├── m2/
│           └── m3/
├── src/                                    # 实现文件（对应 include 中的接口）               # 源码集中实现
│   ├── core/                               # 公共核心库实现（若有）                          # 可选
│   ├── framework/
│   │   ├── openmp/
│   │   │   └── TOpenMP.cpp                  # TOpenMP 实现（并行策略、调度）                  # 放实现
│   │   └── utils/
│   │       └── string_utils.cpp             # string_utils 实现                              # 实现文件
│   │
│   └── modules/
│       ├── report/
│       │   ├── domain/                      # domain 层实现（模型方法、领域验证）            # 仅领域逻辑
│       │   ├── application/                 # 用例层（use-cases / services）                 # 协调 domain 和 infra
│       │   ├── infrastructure/              # infra 实现（DB / FS / network / adapters）      # 具体适配器
│       │   └── presentation/                # REST/CLI/GUI handler 实现                      # 绑定到外部接口
│       ├── m2/
│       └── m3/
├── tests/                                  # 测试（单元/集成/端到端）                         # 可选 BUILD_TESTS
│   ├── unit/
│   ├── integration/
│   └── mocks/                              # 测试 mocks / fixtures
├── examples/                               # 示例程序 / bindings / CLI 示例                    # 替代原先 ambiguous interface/
│   ├── cli/
│   └── bindings/                           # Python/Node/other language bindings 示例         # 如果需要
├── tools/                                  # 开发或构建辅助工具（脚本、小程序）               # 自动化脚本
│   └── codegen/
├── scripts/                                # 构建/发布/lint/format 脚本（CI 用）              # 推荐集中管理
│   ├── format.sh
│   └── build_release.sh
├── ci/                                     # CI 配置（GitHub Actions / GitLab CI / Jenkins）  # 推荐
│   └── github/
│       └── build-and-test.yml
├── benchmarks/                             # 性能基准测试（benchmark 程序和数据）             # 可选
├── packaging/                              # 打包/发行相关脚本或配置（conan/vcpkg/apt spec）  # 可选
└── platform/                               # 平台相关实现（POSIX/Windows 特殊实现）          # 和 src 分离便于选择性编译
    ├── posix/
    └── win32/

```

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
