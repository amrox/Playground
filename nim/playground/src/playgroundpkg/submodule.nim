# This is just an example to get you started. Users of your hybrid library will
# import this file by writing ``import playgroundpkg/submodule``. Feel free to rename or
# remove this file altogether. You may create additional modules alongside
# this file as required.

import algorithm
import options

proc getWelcomeMessage*(): string = "Hello, World!"

proc kth*(list: seq[int], k: int): Option[int] =
  let idx = k - 1
  if idx < 0 or idx >= len(list):
    return none(int)
  return some(sorted(list)[idx])
