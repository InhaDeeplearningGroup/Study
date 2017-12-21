#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: Exercise-4.4.lua

function insert(strings, position, str)
  first = string.sub(strings, 1, position)
  first = string.sub(first, 1, -2)
  later = string.sub(strings, position, -1)
  final = first .. str .. later
  return final
end

strings = "açåo"
position = 5
str = "!"

print(insert(strings, position, str))

-- It prints aç�!�o
-- Because ç represents xC3 and å represents xA5 for UTF-8 strings, 
-- ! inserted by 5th position that is aç�!�o

-- At first, use need to install utf8 following, 
-- $ luarocks install utf8
function insert_new(strings, position, str)
  first = string.sub(strings, utf8.offset(strings, -2, position-1))
  final = first .. str
  return final
end

strings = "açåo"
position = 5
str = "!"

print(insert_new(strings, position, str))

-- It is very first examples. 
-- You have to try better function :)