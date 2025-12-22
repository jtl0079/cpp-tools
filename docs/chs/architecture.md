

# cpp-tools 文件夹架构介绍
```asgl
project/                                    # 顶层仓库根目录
├── README.md                               # 项目说明（如何构建、如何贡献、模块说明） # 必备
├── LICENSE                                 # 许可证文件（MIT/Apache 等）                   # 必备
├── CMakeLists.txt                          # 顶层 CMake：定义项目名、option、子目录、安装规则
├── cmake/                                  # CMake 自定义模块（FindXXX.cmake, toolchain 等）  # 推荐：便于复用
│   ├── dependencies/
│   └── Modules/                            # project 专用的 cmake 小模块
├── docs/                                   # 项目文档（架构、设计决策、接口规范、贡献指南等） # 推荐
│   ├── chs/
│   └── eng/
├── third_party/                            # 第三方库 / 子模块 / vendor（可选：或用 submodule）
├── msvc/                      # ⭐ Visual Studio / MSBuild
│   ├── cpptools.props         # 总入口
│   ├── modules/
│   │   ├── sdl2.props
│   │   ├── openmp.props
│   │   └── vulkan.props
│   └── README.md
├── include/                                # 对外统一头文件入口（公开 API）                   # 保持对外稳定 ABI
│   └── cpptools/                           # 把所有对外头按照项目/命名空间组织，避免全局冲突
│       ├── core/
│       │   └── traits/
│       ├── framework/
│       │   ├── m1/
│       │   └── math/
│       │       ├── api/
│       │       ├── backend/
│       │       ├── benchmark/
│       │       ├── tuning/
│       │       └── dispatch/
│       │
│       └── modules/
│           ├── m1/
│           └── math/
│               ├── domain/
│               │   ├── model/               # 实体定义（struct/class，尽量 POD 或小方法）  # 领域模型
│               │   ├── mapper/              # DTO <-> Domain 转换声明                         # 解耦边界
│               │   └── service/             # 领域服务接口声明（不依赖 infra）               # 纯契约
│               ├── interface/               # repository / api 接口声明（契约层）            # 明确为契约
│               └── presentation/            # view model / serializer 的对外声明             # 展示层契约
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