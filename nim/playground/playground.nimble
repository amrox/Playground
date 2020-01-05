# Package

version       = "0.1.0"
author        = "Andy Mroczkowski"
description   = "A new awesome nimble package"
license       = "MIT"
srcDir        = "src"
installExt    = @["nim"]
bin           = @["playground"]



# Dependencies

requires "nim >= 1.0.4"
requires "minmaxheap"
