#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: practice-01.lua


-- example-01.txt is
-- "Product good 45"
-- "Produce bad 79"
t = io.open("./example-01.txt")
io.input(t)

print(io.read("a"))    -- "Product good 45"
                       -- "Produce bad 79"
print(io.read("num"))  -- nil                     
print(io.read("n"))    --nil
