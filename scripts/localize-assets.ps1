$ErrorActionPreference = 'Stop'
$repositoryRoot = Split-Path -Parent $PSScriptRoot
$assetNames = @(
    'codelab-elements.css',
    'native-shim.js',
    'custom-elements.min.js',
    'prettify.js',
    'codelab-elements.js'
)
foreach ($assetName in $assetNames) {
    $assetPath = Join-Path $repositoryRoot "assets/codelab/$assetName"
    if (-not (Test-Path -LiteralPath $assetPath -PathType Leaf)) {
        throw "Missing local Codelab asset: $assetPath"
    }
}
$utf8 = New-Object System.Text.UTF8Encoding($false)
$updated = 0
foreach ($directory in Get-ChildItem -LiteralPath $repositoryRoot -Directory) {
    $pagePath = Join-Path $directory.FullName 'index.html'
    if (-not (Test-Path -LiteralPath $pagePath -PathType Leaf)) { continue }
    $html = [System.IO.File]::ReadAllText($pagePath)
    $localized = $html
    foreach ($assetName in $assetNames) {
        $localized = $localized.Replace(
            "https://storage.googleapis.com/claat-public/$assetName",
            "../assets/codelab/$assetName"
        )
    }
    if ($localized -ne $html) {
        [System.IO.File]::WriteAllText($pagePath, $localized, $utf8)
        $updated++
    }
}
Write-Output "Localized Codelab assets in $updated page(s)."

