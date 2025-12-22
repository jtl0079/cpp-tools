
# cpp-tools/../math 文件夹架构介绍

```asgl
│       │   ├── math/
│       │   │   ├── api/
│       │   │   │   └── ops.h
│       │   │   ├── backend/
│       │   │   │   ├── serial/
│       │   │   │   │   └── logic.h
│       │   │   │   ├── openmp/
│       │   │   │   │   └── logic.h
│       │   │   │   └── cuda/
│       │   │   │       ├── linear/
│       │   │   │       ├── vector/
│       │   │   │       ├── matrix/
│       │   │   │       ├── statistics/
│       │   │   │       └── signal/
│       │   │   ├── benchmark/
│       │   │   │   ├── serial/
│       │   │   │   ├── openmp/
│       │   │   │   ├── cuda/
│       │   │   │   └── allversion/
│       │   │   │       └── linear/
│       │   │   ├── tuning/
│       │   │   └── dispatch
│       │   │       └── selected.h

```