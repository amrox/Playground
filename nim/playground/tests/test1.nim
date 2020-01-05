# This is just an example to get you started. You may wish to put all of your
# tests into a single file, or separate them into multiple `test1`, `test2`
# etc. files (better names are recommended, just make sure the name starts with
# the letter 't').
#
# To run these tests, simply execute `nimble test`.

import unittest
import options

import playgroundpkg/submodule

#test "correct welcome":
#  check getWelcomeMessage() == "Hello, World!"

test "kth":
  check kth(@[1], 1).get() == 1
  check kth(@[1, 2], 2).get() == 2
  check kth(@[2, 1], 2).get() == 2
  check kth(@[10, 2, 1, 19, 5, 4], 3).get() == 4
  check kth(@[2, 1], 3).isNone
  check kth(@[1], 0).isNone
  check kth(@[1], -1).isNone
