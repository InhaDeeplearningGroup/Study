#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: Exercise-3.6.lua

-- Compute the volume of a right circular cone
-- V = 1/3 * (bottom area) * (height) = 1/3 * pi * r * h

function volume (radius, height)
  v = math.pi * radius * radius * height
  v = v / 3
  return v
end

print("Write radius")
radius = io.read("*n")
print("Write height")
height = io.read("*n")

print(volume(radius, height) .. " ... Finish")





