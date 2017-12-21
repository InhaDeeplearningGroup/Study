#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: Exercise-5.1.lua

sunday = "monday"; monday = "sunday"
t = {sunday = "monday", [sunday] = monday}
print(t.sunday, t[sunday], t[t.sunday])

-- It prints monday   sunday   sunday
-- Because t.sunday is "monday" and t["monday"] = "sunday"