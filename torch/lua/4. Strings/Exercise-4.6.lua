#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: Exercise-4.6.lua

function remove(strings, position, append)
  p1 = position -1
  p2 = position + append
  first = string.sub(strings, 1, p1)
  later = string.sub(strings, p2, -1)
  final = first .. later
  return final
end

strings = "açåo"
position = 2
append = 2

print(remove(strings, position, append))  -- It prints aåo


function remove_new(strings, position, append)
  add = 3 - append
  p1 = string.sub(strings, utf8.offset(strings, position+1))
  final = string.sub(p1, add, add+2)
  return final
end

strings = "açåo"
position = 2
append = 2

print("The result string is: " .. remove_new(strings, position, append))  -- It prints åo

strings = "açåo"
position = 1
append = 2

print("The result string is: " .. remove_new(strings, position, append))  -- It prints çå

strings = "açåo"
position = 0
append = 2

print("The result string is: " .. remove_new(strings, position, append))  -- It prints aç


