#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: Exercise-1.1.lua

function factorial(n)
  if n < 0 then 
    return nil
  elseif n == 0 then
    return 1
  else
    return n * factorial(n-1)
  end
end

print("Type a number: ")
num = io.read("*n")

f = factorial(num)


if f == nil then
  print("[INFO] ValueError: negative values")
else
  print("Result value is", f)
end
