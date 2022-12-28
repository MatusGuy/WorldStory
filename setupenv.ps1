<#
this script may setup the libraries, tools and enviroment needed to work
on this project.
#>

param (
    [switch] $RunCMake
)

$ErrorActionPreference = 'Stop'

Push-Location -Path $PSScriptRoot

$qtpropertybrowser = (New-Item -Force -Path "./lib/include/qtpropertybrowser/" -ItemType 'Directory')

Invoke-WebRequest -Uri "https://github.com/MatusGuy/qt-solutions/archive/refs/heads/master.zip" -OutFile "./qt6-solutions.zip"

Expand-Archive -Path "./qt6-solutions.zip" -DestinationPath "./qt6-solutions/"

Push-Location -Path "./qt6-solutions/qt-solutions-master/qtpropertybrowser"

Copy-Item -Path "./src/" -Destination $qtpropertybrowser -Force -Recurse
Copy-Item -Path "./pathedit-ext/" -Destination $qtpropertybrowser -Force -Recurse

Pop-Location

Remove-Item -Path "./qt6-solutions/" -Recurse -Force -Confirm:$false
Remove-Item -Path "./qt6-solutions.zip" -Force -Confirm:$false

if ($RunCMake) {
    & cmake
}

Pop-Location

exit