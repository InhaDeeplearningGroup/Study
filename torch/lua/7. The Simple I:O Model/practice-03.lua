#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: practice-03.lua


-- example-03.txt is
-- "Product good 45"
-- "Produce bad 79"
-- "Produce middle 82"
t = io.open("./example-03.txt")
io.input(t)

local count = 0
for line in io.lines() do
  count = count + 1
  io.write(string.format("%6d   ", count), line, "\n")
end


-- It prints
-- 1   "Product good 45"
-- 2   "Produce bad 79"
-- 3   "Produce middle 82"
