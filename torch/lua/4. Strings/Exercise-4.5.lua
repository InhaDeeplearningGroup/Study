#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: Exercise-4.5.lua

function remove(strings, position, append)
  p1 = position - 1
  p2 = position + append
  first = string.sub(strings, 1, p1)
  later = string.sub(strings, p2, -1)
  final = first .. " " .. later
  return final
end

strings = "hello world"
position = 7
append = 4

print(remove(strings, position, append))
