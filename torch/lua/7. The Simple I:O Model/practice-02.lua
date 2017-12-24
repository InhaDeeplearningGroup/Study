#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: practice-02.lua


-- example-02.txt is
-- "Product good 45"
-- "Produce bad 79"
t = io.open("./example-02.txt")
io.input(t)

for count = 1, math.huge do
  local line = io.read("L")
  if line == nil then break end
  io.write(string.format("%6d\n", count, line))
end


-- It prints, 
--   1
--   2
  
  
  
