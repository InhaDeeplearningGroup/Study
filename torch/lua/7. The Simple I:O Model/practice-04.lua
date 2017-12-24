#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: practice-04.lua


while true do
  local n1, n2, n3 = io.read("n", "n", "n")
  if not n1 then break end
  print(math.max(n1, n2, n3))
end



