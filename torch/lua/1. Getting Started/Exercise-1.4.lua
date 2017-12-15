#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: Exercise-1.4.lua

-- Which of the following strings are valid identifiers?

-- I refer https://github.com/xfbs/PiL3

print("until?\t--> not valid, question marks are not allowed")
print("end\t--> not valid, reserved keyword")
print("nil\t--> not valid, reserved type name")

print("___\t--> valid")
print("_end\t--> valid")
print("End\t--> valid")
print("NULL\t--> valid")
