#!/usr/bin/env lua
-- Programming in Lua (Fourth edition)
-- file: Exercise-3.1.lua

-- Which of the following are valid numerals? What are their values?

print(".0e12\t\t  --> valid (0.0)")
print(".e12\t\t  --> invalid (no decimal parts (1 more parts)")
print("0.0e\t\t  --> invalid (stdin:1: malformed number near '0.0e')")
print("0x12\t\t  --> valid (18)")
print("0xABFG\t\t  --> invalid (stdin:1: ')' expected near 'G'")
print("0xA\t\t  --> valid (10)")
print("FFFF\t\t  --> nil")
print("0xFFFFFFFF  --> valid (4294967295)")
print("0x  --> invalid (stdin:1: malformed number near '0x')")
print("0x1P10  --> valid (1024)")
print("0.1e1  --> valid (1.0)")
print("0x0.1p1 --> valid (0.125)")





