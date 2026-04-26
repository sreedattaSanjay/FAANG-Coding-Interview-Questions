# run_cpp.ps1 - Compile and run C++ files using Visual Studio
# Usage: .\run_cpp.ps1 path\to\file.cpp

param(
    [Parameter(Mandatory=$true, Position=0)]
    [string]$FilePath
)

# Check if file exists
if (-not (Test-Path $FilePath)) {
    Write-Host "Error: File '$FilePath' not found!" -ForegroundColor Red
    exit 1
}

# Get absolute path and file info
$FullPath = Resolve-Path $FilePath
$FileDir = Split-Path $FullPath -Parent
$FileName = [System.IO.Path]::GetFileNameWithoutExtension($FullPath)
$ExePath = Join-Path $FileDir "$FileName.exe"

Write-Host "`n=== Compiling: $FullPath ===" -ForegroundColor Cyan

# Find and initialize VS Developer environment
$vsPath = Get-ChildItem "${env:ProgramFiles}\Microsoft Visual Studio\2022\*\Common7\Tools\Launch-VsDevShell.ps1" -ErrorAction SilentlyContinue | Select-Object -First 1

if (-not $vsPath) {
    Write-Host "Error: Visual Studio 2022 not found!" -ForegroundColor Red
    exit 1
}

# Initialize VS environment (suppress output)
& $vsPath -SkipAutomaticLocation | Out-Null

# Compile
$compileResult = & cl /EHsc /nologo "/Fe:$ExePath" $FullPath 2>&1

if ($LASTEXITCODE -ne 0) {
    Write-Host "`nCompilation failed:" -ForegroundColor Red
    Write-Host $compileResult
    exit 1
}

Write-Host "Compilation successful!" -ForegroundColor Green

# Run
Write-Host "`n=== Output ===" -ForegroundColor Cyan
& $ExePath

# Cleanup .obj file
$ObjFile = Join-Path (Get-Location) "$FileName.obj"
if (Test-Path $ObjFile) {
    Remove-Item $ObjFile -ErrorAction SilentlyContinue
}

Write-Host "`n=== Done ===" -ForegroundColor Green

