#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: Exercise-4.3.lua

function string.Split(str, delimiter)
  return string.Explode(delimiter, str)
end



function insert_string1(strings, position, str)
  part1= string.sub(strings, position)
  final = str .. part1
  return final
end

strings = "hello world"
position = 1
str = "start: "

print(insert_string1(strings, position, str))

-- Still ongoing...