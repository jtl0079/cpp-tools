# ================================
# 更新 openmp 聚合头
# 使用 CMake 重新配置以触发生成
# ================================
# Update module aggregate header
# Trigger CMake reconfigure
# ================================

$Root = Split-Path -Parent $MyInvocation.MyCommand.Path
$Module = Split-Path -Leaf $Root     # 自动获取目录名作为模块名
$BuildDir = "$Root/build"

Write-Host "== Updating aggregate header for module: $Module ==" -ForegroundColor Cyan

if (!(Test-Path $BuildDir)) {
    Write-Host "Build directory not found. Creating..." -ForegroundColor Yellow
    New-Item -ItemType Directory -Path $BuildDir | Out-Null
}

Set-Location $BuildDir

Write-Host "Running CMake configure..." -ForegroundColor Green
cmake ..

Write-Host "Done ✅ $Module.h updated" -ForegroundColor Green
