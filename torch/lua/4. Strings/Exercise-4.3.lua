#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: Exercise-4.3.lua

function insert(strings, position, str)
  first = string.sub(strings, 1, position)
  first = string.sub(first, 1, -2)
  later = string.sub(strings, position, -1)
  final = first .. str .. later
  return final
end

strings = "hello world"
position = 1
str = "start: "

print(insert(strings, position, str))


strings = "hello world"
position = 7
str = "small "

print(insert(strings, position, str))
