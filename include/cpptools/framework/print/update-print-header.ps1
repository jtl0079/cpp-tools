# ================================
# 更新 openmp 聚合头
# 使用 CMake 重新配置以触发生成
# ================================

$Root = Split-Path -Parent $MyInvocation.MyCommand.Path
$BuildDir = "$Root/build"

Write-Host "== Updating print aggregate header ==" -ForegroundColor Cyan

if (!(Test-Path $BuildDir)) {
    Write-Host "Build directory not found. Creating..." -ForegroundColor Yellow
    New-Item -ItemType Directory -Path $BuildDir | Out-Null
}

Set-Location $BuildDir

Write-Host "Running CMake configure to regenerate headers..." -ForegroundColor Green
cmake ..

Write-Host "Done ✅ print.h updated" -ForegroundColor Green
