```
project/
├── CMakeLists.txt
├── modules/                # ✅ 所有业务模块
│   ├── report/
│   │   ├── include/
│   │   │   ├── domain/report/          # 抽象定义
│   │   │   │   ├── model
│   │   │   │   ├── mapper
│   │   │   │   └── service
│   │   │   ├── interface/       # 对外 API（稳定）
│   │   │   └── presentation/
│   │   ├── src/
│   │   │   ├── domain/          # 实现
│   │   │   ├── application/     # 用例
│   │   │   ├── infrastructure/  # IO 实现
│   │   │   └── presentation/    # UI / API adapter
│   │   ├── test/
│   │   └── CMakeLists.txt
│   ├── m2/
│   └── m3/
│
├── framework/
│   ├── include/framework/
│   ├── src/
│   └── CMakeLists.txt
│
├── platform/
└── interface/

```